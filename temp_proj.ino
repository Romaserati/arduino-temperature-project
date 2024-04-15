#include <temperature.h>;

void setup() {
  // put your setup code here, to run once:
  for (int i = 3; i < 13; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  
  sensor.begin();
  lcd.init();
  lcd.backlight();
  Serial.begin(115200);
}

void loop() {
  printTempOnLed(5000);
  printTempOnMonitor(1000);
}
