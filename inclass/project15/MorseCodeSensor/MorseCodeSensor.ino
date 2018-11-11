#define phc A0
#define amb A1
int ledPin = 5;
int buttonApin = 2;
int current_bri = 0;
int current_amb = 0;
bool on = false;
int counter = 0;
int ss = 0;
int os = 0;
int nums = 0;
int numo = 0;

int burst_start = 0;
int burst_end = 0;

volatile byte state = LOW;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonApin, INPUT_PULLUP);
}

void loop() { 
  
  // put your main code here, to run repeatedly:
  if ( digitalRead(buttonApin) == LOW ){
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(ledPin, LOW);
    state = LOW;
  }

  current_amb = analogRead(amb);
  current_bri = analogRead(phc);

//  Serial.print(current_bri);
//  Serial.print("------");
//  Serial.println(current_amb);

  if ( current_bri > current_amb ) {
    if ( on == false ) {
      burst_start = millis();
    }
    on = true;
    ++counter;
  } else if ( current_bri <= current_amb ) {
    if ( on == true ){
      burst_end = millis();
    }
    on = false;
  }

  if ( !on && counter > 0 ) {
    if ( burst_end - burst_start > 100 && burst_end - burst_start < 500 ) {
      ++ss;
//      Serial.print(".");
//      Serial.print("DOT ");
//      Serial.print(burst_end - burst_start);
//      Serial.println("ms");
    } else if ( burst_end - burst_start >= 500 ) {
      ++os;
//      Serial.print("-");
//      Serial.print("DASH ");
//      Serial.print(burst_end - burst_start);
//      Serial.println("ms");
    }
    
    
    counter = 0;
  }

  if ( ss == 3 ) {
    Serial.print("S");
    ss = 0;
    //os = 0;
    ++nums;
  }

  if ( os == 3 ) {
    Serial.print("O");
    os = 0;
    //ss = 0;
    ++numo;
  } 

  if ( nums == 2 && numo == 1 ) {
    Serial.println("SOS Received");
    nums=0;
    numo=0;
  }
}


