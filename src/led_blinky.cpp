#include "led_blinky.h"

void led_blinky(void *pvParameters){
  pinMode(LED_GPIO, OUTPUT);
  TickType_t xfrequency;
  float temperature;

  while(1) {
    if (xSemaphoreTake(xBinarySemaphoreData, portMAX_DELAY) == pdTRUE) {
      temperature = sensordata.temperature;
      xSemaphoreGive(xBinarySemaphoreData);
    }
    if(temperature < (float)30)  
      xfrequency = pdMS_TO_TICKS(1000);
    else if(temperature >= (float)30 && temperature <= (float)35)
      xfrequency = pdMS_TO_TICKS(500);
    else 
      xfrequency = pdMS_TO_TICKS(250);
    Serial.println("Temperature: " + String(temperature) + " °C");
    Serial.printf("Frequency of Led is: %.0f HZ \n", 1/(((float)xfrequency*2)/1000));
    digitalWrite(LED_GPIO,HIGH);
    vTaskDelay(xfrequency);
    digitalWrite(LED_GPIO,LOW);
    vTaskDelay(xfrequency);
  }          
}