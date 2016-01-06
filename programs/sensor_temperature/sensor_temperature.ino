#include <dht.h>
dht DHT;
#define DHT11_PIN 3

void setup() {
  Serial.begin(9600);
  Serial.println("Starting Temperature Detector...");
}

void loop() {
  // put your main code here, to run repeatedly:
int chk = DHT.read11(DHT11_PIN);
Serial.println(DHT.temperature, 1);
delay(1000);
}
