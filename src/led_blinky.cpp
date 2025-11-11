#include "led_blinky.h"
#include "global.h"
void led_blinky(void *pvParameters)
{
  pinMode(LED_GPIO, OUTPUT);
  TickType_t xfrequency = pdMS_TO_TICKS(250);
  float temperature = 0;

  while (1)
  {

    // MLResult ml_result;
    SensorData data_receive;
    // if (xQueueReceive(xQueueMLResultforLED, &ml_result, 0) == pdPASS)
    // {
    //   Serial.print("[LED] Received from TinyML - Level: ");
    //   Serial.println(ml_result.anomaly_type);

    //   if (ml_result.anomaly_type == "WARNING")
    //     xfrequency = pdMS_TO_TICKS(125);
    //   else if (ml_result.anomaly_type == "CRITICAL")
    //     xfrequency = pdMS_TO_TICKS(50);
    //   else
    //   {
    //     float temp = ml_result.temperature;

    //     if (temp < 30.0)
    //     {
    //       xfrequency = pdMS_TO_TICKS(500);
    //     }
    //     else if (temp >= 30.0 && temp <= 35.0)
    //     {
    //       xfrequency = pdMS_TO_TICKS(250);
    //     }
    //     else
    //     {
    //       xfrequency = pdMS_TO_TICKS(125);
    //     }
    //   }
    //   Serial.print("[LED] Temperature: ");
    //   Serial.print(ml_result.temperature, 2);
    //   Serial.print("°C | Frequency: ");
    //   Serial.print(1.0 / (((float)xfrequency * 2) / 1000.0), 1);
    //   Serial.println(" HZ");
    // }
    // else
    // {
    //   SensorData sensor_data;
    //   if (xQueueReceive(xQueueForLedBlink, &sensor_data, pdMS_TO_TICKS(100)) == pdPASS)
    //   {
    //     Serial.println("[LED] Received from Sensor (backup)");

    //     float temp = sensor_data.temperature;

    //     if (temp < 30.0)
    //     {
    //       xfrequency = pdMS_TO_TICKS(500);
    //     }
    //     else if (temp >= 30.0 && temp <= 35.0)
    //     {
    //       xfrequency = pdMS_TO_TICKS(250);
    //     }
    //     else
    //     {
    //       xfrequency = pdMS_TO_TICKS(125);
    //     }
    //     Serial.print("[LED] Temperature: ");
    //     Serial.print(temp, 2);
    //     Serial.print("°C | Frequency: ");
    //     Serial.print(1.0 / (((float)xfrequency * 2) / 1000.0), 1);
    //     Serial.println(" HZ");
    //   }
    // }
    if (xQueueReceive(xQueueForLedBlink, &data_receive, portMAX_DELAY) == pdPASS)
    {
      // Serial.println("Semaphore was recieved.");
      temperature = data_receive.temperature;

      if (temperature < (float)30)
        xfrequency = pdMS_TO_TICKS(500);
      else if (temperature >= (float)30 && temperature <= (float)35)
        xfrequency = pdMS_TO_TICKS(250);
      else
        xfrequency = pdMS_TO_TICKS(125);
    
    if(xSemaphoreTake(xSemaphoreMutex, portMAX_DELAY) == pdTRUE)
    {
      Serial.print("[LED] Temperature: ");
      Serial.print(temperature, 2);
      Serial.print("°C | Frequency: ");
      Serial.print(1.0 / (((float)xfrequency * 2) / 1000.0), 1);
      Serial.println(" HZ");

      xSemaphoreGive(xSemaphoreMutex);
    }
    }
    digitalWrite(LED_GPIO, HIGH);
    vTaskDelay(xfrequency);
    digitalWrite(LED_GPIO, LOW);
    vTaskDelay(xfrequency);
  }
}
