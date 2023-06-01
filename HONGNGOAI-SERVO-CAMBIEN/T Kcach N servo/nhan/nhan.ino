#include "IRremote.h"
#include <Servo.h>
Servo servo;
int servoPin = 9;
int goc = 90;
 
int RECV_PIN = 11;
 
IRrecv irrecv(RECV_PIN);
 
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
      delay(300);
      servo.write(0);
      delay(300);
    }
    else{
      servo.write(goc*2/3);
      delay(300);
      servo.write(0);
      delay(300);
    }
    irrecv.resume();
  }
}