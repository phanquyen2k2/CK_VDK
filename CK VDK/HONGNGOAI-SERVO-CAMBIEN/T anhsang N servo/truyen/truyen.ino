#include "IRremote.h"

IRsend irsend;

int LIGHT = 0;
int val;
void setup(){
 
  Serial.begin(9600);  // configure baud rate to 9600 bps
}
// chan 3 ngu aj
// s -> - : chan so 3, chan 5V, chan GND
void loop(){
  val = analogRead(LIGHT);
  
  delay(100);

    if(val < 700)
    {
       irsend.sendRC5(0x1, 8); 
       Serial.println(val, DEC);
    }
    else
    {
      irsend.sendRC5(0x0, 8); 
    }
}

