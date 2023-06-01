#include "IRremote.h"

IRsend irsend;

int LIGHT = 0;
int val;
// s -> - : chan so 3, chan 5V, chan GND
void setup(){
 
  Serial.begin(9600);  // configure baud rate to 9600 bps
}

void loop(){
  val = analogRead(LIGHT);
  Serial.println(val, DEC);
  delay(100);

    if(val < 700)
    {
       irsend.sendRC5(0x1, 8); 
    }
    else
    {
      irsend.sendRC5(0x0, 8); 
    }
}

