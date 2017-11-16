#include <SPI.h>

int plus = 3;
int negative = 2;
 
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  SPI.begin();
//  pinMode(plus, OUTPUT);    
//  pinMode(negative, OUTPUT);     
//  digitalWrite(plus, HIGH);
//  digitalWrite(power, LOW);

  pinMode(10, OUTPUT);     
  digitalWrite(10, LOW);
  SPI.end();  
}
 
// the loop routine runs over and over again forever:
void loop() {
//  digitalWrite(negative, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(1000);               // wait for a second
//  digitalWrite(negative, LOW);    // turn the LED off by making the voltage LOW
//  delay(3000);               // wait for a second
}
