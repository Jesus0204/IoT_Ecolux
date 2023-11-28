//#include "UbidotsMicroESP8266.h"
// Este archivo incluye una actualizacion de las librerias de Ubidots y observaras
// al conectarte a Ubidots que se crea otro dispostivo (Device) automaticamente
// tienes que configurar las etiquetas segun el nuevo dispositivo que se crea
// y adicionar la variable var_led  .... todo lo demás es identico 

#include "Ubidots.h"
#include "DHT.h"

#define DEVICE  "5ccf7f4fd351"  // Put here your Ubidots device label
#define VARIABLE  "temp"  // Put here your Ubidots variable label
#define VARIABLE2 "led"
#define VARIABLE3 "humedad"
#define VARIABLE4 "luz"
#define ID_TEMP "6529d32dba8d7a000d21f8fe" 
#define ID_HUM "653308b420c9ce000d8e7313"
#define ID_LED "6532ffb920c9ce000d8e7310"
#define ID_LUZ "654a5c4ac70c89000e05fdbc"
#define TOKEN  "BBFF-s20VLvTuXcpoMIs0Vn7lbCUfGEOY0n"  // Put here your Ubidots TOKEN

#define WIFISSID "iPhone" // Put here your Wi-Fi SSID
#define PASSWORD "J9qu-YUKa-IsSA-OH8Y" // Put here your Wi-Fi password

#define port 5
#define port2 4
#define type DHT11

DHT dht(port, type);

Ubidots client(TOKEN);
float Valor_Temperatura = 0;
float Valor_Humedad = 0;
int Valor_Luz = 0;

const int luzPin = A0;

void setup() {
    //client.wifiConnection(WIFISSID, PASSWORD);
    dht.begin();
    pinMode(port2, OUTPUT);
    digitalWrite(port2, 1);

    Serial.begin(9600);
    client.wifiConnect(WIFISSID, PASSWORD);

    //client.setDebug(true); // Uncomment this line to set DEBUG on
}

void loop() 
{
    float hume = dht.readHumidity();
    float temp = dht.readTemperature();
    int luz = analogRead(luzPin);
    float Valor_Led = client.get(DEVICE, VARIABLE2);

    if(isnan(hume)||isnan(temp)){
      Serial.println("No jala uwu");
      return;
    }

    Serial.println("------------------------------------");
    Serial.print("Temperatura: " + String(temp)); 
    Serial.println("------------------------------------");
    Serial.print("Humedad: "+ String(hume));
    Serial.println("------------------------------------");
    Serial.print("Luz: "+ String(luz));
    
    Valor_Temperatura = temp;
    
    client.add(ID_TEMP, Valor_Temperatura); 
    client.send();

    Valor_Humedad = hume;
    
    client.add(ID_HUM, Valor_Humedad); 
    client.send();

    Valor_Luz = luz;

    client.add(ID_LUZ,Valor_Luz);
    client.send();

    if (luz == 1024){
      digitalWrite(port2, HIGH);
    }
    else{
      digitalWrite(port2, LOW);
    }
    delay(5000);


}