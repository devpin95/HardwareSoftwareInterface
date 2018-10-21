#include "dht.h"

#define libreadpin 7
#define thermreadpin A0
dht d;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  d.read11(libreadpin);

  int temp = analogRead(thermreadpin);
  double tempK = log(10000.0 * ((1024.0 / temp - 1)));
  tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );
  float tempC = tempK - 273.15;
  
  Serial.print( tempC );
  Serial.print( "\t\t" );
  Serial.println( d.temperature );
  Serial.println();

  delay(2000);
}
