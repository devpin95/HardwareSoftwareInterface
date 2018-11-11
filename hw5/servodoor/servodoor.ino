#include <Servo.h>

Servo servo;

int buttonpin = 2;
int deg = 0;
int count = 0;

volatile byte state = LOW;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(9);
  attachInterrupt(digitalPinToInterrupt(buttonpin), toggle, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
  servo.write(deg);
  delay(100);
}

void toggle() {
  ++count;
  if ( count == 0 ) {
    // dont do anything
  }
  else if ( count % 2 == 0 ) {
    // turn 90
    deg = 90;
//    Serial.print(count);
//    Serial.print("-----");
//    Serial.println("OPEN");
//    servo.write(90);
  }
  else if ( count % 2 == 1 ) {
    // turn -90
    deg = 0;
//     Serial.print(count);
//    Serial.print("-----");
//    Serial.println("CLOE");
//    servo.write(0);
  }
}

