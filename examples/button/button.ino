/*

 */


#include <DioMoni.h>


#define LED 13 // Define the led's pin

DioMoni button(12);

void setup()
{
  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);
  Serial.begin(9600);
}

void loop()
{


}
