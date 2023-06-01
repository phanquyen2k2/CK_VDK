#include <SoftwareSerial.h>

#define LINE 4 // dèine line tracking digital pin 2
int val;
SoftwareSerial HC05_master(2,3); //tx,rx
void setup() {
  Serial.begin(9600);
  HC05_master.begin(38400);
}

void loop() {

  val = digitalRead(LINE);
  Serial.println(val);
  
  if (val==0) {
    HC05_master.println("ff");
  }
  else if (val== 1) {
    HC05_master.println("ffffff");
  } 
  // else {
  //   HC05_master.println("fffffffffffffff");
  // } 
  delay(1500); 
}