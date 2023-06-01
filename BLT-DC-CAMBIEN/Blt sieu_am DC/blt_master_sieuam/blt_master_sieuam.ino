#include <SoftwareSerial.h>

const int trig = 9;
const int echo = 10;
unsigned long duration;
int distance;

SoftwareSerial HC05_master(2,3); //tx,rx
void setup() {
  Serial.begin(9600);
  HC05_master.begin(38400);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2 ;
  Serial.print("Distance Measured = ");
  Serial.print(distance);
  Serial.println(" cm ");
  
  if (distance<10) {
    HC05_master.println("ff");
  }
  else if (distance <20) {
    HC05_master.println("ffffff");
  } 
  else if( distance >=20) {
    HC05_master.println("fffffffffffffff");
  }
  delay(1500);   
}
