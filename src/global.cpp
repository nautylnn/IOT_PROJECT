#include "global.h"
//float glob_temperature = 0;
//float glob_humidity = 0;


String WIFI_SSID;
String WIFI_PASS;
String CORE_IOT_TOKEN;
String CORE_IOT_SERVER;
String CORE_IOT_PORT;

String ssid = "ESP32-YOUR NETWORK HERE!!!";
String password = "12345678";
String wifi_ssid = "abcde";
String wifi_password = "123456789";
boolean isWifiConnected = false;
SemaphoreHandle_t xBinarySemaphoreInternet = xSemaphoreCreateBinary();
SemaphoreHandle_t xBinarySemaphoreHumidity = xSemaphoreCreateBinary();
SemaphoreHandle_t xBinarySemaphoreTemperature = xSemaphoreCreateBinary();
SemaphoreHandle_t xBinarySemaphoreTinyML = xSemaphoreCreateBinary();

QueueHandle_t xQueueForLedBlink = xQueueCreate(5, sizeof(SensorData));
QueueHandle_t xQueueForNeoPixel = xQueueCreate(5, sizeof(SensorData));
QueueHandle_t xQueueForTinyML   = xQueueCreate(5, sizeof(SensorData));

//SemaphoreHandle_t xSensorDataReadySem = xSemaphoreCreateBinary();/
