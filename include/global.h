#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

// extern float glob_temperature;
// extern float glob_humidity;

typedef struct {
    float temperature;
    float humidity;
} SensorData;

extern String WIFI_SSID;
extern String WIFI_PASS;
extern String CORE_IOT_TOKEN;
extern String CORE_IOT_SERVER;
extern String CORE_IOT_PORT;

extern String wifi_ssid;
extern String wifi_password;
extern String ssid;
extern String password;
extern boolean isWifiConnected;

extern SemaphoreHandle_t xBinarySemaphoreInternet;
extern SemaphoreHandle_t xBinarySemaphoreHumidity;
extern SemaphoreHandle_t xBinarySemaphoreTemperature;
extern SemaphoreHandle_t xBinarySemaphoreTinyML;
extern SemaphoreHandle_t xSensorDataReadySem;

extern SemaphoreHandle_t xSensorDataMutex;

extern QueueHandle_t xQueueForLedBlink;
extern QueueHandle_t xQueueForNeoPixel;
extern QueueHandle_t xQueueForTinyML;
#endif