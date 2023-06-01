#include "IRremote.h"

IRsend irsend;

int hn = 2;
int val;
void setup(){
 
  Serial.begin(9600);  // configure baud rate to 9600 bps
}

void loop(){
  val = digitalRead(hn);
  Serial.println(val, DEC);
  

    if(val == HIGH)
    {
       irsend.sendRC5(0x1, 8); 
    }
    else
    {
      irsend.sendRC5(0x0, 8); 
    }
    delay(1000);
}

