#include "neo_blinky.h"
#include "global.h"

void neo_blinky(void *pvParameters){
    Adafruit_NeoPixel strip(LED_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);
    strip.begin();
    // Set all pixels to off to start
    strip.clear();
    strip.show();
    float humidity;

    while(1) {
        vTaskDelay(500);
        if (xSemaphoreTake(xBinarySemaphoreData, portMAX_DELAY) == pdTRUE) {
            humidity = sensordata.humidity;
            xSemaphoreGive(xBinarySemaphoreData);
        }
        uint32_t color;
        String status;
        
        if (humidity < 0)
        {
            color = strip.Color(255,255,255);
            status = "ERROR";
        }
        else if (humidity >= 0 && humidity < 60)
        {
            color = strip.Color(255,0,0);
            status = "LOW";
        }
        else if (humidity >= 60 && humidity < 80)
        {
            color = strip.Color(0,255,0);
            status = "NORMAL";
        }
        else if (humidity >= 80)
        {
            color = strip.Color(0,0,255);
            status = "WET";
        }

        strip.setPixelColor(0, color);
        strip.show();

        Serial.print("NeoPixel Update - Humidity: ");
        Serial.print(humidity);
        Serial.print("% | Status: ");
        Serial.print(status);
        Serial.print(" | Color: ");
        if(status == "ERROR") Serial.println("White");
        else if(status == "LOW") Serial.println("Red");
        else if(status == "NORMAL") Serial.println("Green");
        else if(status == "WET") Serial.println("Blue");
    }
}