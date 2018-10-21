#define phc1 A0
#define phc2 A1
#define led 6

int phc1_val;
int phc2_val;

int brightness = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
//  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  phc1_val = analogRead(phc1);
  phc2_val = analogRead(phc2);
  brightness = map(phc1_val, 0, 1023, 0, 255);
  
  Serial.print("1: ");
  Serial.print(phc1_val);
  Serial.print("\t2: ");
  Serial.print(phc2_val);
  Serial.print("\tbrightness: ");
  Serial.print(brightness);
  Serial.println();

  analogWrite(led, brightness);

//  delay(1000);
}
