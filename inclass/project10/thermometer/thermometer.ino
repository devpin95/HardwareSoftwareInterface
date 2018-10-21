#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int tempPin = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int temp = analogRead(tempPin);
  double tempK = log(100000.0 * ((1024.0 / temp - 1)));
  tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );
  float tempC = tempK - 273.15;
  Serial.println(tempC);
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print(tempC);
  delay(1000);
}
