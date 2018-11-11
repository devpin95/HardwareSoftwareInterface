#define phc A0
int ledPin = 5;
int buttonApin = 2;

volatile byte state = LOW;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonApin, INPUT_PULLUP);
}

void loop() {
  ph
  // put your main code here, to run repeatedly:
  if ( digitalRead(buttonApin) == HIGH ){
    state = HIGH;
  }
  else {
    state = LOW;
  }
  digitalWrite(ledPin, state);
}

void toggle() {
  state = !state;
}

