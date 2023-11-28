#include <ESP8266WiFi.h> 
#include "Ubidots.h"

#define DEVICE  "5ccf7f4fd351"  // Put here your Ubidots device label
#define VARIABLE  "luz"  // Put here your Ubidots variable label
#define ID_LUZ "654a5c4ac70c89000e05fdbc"
#define TOKEN  "BBFF-s20VLvTuXcpoMIs0Vn7lbCUfGEOY0n"  // Put here your Ubidots TOKEN

#define WIFISSID "Samir's Galaxy Z Flip3 5G" // Put here your Wi-Fi SSID
#define PASSWORD "cfdu1056" // Put here your Wi-Fi password

Ubidots Client(TOKEN);

const char* ssid = "Samir's Galaxy Z Flip3 5G";       
const char* password = "cfdu1056";

char estado='0';
const int sensorPin = A0;
int Valor_Luz = 0;
int SalidaRele = 5;
int Led_cliente = 4;
int Led_conexionwifi = 16;
char EstadoRele='0';
double Luz = 0, barra=0,  cont_tiempo=0;


WiFiServer server(80);


void setup() {
    Serial.begin(9600);
    pinMode(SalidaRele, OUTPUT);
    pinMode(Led_cliente, OUTPUT);
    pinMode(Led_conexionwifi, OUTPUT); 
    digitalWrite(SalidaRele, HIGH);
    digitalWrite(Led_cliente, LOW);
    digitalWrite(Led_conexionwifi, LOW);
    delay(1000);

    
    WiFi.begin(ssid, password);
    Client.wifiConnect(WIFISSID,PASSWORD);
    Serial.printf("Conectando con red: %s\n", WiFi.SSID().c_str());

    while (WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");                    
    }

    Serial.println("");
    Serial.println("Conectado con red wifi");
    digitalWrite(Led_conexionwifi, HIGH);  
    
  // se configura como servidor
     server.begin();
     Serial.println("Modo servidor activado");
     Serial.printf("\n\nIP modulo: http://%s/\n", WiFi.localIP().toString().c_str());
     Serial.println("");
}



void loop() {
inicio_loop:

  WiFiClient client = server.available();
  if (estado =='0'){  
    Serial.println("esperando que el cliente se conecte al servidor");
    Serial.println("");
     estado='1';
  }
  if (!client) { 
    return;  
  } 
  estado='0';
  Serial.println("cliente conectado");
  Serial.println("");
  
  digitalWrite(Led_cliente, LOW);
  Serial.println("Esperando solicitud");
  cont_tiempo=0; 
  while(!client.available()){
    cont_tiempo= cont_tiempo +0.001 ; 
    if (cont_tiempo > 7) {
      Serial.println ("No hay respuesta del cliente...  ");

      client.println("Connection:close");
      client.println();
      Serial.println ("Cerrando conexión  ");
      Serial.println (" "); 
      delay(1000);
      goto inicio_loop;
    }
    delay(1);
  }

  digitalWrite(Led_cliente, HIGH);
  Serial.println("Solicitud recibida");
  String RespuestaCliente = client.readStringUntil('\r');
  Serial.println(RespuestaCliente);
  client.flush();
  Serial.println("");

  Luz = analogRead(A0);
  if (RespuestaCliente.indexOf('/RELE=ON') != -1) {
    //EstadoRele = '1';
    if(Luz==1024){
      digitalWrite(SalidaRele, LOW); // ACTIVA RELE
      EstadoRele = '0';
    }
    if(Luz<1024){
      digitalWrite(SalidaRele, HIGH); // DESACTIVA RELE, LOGICA NEGATIVA
      EstadoRele = '1';
    }
  } 

  if (RespuestaCliente.indexOf('/RELE=OFF') != -1) {
    Serial.println("APAGADO");
    digitalWrite(SalidaRele, LOW); // DESACTIVA RELE, LOGICA NEGATIVA
    EstadoRele = '0';
  }

  Valor_Luz = Luz;

  Serial.println("------------------------------------");
  Serial.print("Luz: "+ String(Luz));
  Client.add(ID_LUZ,Valor_Luz);
  Client.send();
  delay(5000);


  client.println("");                         
  client.println("");
  client.println("");
  client.println("");
  

  Serial.println("Enviando html");

  { client.print("   <html> <head> <meta http-equiv='refresh' content='3'> <meta name='viewport' content='width=device-width, user-scalable=no'>  ");}
  { client.print("   <title>Automata-Servidor-local</title><style> .estilos_body { background-color: rgb(20,21,38); justify-items: center;   ");}  
  { client.print("   font-family: monospace; margin: auto; width: 100%; height: 100%; max-width: 1024px; overflow: hidden;  ");}
  { client.print("   } h1 { color: rgb(255, 255, 255); font-size: 14px; } p { color: rgb(255, 255, 255); font-size: 32px;  ");}  
  { client.print("  text-align: center; }  n {color: rgb(255, 255, 255); font-size: 25px; text-align: center; } h2 { color: rgb(255,255,255); font-size: 50px; text-align: center; } .cont_temp { width: 280px;   ");}
 // Estilo boton 
 if (EstadoRele == '0') {
  { client.print("  height: 280px; background-color:  rgb(20,21,38); margin: 80px auto; position: relative; } .boton { color: rgb(0, 255, 76);    ");}  
  { client.print("  border: 3px solid rgb(0, 255, 76); position: absolute; right: 90px; top:  250px;  z-index: 3; width: 100px; height: 30px;   ");}      }

 if (EstadoRele == '1') {
  { client.print("  height: 280px; background-color:  rgb(20,21,38); margin: 80px auto; position: relative; } .boton { color: rgb(255, 0, 0);    ");}  
  { client.print("  border: 3px solid rgb(255, 0, 0); position: absolute; right: 90px; top:  250px;  z-index: 3; width: 100px; height: 30px;   ");}      }  
  
  { client.print("  border-radius: 30px; font-size:24px  ; text-decoration: none;  display: flex; align-items: center; justify-content: center;   ");}  
  { client.print("  } @media (min-width: 1030px) { .cont_temp { margin: 50px auto; } p { margin-top: 30px 0; font-size: 45px; } h1 { font-size: 28px;   ");}
  { client.print("  } .boton { top:  220px; right: 60px; width: 150px; height: 50px; } } @media (min-width: 1400px){ .cont_temp { margin: 150px auto;   ");}  
  { client.print("  } .boton { top:  280px; } } </style>   ");}
  { client.print("  </head> <body class='estilos_body' > <div style='display: flex; justify-content: space-between; padding: 10px 30px; '>   ");}  
  { client.print("  <h1>ECOLUX</h1> <h1>2023</h1>   ");}
  { client.print("  </div> <p>ECOLUX</p> <p>Control foco</p> <div class='cont_temp'>   ");} 
// barra circular 
  { client.print("  <div   style=' overflow: hidden; transform: rotate("+ String(barra) +"deg); width: 270px; height: 270px; border-radius: 50%;   ");}   
  { client.print("  position:absolute; z-index: 1; left:5px ; top: 5px;' > <div  style='background-color: rgb(39, 41, 73); width: 270px;   ");} 
  { client.print("  height: 135px' ></div> <div  style='background-color: rgb(255, 0, 0); width: 270px; height: 135px ' ></div>   ");} 
  { client.print("  </div> <div  style='  background-color:  rgb(20,21,38); width: 220px; height: 220px; position: absolute; left: 30px;    ");} 
  { client.print("  top: 30px; z-index: 1; border-radius: 50%;  ' ></div> <div  style='background-color:  rgb(20,21,38); width: 275px;    ");} 
  { client.print("  height: 135px; position: absolute; left: 2px; top: 140px; z-index: 2;  ' ></div>   ");} 
// Luz        
  { client.print("  <h2 style='position: absolute; center: 50px; top: 70px; z-index: 3;'>"+ String(Luz) +" AMP ");} 
//  Boton  
  if (EstadoRele == '0') {
  { client.print("  <a href='/RELE=0N' class='boton'  >ON</a></div> </body> </html>   ");}    }
  if (EstadoRele == '1') {
  { client.print("  <a href='/RELE=0FF' class='boton'  >OFF</a></div> </body> </html>   ");}    }
  
  client.println("");
 
  
  Serial.println("Html enviado.");
  Serial.println(" ");

  client.println("Connection:close");
  client.println();

  Serial.println("Conexion terminada");
  Serial.println(" ");
  digitalWrite(Led_cliente, LOW);

}


