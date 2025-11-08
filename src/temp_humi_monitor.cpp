#include "temp_humi_monitor.h"
DHT20 dht20;
LiquidCrystal_I2C lcd(33,16,2);

void temp_humi_monitor(void *pvParameters){
    float temperature;
    float humidity;
    
    Wire.begin(11, 12);
    dht20.begin();

    lcd.begin();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor Task B-");
    lcd.setCursor(0, 1);
    lcd.print("Initializing...");
    
    vTaskDelay(2000 / portTICK_PERIOD_MS);

    while (1){
        /* code */
        vTaskDelay(50);
        // Reading temperature in Celsius
        if (xSemaphoreTake(xBinarySemaphoreData, portMAX_DELAY) == pdTRUE) {
            dht20.read();
            if (isnan(dht20.getTemperature()) || isnan(dht20.getHumidity())) {
                Serial.println("Failed to read from DHT sensor!");
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Sensor Error!");
                xSemaphoreGive(xBinarySemaphoreData);
                continue;
            }
            sensordata.temperature = dht20.getTemperature();
            sensordata.humidity = dht20.getHumidity();
            temperature = sensordata.temperature;
            humidity = sensordata.humidity;
            xSemaphoreGive(xBinarySemaphoreData);
        }
        lcd.clear();

        lcd.setCursor(0, 0);
        lcd.print("Temp: ");
        lcd.print(sensordata.temperature, 1); 
        lcd.print((char)223);
        lcd.print("C");

        lcd.setCursor(0, 1);
        lcd.print("Humi: ");
        lcd.print(sensordata.humidity, 1); 
        lcd.print("%");

        lcd.setCursor(11, 0); 
        if (sensordata.temperature >= 35.0) { 
            lcd.print("CRIT!");
        } else if (sensordata.temperature >= 30.0) {
            lcd.print("WARN ");
        } else { 
            lcd.print("NORM ");
        }

        lcd.setCursor(11, 1);
        if (humidity < 0) {
            lcd.print("ERROR");
        }
        else if (humidity >= 0 && humidity < 60) {
            lcd.print("LOW");
        }
        else if (humidity >= 60 && humidity < 80) {
            lcd.print("NORM");
        }
        else {
            lcd.print("WET");
        }
}
}