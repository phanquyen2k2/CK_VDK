#include "IRremote.h"
int enA = 11;
int in1 = 12;
int in2 = 13;
int RECV_PIN = 2;
String key;
int state = 0;
int count = 0;
int value = 0;
IRrecv irrecv(RECV_PIN);
 
decode_results results;
void setup(){
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    
    if (results.value == 1) { //nếu giá trị tín hiệu nhận được 1, động cơ servo sẽ hoạt động 
      forward(255);
    }
    if (results.value == 0)
    {
      backward(255);
    }
    irrecv.resume();
  }
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