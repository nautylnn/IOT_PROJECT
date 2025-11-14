#ifndef __TASKCOREIOT_H__
#define __TASKCOREIOT_H__

#include <WiFi.h>
#include <Arduino_MQTT_Client.h>
#include <ThingsBoard.h>
#include "task_core_iot.h"
#include "task_wifi.h"

void taskCoreIOT(void *pvParameters);

#endif