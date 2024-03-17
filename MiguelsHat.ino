#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
bool displaying {false};
#define PIN_HALL_SENSOR 4
#define PIN_LED 13

volatile bool detected = true;

void setup() {
  pinMode(PIN_HALL_SENSOR, INPUT_PULLUP);
  pinMode(PIN_LED, OUTPUT);
  lcd.init();
}

void loop() {
  digitalWrite(PIN_LED, digitalRead(PIN_HALL_SENSOR));
  bool detected = digitalRead(PIN_HALL_SENSOR);
  
  if (!displaying && detected) {
    delay(1000);
    lcd.backlight();
    delay(1000);
    lcd.setCursor(0, 0);
    lcd.print("Techn. Defekt");
    lcd.setCursor(0, 1);
    lcd.print("Zug f\xE1llt aus.");
    displaying = true;
  }

  if (displaying && !detected)
  {
    delay(20000);
    lcd.clear();
    lcd.noBacklight();
    displaying = false;
  }
}

