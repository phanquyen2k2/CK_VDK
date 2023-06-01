#include "IRremote.h"
#include <Stepper.h>

#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11  

int stepsPerRevolution = 1024;
Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);
// s -> - : chan so 12, chan 5V, chan GND
int RECV_PIN = 12;
 
IRrecv irrecv(RECV_PIN);
 
decode_results results;
void setup(){
  myStepper.setSpeed(30);
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}
// nho cam chan nguon may con cho
void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    
    if (results.value == 1) { //nếu giá trị tín hiệu nhận được 1, động cơ servo sẽ hoạt động 
      myStepper.step(-stepsPerRevolution);
      delay(500);
    }
    if (results.value == 0)
    {
      myStepper.step(stepsPerRevolution);
      delay(500);
    }
    irrecv.resume();
  }
}