#include <SPI.h>
#include <Ethernet.h>

// network configuration.  gateway and subnet are optional.

 // the media access control (ethernet hardware) address for the shield:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };  
//the IP address for the shield:
byte ip[] = { 192, 168, 50, 10 };    
// the router's gateway address:
byte gateway[] = { 192, 168, 50, 1 };
// the subnet:
byte subnet[] = { 255, 255, 255, 0 };

// telnet defaults to port 23
EthernetServer server = EthernetServer(5000);

void setup() {
  // initialize the ethernet device
  Ethernet.begin(mac, ip, gateway, subnet);

  // start listening for clients
  server.begin();

  // Inicializa a comunicação serial
  Serial.begin(9600);
}

void loop() {
  // Aguarda a conexão do cliente
  EthernetClient client = server.available();
  if (client) {
    Serial.println("Cliente conectado");

    while (client.connected()) {
      // Verifica se há dados na Serial
      if (Serial.available()) {
        // Lê os dados da Serial
        char c = Serial.read();
        
        // Envia os dados para o cliente TCP
        client.print(c);
      }

      // Verifica se há dados no cliente TCP
      if (client.available()) {
        // Lê os dados do cliente TCP
        char c = client.read();
        
        // Faça algo com os dados recebidos, por exemplo, imprimir no Serial Monitor
        Serial.print(c);
      }
    }

    // Fecha a conexão com o cliente
    client.stop();
    Serial.println("Cliente desconectado");
  }
}