#include "IRremote.h"

IRsend irsend;

int GasPin = 0;
int val;
void setup(){
 
  Serial.begin(9600);  // configure baud rate to 9600 bps
}

void loop(){
  val = analogRead(GasPin);
  Serial.println(val, DEC);
  delay(100);

    if(val < 500)
    {
       irsend.sendRC5(0x1, 8); 
    }
    else
    {
      irsend.sendRC5(0x0, 8); 
    }
}

