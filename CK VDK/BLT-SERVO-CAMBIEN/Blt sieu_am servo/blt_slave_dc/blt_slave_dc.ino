#include <SoftwareSerial.h>
#include <Servo.h>
Servo servo;
int servoPin = 14;
int goc = 360;
SoftwareSerial HC05_slave(2,3); //tx,rx

String readStr;

void setup() {
  Serial.begin(9600);
   servo.attach(servoPin);
  HC05_slave.begin(9600);
}

void loop() {
  if (HC05_slave.available()) {
    readStr = HC05_slave.readString();
    readStr.trim();
    Serial.println(readStr.length());
    if (readStr.length()<=2) {
      servo.write(180);
      delay(500);
      servo.write(0);
      delay(300);
    }
    else if (readStr.length()==6 or readStr.length() == 3) {
      servo.write(90);
      delay(300);
      servo.write(0);
      delay(300);
    } 
    else if (readStr.length() == 5 or readStr.length() == 10) {
       servo.write(30);
      delay(300);
      servo.write(0);
      delay(300);
    }
  } 
  delay(100);
}
