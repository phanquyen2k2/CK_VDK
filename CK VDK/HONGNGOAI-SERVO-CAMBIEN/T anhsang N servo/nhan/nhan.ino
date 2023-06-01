#include "IRremote.h"
#include <Servo.h>
Servo servo;
int servoPin = 9;
int goc = 180;
 
int RECV_PIN = 11;
 
IRrecv irrecv(RECV_PIN);
// s -> - : chan so 11, chan 5V, chan GND 
decode_results results;
 
void setup()
{
  Serial.begin(9600);
  servo.attach(servoPin);
  irrecv.enableIRIn(); // Start the receiver
}
void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    
    if (results.value == 1) { //nếu giá trị tín hiệu nhận được 1, động cơ servo sẽ hoạt động 
      servo.write(goc);
      delay(500);
      servo.write(0);
      delay(500);
    }
    else{
      servo.write(goc*2/3);
      delay(500);
      servo.write(0);
      delay(500);
    }
    irrecv.resume();
  }
}