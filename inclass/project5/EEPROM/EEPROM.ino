#include <EEPROM.h>

int memlen = 0;
int oldmem[10] = {0, };
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
  
  memlen = EEPROM.length();
  Serial.print("There are ");
  Serial.print(memlen);
  Serial.println(" addresses in EEPROM\n");

  // -----------------------------------------------------------------
  
  Serial.println("This is the data in 10-20");
  
  for ( int i = 0; i < 10; ++i ) {
    Serial.print( EEPROM.read(i+10) );
    Serial.print(", ");
  }
  
  // -----------------------------------------------------------------
  
  Serial.println("\n");
  
  for ( int i = 0; i < 10; ++i ) {
    EEPROM.put( i + 10 + sizeof(uint32_t), 256 );
  }

  Serial.println("This is the data in 10-20 after we change them all to 256");
  int val = 0;
  for ( int i = 0; i < 10; ++i ) {
    EEPROM.get( i + 10 + sizeof(uint32_t) ,val );
    Serial.print( val );
    Serial.print(", ");
  }

  Serial.println("\n");
  uint16_t val1;
  EEPROM.put( 10, 256 );
  EEPROM.get( 10, val1 );
  Serial.print( val1 );

}

void loop() {
  // put your main code here, to run repeatedly:

}
