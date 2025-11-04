#include "led_blinky.h"

void led_blinky(void *pvParameters){
    pinMode(LED_GPIO, OUTPUT);
    TickType_t xfrequency = pdMS_TO_TICKS(250);
    float temperature = 0;

    SensorData data_receive;
  while(1) {  
   
    if(xQueueReceive(xQueueForLedBlink, &data_receive, portMAX_DELAY ) == pdPASS)
    {
    // Serial.println("Semaphore was recieved.");
     temperature = data_receive.temperature;   

     if(temperature < (float)30)  
       xfrequency = pdMS_TO_TICKS(500);
     else if(temperature >= (float)30 && temperature <= (float)35)
       xfrequency = pdMS_TO_TICKS(250);
     else 
       xfrequency = pdMS_TO_TICKS(125);

    Serial.println("Temperature: " + String(temperature) + " °C");
    Serial.printf("Frequency of Led is: %.0f HZ \n", 1/(((float)xfrequency*2)/1000));
    }               
    digitalWrite(LED_GPIO,HIGH);
    vTaskDelay(xfrequency);
    digitalWrite(LED_GPIO,LOW);
    vTaskDelay(xfrequency);
  }
}