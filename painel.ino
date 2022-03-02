#include <WiFi.h>
#include <SPI.h>
//#include "SPI.h"
#include "bandeiras.h"
#include "fonte.h"
#include "painel.h"

const char *ssid = "RFSimao";
const char *password = "largaessevicio";

String	bufferSerial="";
String  bufferSerial2="";

#define R 0
#define G 1
#define B 2

/*
//Definições para ESP32

//Definições da SPI
#define SPI_FREQUENCY 20000000
#define SPI_BUS_CLK   	14  //Clock de comando do painel
#define SPI_BUS_MOSI  	13	//Sinal de saída de dados
#define SPI_BUS_MISO  	12
#define SPI_BUS_SS    	4

#define P_LAT         	22
#define P_A           	19
#define P_B           	23
#define P_C           	18
#define P_D           	5
#define P_OE          	16  //RX2

*/


//Definições para ARDUINO
#define P_LAT           7
#define P_A             6
#define P_B             5
#define P_C             4
#define P_D             3
#define P_OE            8   




#define matrix_width  32
#define matrix_height 16
#define width         3
#define heigth        4

#define scanPattern   4
#define panelRows     2
#define colors        3
#define panelsBytesRow  8
#define muxdelay 1  //delay em microssegundos para mudança de linhas


Painel painel(P_OE,P_A,P_B,P_C,P_D,P_LAT);

void setup() {
	Serial.begin(9600);
  Serial2.begin(9600);
  painel.configPanel(width,heigth,panelRows,colors,panelsBytesRow,muxdelay);
  painel.spiInit();          //configura a porta SPI
  
  
	Serial.print("Tamanho unitário do buffer: ");
	Serial.println(painel.row_buffer_size);
	Serial.print("Quantidade total de cores: ");
	Serial.println(colors);
	Serial.print("Quantidade de linhas: ");
	Serial.println(panelRows);
	Serial.print("Quantidade total de bytes: ");
	Serial.println(painel.row_buffer_size*colors*panelRows);

	//painel.brightness(1);
  digitalWrite(P_OE,true);
  
	painel.ativarLinha('X');         //Desativa as saídas do painel para não exibir lixo enquanto se inicia
	painel.flushDisplay();   			//Zera todos os bytes dos ShiftRegisters do painel
  digitalWrite(P_OE,false);
	//painel.brightness(255);
 
	// ConnectToWiFi(ssid,password);			//Inicia a conexão com a rede wifi
  /*painel.fillBufferRGB(painel.black[R],painel.black[G],painel.black[B]);
	painel.advertencia();
  painel.letra('K',1,painel.yellow[R],painel.yellow[G],painel.yellow[B]);
  painel.numero(0,4,painel.cyan[R],painel.cyan[G],painel.cyan[B]);
  painel.numero(7,7,painel.magenta[R],painel.magenta[G],painel.magenta[B]);
  painel.numero(7,10,painel.blue[R],painel.blue[G],painel.blue[B]);*/
}

void loop() {
  // put your main code here, to run repeatedly:

 //painel.fillDisplay();
 //painel.patternTest();
 //painel.checkeredFlag();
 //advertencia(10,10);
 //fillyellow();
 //delay(1000);


// for (int n=0;n<10;n++){
  //int w=0;
	//while(w<100){
	  //numero(0,0,false,false,false);
	  //delay(1000);
	  // painel.flushDisplay();
   //w++;
	//}
 //}
 //painel.flushDisplay();
 //delay(500);
 if(painel.showBuffer){
      painel.sendBuffer();
 }
}


//***************************************************************************************************

void serialEvent() {
  // Enquanto houverem bytes disponíveis;
  bufferSerial="";
  char c;
  while (Serial.available()>0) {
    c = Serial.read(); // Lê byte do buffer serial;
    if (c!='\n'){
      if(c!='\r'){
        bufferSerial.concat(c);  
      }
    }
    delay(10);
  }
  Serial.print("mensagem recebida na serial 1: ");
  Serial.println(bufferSerial);
  painel.decodeMsg(bufferSerial);
}

void serialEvent2() {
  // Enquanto houverem bytes disponíveis;
  bufferSerial2="";
  char c;
  while (Serial2.available()>0) {
    c = Serial2.read(); // Lê byte do buffer serial;
    if (c!='\n'){
      if(c!='\r'){
        bufferSerial2.concat(c);  
      }
    }
    delay(10);
  }
  Serial.print("mensagem recebida na serial 2: ");
  Serial.println(bufferSerial2);
  painel.decodeMsg(bufferSerial2);
}
