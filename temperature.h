#define ONE_WIRE_BUS 2

#include <DallasTemperature.h>
#include <Wire.h>
#include <OneWire.h>
#include <LiquidCrystal_I2C.h>

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensor(&oneWire);

LiquidCrystal_I2C lcd(0x27, 20, 4);

void printTempOnMonitor(uint32_t interval) {
  static unsigned long timer;
  if (timer + interval > millis()) return;
  timer = millis();
  
  sensor.requestTemperatures();
  delay(200);
  double temp = sensor.getTempCByIndex(0);
  if (temp != DEVICE_DISCONNECTED_C) {
    lcd.setCursor(0, 0);
    lcd.print("Temperature: ");
    lcd.print(temp);
  }
  else {
    lcd.print("Can't read temp");
  } 
}

void printTempOnLed(uint32_t interval) {
  static unsigned long timer;
  if (timer + interval > millis()) return;
  timer = millis();
  
  sensor.requestTemperatures();
  double temp = sensor.getTempCByIndex(0);
  for (int i = 3; i < temp / 3; i++) {
    if (temp / 3 > 13) {
      Serial.println("Temperature is higher than 40");
      for (int i = 3; i < 13; i++) {
        digitalWrite(i, HIGH);
        delay(100);
      }
      break;
    }
    digitalWrite(i, HIGH);
    delay(100);
    digitalWrite(temp / 3 + 1, LOW);
  }
}
