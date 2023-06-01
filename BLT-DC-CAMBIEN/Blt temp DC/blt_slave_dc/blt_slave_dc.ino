#include <SoftwareSerial.h>

SoftwareSerial HC05_slave(2,3); //tx,rx
int in1 = 12;
int in2 = 13;
int enA = 11;
String readStr;

void setup() {
  Serial.begin(9600);
  HC05_slave.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enA, OUTPUT);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void loop() {
  if (HC05_slave.available()) {
    readStr = HC05_slave.readString();
    readStr.trim();
    Serial.println(readStr.length());
    if (readStr.length()<=2) {
      forward(255);

    }
    else if (readStr.length()==6 or readStr.length() == 3) {
      backward(255);

    } 
  } 
  delay(100);
}
void forward(int dutycycle) {
  // Động cơ A
  analogWrite(enA, dutycycle);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
 

 
  // Đèn
}
void backward(int dutycycle) {
  // Động cơ A
  analogWrite(enA, dutycycle);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}