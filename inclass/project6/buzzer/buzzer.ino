//www.elegoo.com
//2016.12.08

#include "pitches.h"

int buzzerPin = 2;
int blue = 7;
int red = 8;
int green = 12;
 
// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_F4, 
  NOTE_E4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, 
  NOTE_G4, NOTE_F4, NOTE_C4, NOTE_C4, NOTE_C5, 
  NOTE_A4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_AS4,
  NOTE_AS4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_F4
  };
int duration = 500;  // 500 miliseconds

int tempo[] = {
  8, 8, 4, 4, 4, 2, 8, 8, 4, 4, 4, 2, 8, 8, 4, 4, 4, 4, 4, 8, 8, 4, 4, 4, 2
};
 
void setup() {
 
}
 
void loop() {  
  for (int thisNote = 0; thisNote < 26; thisNote++) {
    // pin8 output the voice, every scale is 0.5 sencond
    tone(buzzerPin, melody[thisNote], 1130/tempo[thisNote]);

    if ( thisNote % 3 == 0 ) {
      //blue
      digitalWrite(blue, HIGH);
    }
    else {
      digitalWrite(blue, LOW);
    }

    if ( thisNote % 2 == 0 ) {
      //blue
      digitalWrite(red, HIGH);
    }
    else {
      digitalWrite(red, LOW);
    }

    if ( thisNote % 3 == 0 ) {
      //blue
      digitalWrite(green, HIGH);
    }
    else {
      digitalWrite(green, LOW);
    }
     
    // Output the voice after several minutes
    delay( (1130/tempo[thisNote])*1.275);
  }
   
  // restart after two seconds 
  delay(2000);
}
