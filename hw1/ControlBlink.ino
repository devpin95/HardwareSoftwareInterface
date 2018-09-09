int incomingByte = 0;   // for incoming serial data
int spdLED = 1000;  // 1 second

void setup() {
  // put your setup code here, to run once:
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
}

void loop() {
  // put your main code here, to run repeatedly:
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
  
    if ( incomingByte == '+' ) {
      if ( spdLED > 125 ) {
        spdLED /= 2;
        Serial.print(spdLED);
      }
    }
    else if ( incomingByte == '-' ) {
      if ( spdLED < 4000 ) {
        spdLED *= 2;
        Serial.print(spdLED);
      }
      else {
        Serial.print(spdLED);
      }
    }
  }
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(spdLED);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(spdLED);                       // wait for a second

}
