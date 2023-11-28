
#include <ESP8266WiFi.h> //Esto depende de que ESP tienen

void setup()
{
  Serial.begin(9600);
  Serial.println();

  WiFi.begin("Samir's Galaxy Z Flip3 5G", "cfdu1056"); //Aqui va primero el nombre de su hotspot y luego contraseña

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println(".");
  }
  Serial.println();

  Serial.println("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {}
