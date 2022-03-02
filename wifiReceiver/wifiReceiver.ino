#include <WiFi.h>

String clientBuffer="";

const char *ssid = "organizacao12h";
const char *password = "@betocarrero12h";

WiFiServer wifiServer(8000);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600);
  //Serial2.println("iniciando");
  ConnectToWiFi();

  wifiServer.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  if (WiFi.status()==WL_CONNECTED){
        WiFiClient client = wifiServer.available();
      
        if(client){
            Serial.println("cliente conectado");
            while(client.connected()){
              if(client.available()){
                clientBuffer="";
                while (client.available()>0) {
                char c = client.read();
                clientBuffer.concat(c);
                Serial2.print(c);
                }
                delay(10);
                Serial.print("Mensagem Recebida: ");
                Serial.println(clientBuffer);
                //Serial2.println(clientBuffer);
              }
            }
            
            client.stop();
            Serial.println("Client disconnected");
        }  
  }else {
    Serial.println("conexão com wifi perdida... tentando novamente");
    ConnectToWiFi();
  }


  

}

void ConnectToWiFi(){
  //  WiFi.mode(WIFI_STA);
  Serial.print("Connecting to "); Serial.println(ssid);
  WiFi.begin(ssid, password);
 
    uint8_t i = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
    Serial.print('.');
    delay(500);
    if ((++i % 16) == 0)
    {
      Serial.println(F(" still trying to connect"));
    }
    } 
  Serial.print(F("Connected. My IP address is: "));
  Serial.println(WiFi.localIP());
  Serial2.println(WiFi.localIP());
}
