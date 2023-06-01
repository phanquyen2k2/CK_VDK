#include <SoftwareSerial.h>
#include <Stepper.h>

#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
int stepsPerRevolution = 1024;
Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);  
SoftwareSerial HC05_slave(2,3); //tx,rx

String readStr;

void setup() {
  Serial.begin(9600);
  HC05_slave.begin(9600);
    myStepper.setSpeed(30);

}

void loop() {
  if (HC05_slave.available()) {
    readStr = HC05_slave.readString();
    readStr.trim();
    Serial.println(readStr.length());
    if (readStr.length()<=2) {
      myStepper.step(-stepsPerRevolution);
      delay(100);
    }
    else if (readStr.length()==6 or readStr.length() == 3) {
      myStepper.step(stepsPerRevolution);
      delay(100);
    } 
  
  } 
  delay(100);
}
