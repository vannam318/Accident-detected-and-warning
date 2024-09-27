#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

const int ThermalPin = A8;
const int VibrationPin = A9;
const int RainPin = A10;

int ThermalValue = 0;
int RainValue = 0;

int ThermalPoint = 100;
int VibraPoint = 50;
int RainPoint = 300;

void setup() {
  Wire.begin();
  lcd.begin();
  lcd.backlight();
  delay(1000);
  lcd.print("Blackbox Project");
  delay(2000);
  lcd.clear();
}

bool isAccidentCondition() {
  return RainValue < RainPoint || VibraValue > VibraPoint;
}

void loop() {
  int reading = analogRead(ThermalPin);
  float voltage = (reading * 5.0) / 1024.0;
  ThermalValue = voltage * 100.0;
  VibraValue = analogRead(VibrationPin);
  RainValue = analogRead(RainPin);
  
  bool accident = isAccidentCondition();

  if (accident) {
    for (int i = 0; i < 3; i++) {
      lcd.print("Canh bao tai nan");
      delay(1000);
      lcd.clear();
      delay(1000);
    }
    delay(2000);
    lcd.clear();
    lcd.print("Tai nan xay ra!");
    delay(3000);
    lcd.clear();
  } else {
    lcd.clear();
    lcd.print("Trang thai an toan");
    delay(1000);
  }
}