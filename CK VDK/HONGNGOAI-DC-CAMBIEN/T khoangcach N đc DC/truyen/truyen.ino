#include "IRremote.h"

IRsend irsend;

const int trigPin = 9; 
const int echoPin = 10; 
unsigned long duration;  
int distance;

void setup(){
  pinMode(trigPin, OUTPUT); //Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);  // configure baud rate to 9600 bps
}

void loop(){
  digitalWrite(trigPin, LOW); // clears the trigPin
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2 ;

  Serial.print("Distance Measured "); 
  Serial.print(distance);
  Serial.println("cm");
  delay(100);

    if(distance < 20)
    {
       irsend.sendRC5(0x1, 8); 
    }
    else
    {
      irsend.sendRC5(0x0, 8); 
    }
}

