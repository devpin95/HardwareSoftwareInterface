#include <EEPROM.h>
#include <string.h>

#define addr_first_login 0   // 255 = not first time, 0 = first time
#define addr_password_len 1
#define addr_password_start 2
#define NEW 0
#define RETURNING 255

bool first_login = false;
bool signedout = false;
int btnpin = 7;

void setup() {
  // put your setup code here, to run once:
  pinMode(btnpin, INPUT_PULLUP);
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps

//  EEPROM.write( addr_first_login, 0 );
  first_login = checkFirstTime();

  if ( first_login ) {
    Serial.print( "This is your first time logging in\n" );
    Serial.print( "Enter a password at least 4 characters long\n" );
    setPass( getPass() );
    Serial.println( "Press the button to reset" );
  }
  else {
    Serial.print( "Welcome back!\n" );
    Serial.print( "Please enter your password\n" );
    while ( !checkPass( getPass() ) ) {
      Serial.print( "Incorrect Password\n" );
    }

    Serial.println( "Successfully Logged In" );
    Serial.println( "Press the button to reset" );
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if ( digitalRead(btnpin) == LOW && !signedout ) {
    EEPROM.write( addr_first_login, NEW );
    Serial.println( "Resetting" );
    signedout = true;
  }
  
//  delay(1000);
}

String getPass( ) {
  String pass;
  while ( true ) {
    if ( Serial.available() > 0 ) 
    {
      pass = Serial.readString();
      if ( pass.length() < 4 ) Serial.print( "Password must be at least 4 characters long" );
      else return pass;
    }
  }
}

void setPass( const String &pass ) {
  for ( int i = 0; i < pass.length(); ++i ) {
      EEPROM.write( addr_password_start+i, pass[i] );
  }
  EEPROM.write( addr_password_len, pass.length() );
}

bool checkPass( const String &pass ) {
  int pass_len = EEPROM.read( addr_password_len );

  if (pass_len < pass.length()) return false; 
  
  for ( int i = 0; i < pass.length(); ++i ) {
    if ( pass[i] != EEPROM.read( addr_password_start+i ) ) {
      return false;
    }
  }
  return true;
}

bool checkFirstTime( ) {
  int fl = EEPROM.read( addr_first_login );
  if ( fl == NEW ) {
    EEPROM.write( addr_first_login, RETURNING );
    return true;
  }
  else {
    return false;
  }
}

