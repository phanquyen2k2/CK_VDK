  #include <SoftwareSerial.h>
int gasPin = 0;
int val = 0;
SoftwareSerial HC05_master(2,3); //tx,rx
void setup() {
  Serial.begin(9600);
  HC05_master.begin(9600);
}

void loop() {

  val = analogRead(gasPin);
  Serial.println(val);
  
  if (val <500) {
    HC05_master.println("ff");
  }
  else if (val >=500) {
    HC05_master.println("ffffff");
  } 
  delay(500);   
}