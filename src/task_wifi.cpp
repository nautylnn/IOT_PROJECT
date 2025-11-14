#include "task_wifi.h"

void startAPinWIFI()
{
    WiFi.mode(WIFI_AP);
    WiFi.softAP(String(SSID_AP), String(PASS_AP));
    Serial.print("AP IP: ");
    Serial.println(WiFi.softAPIP());
}

void startSTA()
{
    Serial.println("Connecting to AP ...");
    if (WIFI_SSID.isEmpty())
    {
        vTaskDelete(NULL);
    }

    WiFi.mode(WIFI_STA);

    if (WIFI_PASS.isEmpty())
    {
        WiFi.begin(WIFI_SSID.c_str());
    }
    else
    {
        Serial.println(WIFI_SSID.c_str());
        Serial.println(WIFI_PASS.c_str());
        WiFi.begin(WIFI_SSID.c_str(), WIFI_PASS.c_str());
    }

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    Serial.println("Connected to AP");
    //Give a semaphore here
    // xSemaphoreGive(xBinarySemaphoreInternet);
}

bool Wifi_reconnect()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        return true;
    }
    startSTA();
    return false;
}
