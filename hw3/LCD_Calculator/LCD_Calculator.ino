/*
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 8
 * LCD D4 pin to digital pin 9
 * LCD D5 pin to digital pin 10
 * LCD D6 pin to digital pin 11
 * LCD D7 pin to digital pin 12
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
*/

#include <LiquidCrystal.h>

#define INT_LIMIT 999999

String str;
float left;
float right;
char op;
int steps = 1;
String lcdstr;
String lcdstrval;
bool prompted_left = false;
bool prompted_op = false;
bool prompted_right = false;

int blink_counter = 0;
bool error = false;

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  if ( !error ) {
    if ( steps == 1 && !prompted_left ) {
      // prompt for left
      prompted_left = true;
      Serial.println("Enter the first number");
    }
    else if ( steps == 2 && !prompted_op ) {
      // prompt for operator
      prompted_op = true;
      Serial.println("Enter the operator +, -, *, /");
    }
    else if ( steps == 3 && !prompted_right ) {
      // prompt for right
      prompted_right = true;
      Serial.println("Enter the second number");
    }
    
    if ( Serial.available() > 0 ) {
      str = Serial.readString();
      if ( str == "C" || str =="c" ) {
        left = 0;
        right = 0;
        steps = 1;
        lcdstr = "";
        lcdstrval = "";
      }
      else {
        if ( steps == 1 ){
          // getting the left number
          lcdstr = "";
          left = str.toFloat();
          
          if ( left < INT_LIMIT ) {
            lcdstr += str;
            ++steps;
          } else {
            Serial.println("Number too large");
            lcdstrval = "error: overflow";
            lcdstr = "";
            Serial.print(lcdstr);
            prompted_left = false;
            steps = 1;
            error = true;
          }
        }
        else if ( steps == 2 ) {
          // getting the operator
          op = str[0];
          switch (op) {
             case '+' : ++steps; lcdstr += op; break;
             case '-' : ++steps; lcdstr += op; break;
             case '*' : ++steps; lcdstr += op; break;
             case 'x' : ++steps; lcdstr += op; break;
             case '/' : ++steps; lcdstr += op; break;
             default: Serial.println("Not a valid operation"); prompted_op = false; break;
          }
        }
        else if ( steps == 3 ) {
          // getting the right number
          right = str.toFloat();
          if ( right < INT_LIMIT ) {
            lcdstr += str;
            ++steps;
          } else {
            Serial.println("Number too large");
            lcdstrval = "error: overflow";
            prompted_right = false;
            error = true;
          }
        }
      }
    }
  
    else if ( steps == 4 ) {
      steps = 1;
      double val = calc(left, right, op);
      if ( val < INT_LIMIT ) {
        lcdstrval = '=' + String( val );
      }
      else {
        lcdstr = "";
        lcdstrval = "error: overflow";
        error = true;
        steps = 1;
      }
  
      Serial.print(lcdstr);
      Serial.println(lcdstrval);
  
      prompted_left = false;
      prompted_op = false;
      prompted_right = false;
    }
      
    // display the LCD string
    lcd.begin(16, 2);
    // Print a message to the LCD.
    lcd.print(lcdstr);
    lcd.setCursor(0,1);
    lcd.print(lcdstrval);
    delay(500);
  }
  else {
    lcd.clear();
    
    delay(500);
    
    lcd.begin(16, 2);
    // Print a message to the LCD.
    lcd.print(lcdstr);
    lcd.setCursor(0,1);
    lcd.print(lcdstrval);
    
    delay(500);
    
    ++blink_counter;

    if ( blink_counter == 2 ){
      error = false;
      blink_counter = 0;
    }
  }
}

double calc(float l, float r, char o) {
  switch (o) {
    case '+' : return l + r; break;
    case '-' : return l - r; break;
    case '*' : return l * r; break;
    case 'x' : return l * r; break;
    case '/' : return l / r; break;
    default: return l; break;
  }
}

