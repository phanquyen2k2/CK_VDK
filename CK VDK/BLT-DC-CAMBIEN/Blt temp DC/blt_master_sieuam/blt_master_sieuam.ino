#include <SoftwareSerial.h>
#include "dht11.h"
#define DHT11_PIN 4 
dht11 DHT;

SoftwareSerial HC05_master(2,3); //tx,rx
void setup() {
  Serial.begin(9600);
  HC05_master.begin(38400);
}

void loop() {
  int chk;
  Serial.print("DHT11, \t");
  chk = DHT.read(DHT11_PIN);
  switch(chk) {
    case DHTLIB_OK:
      Serial.print("OK, \t");
      break;
    case DHTLIB_ERROR_CHECKSUM:
      Serial.print("Checksum error, \t");
      break;
    case DHTLIB_ERROR_TIMEOUT:
      Serial.print("Time out error, \t");
      break;
    default:
      Serial.print("Unknown error, \t");
      break;
  }
  Serial.print("Do am: ");
  Serial.print(DHT.humidity, 1);
  Serial.print(", \t Nhiet do: ");
  Serial.print(DHT.temperature, 1);
  Serial.println(); 
  
  if(DHT.humidity > 40 && DHT.temperature <= 32){
    HC05_master.println("ff");
  }
  else {
    HC05_master.println("ffffff");
  } 
  // else if( distance >=20) {
  //   HC05_master.println("fffffffffffffff");
  // }
  delay(1500);   
}
