#include "IRremote.h"

IRsend irsend;

#define LINE 2 // dèine line tracking digital pin 2
int val;

void setup(){
  Serial.begin(9600);  // configure baud rate to 9600 bps
}

void loop(){
  val = digitalRead(LINE);
  Serial.println(val);
  delay(100);
  if(val == 0){
    Serial.println("đã vô 0");
    irsend.sendRC5(0x1, 8);
  }
  else if (val == 1)
  {
    Serial.println("đã vô 1");
      irsend.sendRC5(0x0, 8); 
  } 

    
}


