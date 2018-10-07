#define ENABLE 5
#define DIRA 3
#define DIRB 4

int xpin = A0;
int ypin = A1;
int swpin = 13;
int ledpin = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode( swpin, INPUT_PULLUP );
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  pinMode(ledpin,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  int y = analogRead(ypin);

  if ( y > 522 ) {
    digitalWrite(ENABLE,HIGH); // enable on
    digitalWrite(DIRA,HIGH); //one way
    digitalWrite(DIRB,LOW);
  }
  else if ( y < 502 ) {
    digitalWrite(ENABLE,HIGH); // enable on
    digitalWrite(DIRA,LOW); //one way
    digitalWrite(DIRB,HIGH);
  }
  else {
    digitalWrite(DIRA,LOW); //one way
    digitalWrite(DIRB,LOW);
    digitalWrite(ENABLE,LOW); // enable on
  }

  if ( digitalRead(swpin) == HIGH ) {
    digitalWrite(ledpin, HIGH);
  } else {
    digitalWrite(ledpin, LOW);
  }
  
  
//  digitalWrite(ENABLE,HIGH);
//  digitalWrite(DIRA,HIGH); //one way
//  digitalWrite(DIRB,LOW);
}
