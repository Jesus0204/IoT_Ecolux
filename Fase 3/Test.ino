#include <DHT.h>

#define port 5 //En que puerto lo conectaron
#define type DHT11 //Tipo de sensor que tienen

DHT dht(port, type);
float temp,hume;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  hume = dht.readHumidity();
  temp = dht.readTemperature();
  Serial.println("Temperatura: " + String(temp)); 
  Serial.println("Humedad: "+ String(hume));
  if(temp < 20){
    Serial.println("Hace frio");
  }
  if(hume < 40){
    Serial.println("Esta mojado");
  }
  delay(5000);
  
}