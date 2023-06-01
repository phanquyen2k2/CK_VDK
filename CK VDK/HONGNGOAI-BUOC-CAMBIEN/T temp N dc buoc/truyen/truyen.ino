
#include "IRremote.h"

IRsend irsend;
#include "dht11.h"
#define DHT11_PIN 4 
dht11 DHT;
void setup() {
  Serial.begin(9600);
}
int led= 13;
void loop() {
  // put your main code here, to run repeatedly:
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
  if(DHT.humidity > 40 && DHT.temperature <= 24){
    irsend.sendRC5(0x1, 8); 
  }
  else {
    irsend.sendRC5(0x0, 8); 

  }
  //Serial.print(", \t ");
  //Serial.println(DHT.parity, 1);
  delay(1000);
}

