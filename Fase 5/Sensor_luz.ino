const int sensorPin = A0; // Define el pin analógico al que está conectado el sensor
int valorSensor; // Variable para almacenar el valor leído del sensor

void setup() {
  Serial.begin(9600); // Inicializa la comunicación serial
}

void loop() {
  valorSensor = analogRead(sensorPin); // Lee el valor del sensor
  Serial.println(valorSensor); // Envía el valor a la consola serial
  delay(1000); // Espera un segundo antes de leer nuevamente
}

