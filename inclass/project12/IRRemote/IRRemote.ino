#include "IRremote.h"

#define irpin 11
#define RED 6
#define GREEN 5
#define YELLOW 9
#define POWER 0xFFA25D
#define BTN1 0xFF30CF
#define BTN2 0xFF18E7
#define BTN3 0xFF7A85
#define VOLUP 0xFF629D
#define VOLDOWN 0xFFA857
#define BTNUP 0xFF906F
#define BTNDOWN 0xFFE01F

int red_level = 255;
int green_level = 255;
int yellow_level = 255;
bool red_blinking = false;
bool green_blinking = false;
bool yellow_blinking = false;
int blink_frequency = 250;
int brightness = HIGH;
bool on = true;

IRrecv irrecv(irpin);
decode_results results;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  irrecv.enableIRIn();  // start the receiver
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if ( irrecv.decode( &results ) ){
    switch ( results.value ) {
      case POWER: if ( on ) on=false; else on = true; break;
      case BTN1: if ( red_blinking ) red_blinking=false; else red_blinking=false;    break;
      case BTN2: if ( green_blinking ) green_blinking=false; else green_blinking=false;    break;
      case BTN3: if ( yellow_blinking ) yellow_blinking=false; else yellow_blinking=false;    break;
      case VOLUP: Serial.println("Vol+");    break;
      case VOLDOWN: Serial.println("Vol-");    break;
      case BTNUP: Serial.println("Up");    break;
      case BTNDOWN: Serial.println("Down");    break;
    }

    if ( on ) {
      if ( red_blinking ) analogWrite(RED, brightness);
      if ( green_blinking ) analogWrite(GREEN, brightness);
      if ( yellow_blinking ) analogWrite(YELLOW, brightness);
      delay(blink_frequency);
      if ( red_blinking ) analogWrite(RED, LOW);
      if ( green_blinking ) analogWrite(GREEN, LOW);
      if ( yellow_blinking ) analogWrite(YELLOW, LOW);
      delay(blink_frequency);
    } else {
      analogWrite(RED, LOW);
      analogWrite(GREEN, LOW);
      analogWrite(YELLOW, LOW);
    }
    
    irrecv.resume();
    
  }
  //delay(1000);
}
