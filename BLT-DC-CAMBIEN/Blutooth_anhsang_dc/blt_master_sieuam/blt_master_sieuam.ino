#include <SoftwareSerial.h>

int LIGHT = 0;
int val;
SoftwareSerial HC05_master(2,3); //tx,rx
void setup() {
  Serial.begin(9600);
  HC05_master.begin(9600);
}

void loop() {

  val = analogRead(LIGHT);
  Serial.println(val);
  
  if (val<700) {
    HC05_master.println("ff");
  }
  else if (val >= 700) {
    HC05_master.println("ffffff");
  }
  delay(1500);   
}