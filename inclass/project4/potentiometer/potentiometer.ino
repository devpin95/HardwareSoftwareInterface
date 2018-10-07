int green = 11;
int blue = 10;
int buttonpin = 7;
int potpin = A5;
int potmin = 0;
int potmax = 1023;
int ledmin = 0;
int ledmax = 255;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonpin, INPUT_PULLUP);
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
}

void loop() {
  // put your main code here, to run repeatedly:

  int val = analogRead(potpin);
  map(val, potmin, potmax, ledmin, ledmax);
  Serial.println(val);
  
  if (digitalRead(buttonpin) == LOW)
  {
    analogWrite(blue, LOW);
    analogWrite(green, val);
//    delay(250);
//    analogWrite(green, LOW);
//    delay(250);
  }
  else if (digitalRead(buttonpin) == HIGH)
  {
    analogWrite(green, LOW);
    analogWrite(blue, val);
//    delay(250);
//    analogWrite(blue, LOW);
//    delay(250);
  }
}
