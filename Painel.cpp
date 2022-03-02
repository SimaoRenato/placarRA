#include "Arduino.h"
#include "Painel.h"
#include "bandeiras.h"
#include "fonte.h"
#include <SPI.h>
#include <WiFi.h>



Painel::Painel(int _OE, int _A, int _B, int _C, int _D, int _LAT){

	
	pinMode(_OE,OUTPUT);
	pinMode(_A,OUTPUT);
	pinMode(_B,OUTPUT);
	pinMode(_C,OUTPUT);
	pinMode(_D,OUTPUT);
	pinMode(_LAT,OUTPUT);
	
	P_OE=_OE;
	P_A=_A;
	P_B=_B;
	P_C=_C;
	P_D=_D;
	P_LAT=_LAT;
	
}
void Painel::configPanel(int _width,int _heigth,int _panelRows,int _colors,int _panelsBytesRow,int _muxdelay){
		
	width=_width;
	heigth=_heigth;
	panelRows=_panelRows;
	colors=_colors;
	panelsBytesRow=_panelsBytesRow;
	muxdelay=_muxdelay;
	
	row_buffer_size = (width*heigth)*panelsBytesRow;
}

void Painel::spiInit(){
	
		//Configuração da SPI para Arduino
			Serial.println("Configurando SPI Arduino");
			SPI.begin();
			SPI.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));
		
		//Configuração da SPI para ESP32
		/*
			Serial.println("Configurando SPI ESP32");
			SPI.begin(SPI_BUS_CLK,SPI_BUS_MISO,SPI_BUS_MOSI,SPI_BUS_SS);
			SPI.setFrequency(SPI_FREQUENCY);
			SPI.setDataMode(SPI_MODE0);
			SPI.setBitOrder(MSBFIRST);
		*/
	
	
}

void Painel::latch(){	//Sequencia de comandos para o shiftRegister aplicar os sinais aos LEDs 
	digitalWrite(P_OE,true);
	//analogWrite(P_OE,255);
	digitalWrite(P_LAT,true);	
	digitalWrite(P_LAT,false);
	//delayMicroseconds(muxdelay);
	//analogWrite(P_OE,_brightness);
	digitalWrite(P_OE,false);
}

void Painel::enviarSPI(uint8_t var){
	
	//#ifdef ESP32
	//SPI.write(var);
	//#endif
	
	//#ifdef ARDUINO
	SPI.transfer(var);
	//#endif
	
}

void Painel::ativarLinha(char linha){
	//delayMicroseconds(muxdelay);
	switch (linha) {
		case 'A':							//ativa linha A
			digitalWrite(P_A,false);
			digitalWrite(P_B,true);
			digitalWrite(P_C,true);
			digitalWrite(P_D,true);
			//delayMicroseconds(muxdelay);
			break;
		case 'B':							//ativa linha B
			digitalWrite(P_A,true);
			digitalWrite(P_B,false);
			digitalWrite(P_C,true);
			digitalWrite(P_D,true);
			//delayMicroseconds(muxdelay);
			break;
		case 'C':							//ativa linha C
			digitalWrite(P_A,true);
			digitalWrite(P_B,true);
			digitalWrite(P_C,false);
			digitalWrite(P_D,true);
			//delayMicroseconds(muxdelay);
			break;
		case 'D':							//ativa linha D
			digitalWrite(P_A,true);
			digitalWrite(P_B,true);
			digitalWrite(P_C,true);
			digitalWrite(P_D,false);
			//delayMicroseconds(muxdelay);
			break;
		case 'O':							//ativa todas as linhas
			digitalWrite(P_A,false);
			digitalWrite(P_B,false);
			digitalWrite(P_C,false);
			digitalWrite(P_D,false);
			//delayMicroseconds(muxdelay);
			break;
		case 'X':							//Desativa todas as linhas
			digitalWrite(P_A,true);
			digitalWrite(P_B,true);
			digitalWrite(P_C,true);
			digitalWrite(P_D,true);
			//delayMicroseconds(muxdelay);
			break;
		
	}
	//delayMicroseconds(muxdelay);
}

void Painel::fillDisplay(){
  ativarLinha('O');
  Serial.println("acendendo Display");
	for (int i=0; i<colors*panelRows;i++){
		for (int k=0;k<row_buffer_size;k++){	
			enviarSPI(0xff);
		}
	}
	latch();
}

void Painel::checkeredFlag(){
  Serial.println("Bandeira Quadriculada");
  ativarLinha('O');
  int b=0;
  bool c=false;	
	for (int i=0; i<colors*panelRows;i++){
		for (int k=0;k<row_buffer_size/4;k++){
			if(b%24==0){
				c=!c;
			}
			if (c){
				enviarSPI(0xff);
				enviarSPI(0xff);
				enviarSPI(0x00);
				enviarSPI(0x00);
			}else{
				enviarSPI(0x00);
				enviarSPI(0x00);
				enviarSPI(0xff);
				enviarSPI(0xff);
			}
			b++;
		}
	}
	latch();
}

void Painel::ConnectToWiFi(char ssid,char password){
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
}

void Painel::flushDisplay(){
	for (int i=0; i<colors*panelRows;i++){
		for (int k=0;k<row_buffer_size;k++){
			enviarSPI(0x00);
		}
	}
 latch();
}

void Painel::brightness(int var){
	_brightness=255-var;
	Serial.print("Brilho: ");
	Serial.println(_brightness);
	analogWrite(P_OE,_brightness);
}

void Painel::fillBufferRGB(bool R,bool G, bool B){
	
  for (int i=0;i<row_buffer_size;i++){
        A1_R_buffer[i]=0xFF*R;
        A2_R_buffer[i]=0xFF*R; 
        B1_R_buffer[i]=0xFF*R;
        B2_R_buffer[i]=0xFF*R;
        C1_R_buffer[i]=0xFF*R;
        C2_R_buffer[i]=0xFF*R;
        D1_R_buffer[i]=0xFF*R; 
        D2_R_buffer[i]=0xFF*R; 
        
        A1_G_buffer[i]=0xFF*G;
        A2_G_buffer[i]=0xFF*G; 
        B1_G_buffer[i]=0xFF*G;
        B2_G_buffer[i]=0xFF*G;
        C1_G_buffer[i]=0xFF*G;
        C2_G_buffer[i]=0xFF*G;
        D1_G_buffer[i]=0xFF*G; 
        D2_G_buffer[i]=0xFF*G; 
        
        A1_B_buffer[i]=0xFF*B;
        A2_B_buffer[i]=0xFF*B; 
        B1_B_buffer[i]=0xFF*B;
        B2_B_buffer[i]=0xFF*B;
        C1_B_buffer[i]=0xFF*B;
        C2_B_buffer[i]=0xFF*B;
        D1_B_buffer[i]=0xFF*B; 
        D2_B_buffer[i]=0xFF*B; 
  }     
}

void Painel::sendBuffer(){
   for (int i=0;i<row_buffer_size;i++){
     enviarSPI(A2_B_buffer[i]);
  }
  for (int i=0;i<row_buffer_size;i++){
     enviarSPI(A1_B_buffer[i]);
  }
  for (int i=0;i<row_buffer_size;i++){
     enviarSPI(A2_G_buffer[i]);
  }
  for (int i=0;i<row_buffer_size;i++){
     enviarSPI(A1_G_buffer[i]);
  }
  for (int i=0;i<row_buffer_size;i++){
     enviarSPI(A2_R_buffer[i]);
  }
  for (int i=0;i<row_buffer_size;i++){
     enviarSPI(A1_R_buffer[i]);
  }
  ativarLinha('X');
  latch();
  delayMicroseconds(muxdelay);
  ativarLinha('A');
  for (int i=0;i<row_buffer_size;i++){
     enviarSPI(B2_B_buffer[i]);
  }
  for (int i=0;i<row_buffer_size;i++){
     enviarSPI(B1_B_buffer[i]);
  }
  for (int i=0;i<row_buffer_size;i++){
     enviarSPI(B2_G_buffer[i]);
  }
  for (int i=0;i<row_buffer_size;i++){
     enviarSPI(B1_G_buffer[i]);
  }
  for (int i=0;i<row_buffer_size;i++){
     enviarSPI(B2_R_buffer[i]);
  }
  for (int i=0;i<row_buffer_size;i++){
     enviarSPI(B1_R_buffer[i]);
  }
  ativarLinha('X');
  latch();
  delayMicroseconds(muxdelay);
  ativarLinha('B');
  
  for (int i=0;i<row_buffer_size;i++){
     enviarSPI(C2_B_buffer[i]);
  }
  for (int i=0;i<row_buffer_size;i++){
     enviarSPI(C1_B_buffer[i]);
  }
  for (int i=0;i<row_buffer_size;i++){
     enviarSPI(C2_G_buffer[i]);
  }
  for (int i=0;i<row_buffer_size;i++){
     enviarSPI(C1_G_buffer[i]);
  }
  for (int i=0;i<row_buffer_size;i++){
     enviarSPI(C2_R_buffer[i]);
  }
  for (int i=0;i<row_buffer_size;i++){
     enviarSPI(C1_R_buffer[i]);
  }
 ativarLinha('X');
  latch();
  delayMicroseconds(muxdelay);
  ativarLinha('C');
  
  for (int i=0;i<row_buffer_size;i++){
     enviarSPI(D2_B_buffer[i]);
  }
  for (int i=0;i<row_buffer_size;i++){
     enviarSPI(D1_B_buffer[i]);
  }
  for (int i=0;i<row_buffer_size;i++){
     enviarSPI(D2_G_buffer[i]);
  }
  for (int i=0;i<row_buffer_size;i++){
     enviarSPI(D1_G_buffer[i]);
  }
  for (int i=0;i<row_buffer_size;i++){
     enviarSPI(D2_R_buffer[i]);
  }
  for (int i=0;i<row_buffer_size;i++){
     enviarSPI(D1_R_buffer[i]);
  }
  ativarLinha('X');
  latch();
  delayMicroseconds(muxdelay);
  ativarLinha('D');
}

void Painel::advertencia(){
   for (int i=0;i<8;i++){
    //painel 12
     A1_R_buffer[i]=A1_P12[i];
     A1_G_buffer[i]=A1_P12[i];
     A1_B_buffer[i]=A1_P12[i];
     A2_R_buffer[i]=A2_P12[i];
     A2_G_buffer[i]=A2_P12[i];
     A2_B_buffer[i]=A2_P12[i];
     
     B1_R_buffer[i]=B1_P12[i];
     B1_G_buffer[i]=B1_P12[i];
     B1_B_buffer[i]=B1_P12[i];
     B2_R_buffer[i]=B2_P12[i];
     B2_G_buffer[i]=B2_P12[i];
     B2_B_buffer[i]=B2_P12[i];
     
     C1_R_buffer[i]=C1_P12[i];
     C1_G_buffer[i]=C1_P12[i];
     C1_B_buffer[i]=C1_P12[i];
     C2_R_buffer[i]=C2_P12[i];
     C2_G_buffer[i]=C2_P12[i];
     C2_B_buffer[i]=C2_P12[i];

     D1_R_buffer[i]=D1_P12[i];
     D1_G_buffer[i]=D1_P12[i];
     D1_B_buffer[i]=D1_P12[i];
     D2_R_buffer[i]=D2_P12[i];
     D2_G_buffer[i]=D2_P12[i];
     D2_B_buffer[i]=D2_P12[i]; 

     //painel 9
     A1_R_buffer[i+24]=A1_P9[i];
     A1_G_buffer[i+24]=A1_P9[i];
     A1_B_buffer[i+24]=A1_P9[i];
     A2_R_buffer[i+24]=A2_P9[i];
     A2_G_buffer[i+24]=A2_P9[i];
     A2_B_buffer[i+24]=A2_P9[i];
     
     B1_R_buffer[i+24]=B1_P9[i];
     B1_G_buffer[i+24]=B1_P9[i];
     B1_B_buffer[i+24]=B1_P9[i];
     B2_R_buffer[i+24]=B2_P9[i];
     B2_G_buffer[i+24]=B2_P9[i];
     B2_B_buffer[i+24]=B2_P9[i];
     
     C1_R_buffer[i+24]=C1_P9[i];
     C1_G_buffer[i+24]=C1_P9[i];
     C1_B_buffer[i+24]=C1_P9[i];
     C2_R_buffer[i+24]=C2_P9[i];
     C2_G_buffer[i+24]=C2_P9[i];
     C2_B_buffer[i+24]=C2_P9[i];

     D1_R_buffer[i+24]=D1_P9[i];
     D1_G_buffer[i+24]=D1_P9[i];
     D1_B_buffer[i+24]=D1_P9[i];
     D2_R_buffer[i+24]=D2_P9[i];
     D2_G_buffer[i+24]=D2_P9[i];
     D2_B_buffer[i+24]=D2_P9[i]; 
     
     //painel 6
     A1_R_buffer[i+48]=A1_P6[i];
     A1_G_buffer[i+48]=A1_P6[i];
     A1_B_buffer[i+48]=A1_P6[i];
     A2_R_buffer[i+48]=A2_P6[i];
     A2_G_buffer[i+48]=A2_P6[i];
     A2_B_buffer[i+48]=A2_P6[i];
     
     B1_R_buffer[i+48]=B1_P6[i];
     B1_G_buffer[i+48]=B1_P6[i];
     B1_B_buffer[i+48]=B1_P6[i];
     B2_R_buffer[i+48]=B2_P6[i];
     B2_G_buffer[i+48]=B2_P6[i];
     B2_B_buffer[i+48]=B2_P6[i];
     
     C1_R_buffer[i+48]=C1_P6[i];
     C1_G_buffer[i+48]=C1_P6[i];
     C1_B_buffer[i+48]=C1_P6[i];
     C2_R_buffer[i+48]=C2_P6[i];
     C2_G_buffer[i+48]=C2_P6[i];
     C2_B_buffer[i+48]=C2_P6[i];

     D1_R_buffer[i+48]=D1_P6[i];
     D1_G_buffer[i+48]=D1_P6[i];
     D1_B_buffer[i+48]=D1_P6[i];
     D2_R_buffer[i+48]=D2_P6[i];
     D2_G_buffer[i+48]=D2_P6[i];
     D2_B_buffer[i+48]=D2_P6[i]; 

     //painel 3
     A1_R_buffer[i+72]=A1_P3[i];
     A1_G_buffer[i+72]=A1_P3[i];
     A1_B_buffer[i+72]=A1_P3[i];
     A2_R_buffer[i+72]=A2_P3[i];
     A2_G_buffer[i+72]=A2_P3[i];
     A2_B_buffer[i+72]=A2_P3[i];
     
     B1_R_buffer[i+72]=B1_P3[i];
     B1_G_buffer[i+72]=B1_P3[i];
     B1_B_buffer[i+72]=B1_P3[i];
     B2_R_buffer[i+72]=B2_P3[i];
     B2_G_buffer[i+72]=B2_P3[i];
     B2_B_buffer[i+72]=B2_P3[i];
     
     C1_R_buffer[i+72]=C1_P3[i];
     C1_G_buffer[i+72]=C1_P3[i];
     C1_B_buffer[i+72]=C1_P3[i];
     C2_R_buffer[i+72]=C2_P3[i];
     C2_G_buffer[i+72]=C2_P3[i];
     C2_B_buffer[i+72]=C2_P3[i];

     D1_R_buffer[i+72]=D1_P3[i];
     D1_G_buffer[i+72]=D1_P3[i];
     D1_B_buffer[i+72]=D1_P3[i];
     D2_R_buffer[i+72]=D2_P3[i];
     D2_G_buffer[i+72]=D2_P3[i];
     D2_B_buffer[i+72]=D2_P3[i]; 
   }
}

void Painel::desclassificacao(){
   for (int i=0;i<8;i++){
    //painel 12
     A1_R_buffer[i]=A1_P12_Desc[i];
     A1_G_buffer[i]=A1_P12_Desc[i];
     A1_B_buffer[i]=A1_P12_Desc[i];
     A2_R_buffer[i]=A2_P12_Desc[i];
     A2_G_buffer[i]=A2_P12_Desc[i];
     A2_B_buffer[i]=A2_P12_Desc[i];
     
     B1_R_buffer[i]=B1_P12_Desc[i];
     B1_G_buffer[i]=B1_P12_Desc[i];
     B1_B_buffer[i]=B1_P12_Desc[i];
     B2_R_buffer[i]=B2_P12_Desc[i];
     B2_G_buffer[i]=B2_P12_Desc[i];
     B2_B_buffer[i]=B2_P12_Desc[i];
     
     C1_R_buffer[i]=C1_P12_Desc[i];
     C1_G_buffer[i]=C1_P12_Desc[i];
     C1_B_buffer[i]=C1_P12_Desc[i];
     C2_R_buffer[i]=C2_P12_Desc[i];
     C2_G_buffer[i]=C2_P12_Desc[i];
     C2_B_buffer[i]=C2_P12_Desc[i];

     D1_R_buffer[i]=D1_P12_Desc[i];
     D1_G_buffer[i]=D1_P12_Desc[i];
     D1_B_buffer[i]=D1_P12_Desc[i];
     D2_R_buffer[i]=D2_P12_Desc[i];
     D2_G_buffer[i]=D2_P12_Desc[i];
     D2_B_buffer[i]=D2_P12_Desc[i]; 

     //painel 9
     A1_R_buffer[i+24]=A1_P9_Desc[i];
     A1_G_buffer[i+24]=A1_P9_Desc[i];
     A1_B_buffer[i+24]=A1_P9_Desc[i];
     A2_R_buffer[i+24]=A2_P9_Desc[i];
     A2_G_buffer[i+24]=A2_P9_Desc[i];
     A2_B_buffer[i+24]=A2_P9_Desc[i];
     
     B1_R_buffer[i+24]=B1_P9_Desc[i];
     B1_G_buffer[i+24]=B1_P9_Desc[i];
     B1_B_buffer[i+24]=B1_P9_Desc[i];
     B2_R_buffer[i+24]=B2_P9_Desc[i];
     B2_G_buffer[i+24]=B2_P9_Desc[i];
     B2_B_buffer[i+24]=B2_P9_Desc[i];
     
     C1_R_buffer[i+24]=C1_P9_Desc[i];
     C1_G_buffer[i+24]=C1_P9_Desc[i];
     C1_B_buffer[i+24]=C1_P9_Desc[i];
     C2_R_buffer[i+24]=C2_P9_Desc[i];
     C2_G_buffer[i+24]=C2_P9_Desc[i];
     C2_B_buffer[i+24]=C2_P9_Desc[i];

     D1_R_buffer[i+24]=D1_P9_Desc[i];
     D1_G_buffer[i+24]=D1_P9_Desc[i];
     D1_B_buffer[i+24]=D1_P9_Desc[i];
     D2_R_buffer[i+24]=D2_P9_Desc[i];
     D2_G_buffer[i+24]=D2_P9_Desc[i];
     D2_B_buffer[i+24]=D2_P9_Desc[i]; 
     
     //painel 6
     A1_R_buffer[i+48]=A1_P6_Desc[i];
     A1_G_buffer[i+48]=A1_P6_Desc[i];
     A1_B_buffer[i+48]=A1_P6_Desc[i];
     A2_R_buffer[i+48]=A2_P6_Desc[i];
     A2_G_buffer[i+48]=A2_P6_Desc[i];
     A2_B_buffer[i+48]=A2_P6_Desc[i];
     
     B1_R_buffer[i+48]=B1_P6_Desc[i];
     B1_G_buffer[i+48]=B1_P6_Desc[i];
     B1_B_buffer[i+48]=B1_P6_Desc[i];
     B2_R_buffer[i+48]=B2_P6_Desc[i];
     B2_G_buffer[i+48]=B2_P6_Desc[i];
     B2_B_buffer[i+48]=B2_P6_Desc[i];
     
     C1_R_buffer[i+48]=C1_P6_Desc[i];
     C1_G_buffer[i+48]=C1_P6_Desc[i];
     C1_B_buffer[i+48]=C1_P6_Desc[i];
     C2_R_buffer[i+48]=C2_P6_Desc[i];
     C2_G_buffer[i+48]=C2_P6_Desc[i];
     C2_B_buffer[i+48]=C2_P6_Desc[i];

     D1_R_buffer[i+48]=D1_P6_Desc[i];
     D1_G_buffer[i+48]=D1_P6_Desc[i];
     D1_B_buffer[i+48]=D1_P6_Desc[i];
     D2_R_buffer[i+48]=D2_P6_Desc[i];
     D2_G_buffer[i+48]=D2_P6_Desc[i];
     D2_B_buffer[i+48]=D2_P6_Desc[i]; 

     //painel 3
     A1_R_buffer[i+72]=A1_P3_Desc[i];
     A1_G_buffer[i+72]=A1_P3_Desc[i];
     A1_B_buffer[i+72]=A1_P3_Desc[i];
     A2_R_buffer[i+72]=A2_P3_Desc[i];
     A2_G_buffer[i+72]=A2_P3_Desc[i];
     A2_B_buffer[i+72]=A2_P3_Desc[i];
     
     B1_R_buffer[i+72]=B1_P3_Desc[i];
     B1_G_buffer[i+72]=B1_P3_Desc[i];
     B1_B_buffer[i+72]=B1_P3_Desc[i];
     B2_R_buffer[i+72]=B2_P3_Desc[i];
     B2_G_buffer[i+72]=B2_P3_Desc[i];
     B2_B_buffer[i+72]=B2_P3_Desc[i];
     
     C1_R_buffer[i+72]=C1_P3_Desc[i];
     C1_G_buffer[i+72]=C1_P3_Desc[i];
     C1_B_buffer[i+72]=C1_P3_Desc[i];
     C2_R_buffer[i+72]=C2_P3_Desc[i];
     C2_G_buffer[i+72]=C2_P3_Desc[i];
     C2_B_buffer[i+72]=C2_P3_Desc[i];

     D1_R_buffer[i+72]=D1_P3_Desc[i];
     D1_G_buffer[i+72]=D1_P3_Desc[i];
     D1_B_buffer[i+72]=D1_P3_Desc[i];
     D2_R_buffer[i+72]=D2_P3_Desc[i];
     D2_G_buffer[i+72]=D2_P3_Desc[i];
     D2_B_buffer[i+72]=D2_P3_Desc[i]; 
   }
}

void Painel::box(){
   for (int i=0;i<8;i++){
    //painel 12
     A1_R_buffer[i]=A1_P12_Box[i];
     A1_G_buffer[i]=A1_P12_Desc[i];
     A1_B_buffer[i]=A1_P12_Desc[i];
     A2_R_buffer[i]=A2_P12_Box[i];
     A2_G_buffer[i]=A2_P12_Desc[i];
     A2_B_buffer[i]=A2_P12_Desc[i];
     
     B1_R_buffer[i]=B1_P12_Box[i];
     B1_G_buffer[i]=B1_P12_Desc[i];
     B1_B_buffer[i]=B1_P12_Desc[i];
     B2_R_buffer[i]=B2_P12_Box[i];
     B2_G_buffer[i]=B2_P12_Desc[i];
     B2_B_buffer[i]=B2_P12_Desc[i];
     
     C1_R_buffer[i]=C1_P12_Box[i];
     C1_G_buffer[i]=C1_P12_Desc[i];
     C1_B_buffer[i]=C1_P12_Desc[i];
     C2_R_buffer[i]=C2_P12_Box[i];
     C2_G_buffer[i]=C2_P12_Desc[i];
     C2_B_buffer[i]=C2_P12_Desc[i];

     D1_R_buffer[i]=D1_P12_Box[i];
     D1_G_buffer[i]=D1_P12_Desc[i];
     D1_B_buffer[i]=D1_P12_Desc[i];
     D2_R_buffer[i]=D2_P12_Box[i];
     D2_G_buffer[i]=D2_P12_Desc[i];
     D2_B_buffer[i]=D2_P12_Desc[i]; 

     //painel 9
     A1_R_buffer[i+24]=A1_P9_Box[i];
     A1_G_buffer[i+24]=A1_P9_Desc[i];
     A1_B_buffer[i+24]=A1_P9_Desc[i];
     A2_R_buffer[i+24]=A2_P9_Box[i];
     A2_G_buffer[i+24]=A2_P9_Desc[i];
     A2_B_buffer[i+24]=A2_P9_Desc[i];
     
     B1_R_buffer[i+24]=B1_P9_Box[i];
     B1_G_buffer[i+24]=B1_P9_Desc[i];
     B1_B_buffer[i+24]=B1_P9_Desc[i];
     B2_R_buffer[i+24]=B2_P9_Box[i];
     B2_G_buffer[i+24]=B2_P9_Desc[i];
     B2_B_buffer[i+24]=B2_P9_Desc[i];
     
     C1_R_buffer[i+24]=C1_P9_Box[i];
     C1_G_buffer[i+24]=C1_P9_Desc[i];
     C1_B_buffer[i+24]=C1_P9_Desc[i];
     C2_R_buffer[i+24]=C2_P9_Box[i];
     C2_G_buffer[i+24]=C2_P9_Desc[i];
     C2_B_buffer[i+24]=C2_P9_Desc[i];

     D1_R_buffer[i+24]=D1_P9_Box[i];
     D1_G_buffer[i+24]=D1_P9_Desc[i];
     D1_B_buffer[i+24]=D1_P9_Desc[i];
     D2_R_buffer[i+24]=D2_P9_Box[i];
     D2_G_buffer[i+24]=D2_P9_Desc[i];
     D2_B_buffer[i+24]=D2_P9_Desc[i]; 
     
     //painel 6
     A1_R_buffer[i+48]=A1_P6_Box[i];
     A1_G_buffer[i+48]=A1_P6_Desc[i];
     A1_B_buffer[i+48]=A1_P6_Desc[i];
     A2_R_buffer[i+48]=A2_P6_Box[i];
     A2_G_buffer[i+48]=A2_P6_Desc[i];
     A2_B_buffer[i+48]=A2_P6_Desc[i];
     
     B1_R_buffer[i+48]=B1_P6_Box[i];
     B1_G_buffer[i+48]=B1_P6_Desc[i];
     B1_B_buffer[i+48]=B1_P6_Desc[i];
     B2_R_buffer[i+48]=B2_P6_Box[i];
     B2_G_buffer[i+48]=B2_P6_Desc[i];
     B2_B_buffer[i+48]=B2_P6_Desc[i];
     
     C1_R_buffer[i+48]=C1_P6_Box[i];
     C1_G_buffer[i+48]=C1_P6_Desc[i];
     C1_B_buffer[i+48]=C1_P6_Desc[i];
     C2_R_buffer[i+48]=C2_P6_Box[i];
     C2_G_buffer[i+48]=C2_P6_Desc[i];
     C2_B_buffer[i+48]=C2_P6_Desc[i];

     D1_R_buffer[i+48]=D1_P6_Box[i];
     D1_G_buffer[i+48]=D1_P6_Desc[i];
     D1_B_buffer[i+48]=D1_P6_Desc[i];
     D2_R_buffer[i+48]=D2_P6_Box[i];
     D2_G_buffer[i+48]=D2_P6_Desc[i];
     D2_B_buffer[i+48]=D2_P6_Desc[i]; 

     //painel 3
     A1_R_buffer[i+72]=A1_P3_Box[i];
     A1_G_buffer[i+72]=A1_P3_Desc[i];
     A1_B_buffer[i+72]=A1_P3_Desc[i];
     A2_R_buffer[i+72]=A2_P3_Box[i];
     A2_G_buffer[i+72]=A2_P3_Desc[i];
     A2_B_buffer[i+72]=A2_P3_Desc[i];
     
     B1_R_buffer[i+72]=B1_P3_Box[i];
     B1_G_buffer[i+72]=B1_P3_Desc[i];
     B1_B_buffer[i+72]=B1_P3_Desc[i];
     B2_R_buffer[i+72]=B2_P3_Box[i];
     B2_G_buffer[i+72]=B2_P3_Desc[i];
     B2_B_buffer[i+72]=B2_P3_Desc[i];
     
     C1_R_buffer[i+72]=C1_P3_Box[i];
     C1_G_buffer[i+72]=C1_P3_Desc[i];
     C1_B_buffer[i+72]=C1_P3_Desc[i];
     C2_R_buffer[i+72]=C2_P3_Box[i];
     C2_G_buffer[i+72]=C2_P3_Desc[i];
     C2_B_buffer[i+72]=C2_P3_Desc[i];

     D1_R_buffer[i+72]=D1_P3_Box[i];
     D1_G_buffer[i+72]=D1_P3_Desc[i];
     D1_B_buffer[i+72]=D1_P3_Desc[i];
     D2_R_buffer[i+72]=D2_P3_Box[i];
     D2_G_buffer[i+72]=D2_P3_Desc[i];
     D2_B_buffer[i+72]=D2_P3_Desc[i]; 
   }
}


void Painel::numero(int num, int p,bool R,bool G, bool B){
	
	
		uint8_t A1[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		uint8_t A2[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		uint8_t B1_[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		uint8_t B2[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		uint8_t C1[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		uint8_t C2[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		uint8_t D1[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		uint8_t D2[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	int i=0;
		
		switch(num){
			case 0:
				for (i=0;i<8;i++){
					A1[i]=A1_0[i];
					A2[i]=A2_0[i];
					B1_[i]=B1_0[i];
					B2[i]=B2_0[i];
					C1[i]=C1_0[i];
					C2[i]=C2_0[i];
					D1[i]=D1_0[i];
					D2[i]=D2_0[i];
				}
			break;
			case 1:
			for (i=0;i<8;i++){
					A1[i]=A1_1[i];
					A2[i]=A2_1[i];
					B1_[i]=B1_1[i];
					B2[i]=B2_1[i];
					C1[i]=C1_1[i];
					C2[i]=C2_1[i];
					D1[i]=D1_1[i];
					D2[i]=D2_1[i];
				}			
			break;
			case 2:
			for (i=0;i<8;i++){
					A1[i]=A1_2[i];
					A2[i]=A2_2[i];
					B1_[i]=B1_2[i];
					B2[i]=B2_2[i];
					C1[i]=C1_2[i];
					C2[i]=C2_2[i];
					D1[i]=D1_2[i];
					D2[i]=D2_2[i];
				}
			break;
			case 3:
			for (i=0;i<8;i++){
					A1[i]=A1_3[i];
					A2[i]=A2_3[i];
					B1_[i]=B1_3[i];
					B2[i]=B2_3[i];
					C1[i]=C1_3[i];
					C2[i]=C2_3[i];
					D1[i]=D1_3[i];
					D2[i]=D2_3[i];
				}			
			break;
			case 4:
			for (i=0;i<8;i++){
					A1[i]=A1_4[i];
					A2[i]=A2_4[i];
					B1_[i]=B1_4[i];
					B2[i]=B2_4[i];
					C1[i]=C1_4[i];
					C2[i]=C2_4[i];
					D1[i]=D1_4[i];
					D2[i]=D2_4[i];
				}			
			break;
			case 5:
			for (i=0;i<8;i++){
					A1[i]=A1_5[i];
					A2[i]=A2_5[i];
					B1_[i]=B1_5[i];
					B2[i]=B2_5[i];
					C1[i]=C1_5[i];
					C2[i]=C2_5[i];
					D1[i]=D1_5[i];
					D2[i]=D2_5[i];
				}			
			break;
			case 6:
			for (i=0;i<8;i++){
					A1[i]=A1_6[i];
					A2[i]=A2_6[i];
					B1_[i]=B1_6[i];
					B2[i]=B2_6[i];
					C1[i]=C1_6[i];
					C2[i]=C2_6[i];
					D1[i]=D1_6[i];
					D2[i]=D2_6[i];
				}			
			break;
			case 7:
			for (i=0;i<8;i++){
					A1[i]=A1_7[i];
					A2[i]=A2_7[i];
					B1_[i]=B1_7[i];
					B2[i]=B2_7[i];
					C1[i]=C1_7[i];
					C2[i]=C2_7[i];
					D1[i]=D1_7[i];
					D2[i]=D2_7[i];
				}			
			break;
			case 8:
			for (i=0;i<8;i++){
					A1[i]=A1_8[i];
					A2[i]=A2_8[i];
					B1_[i]=B1_8[i];
					B2[i]=B2_8[i];
					C1[i]=C1_8[i];
					C2[i]=C2_8[i];
					D1[i]=D1_8[i];
					D2[i]=D2_8[i];
				}			
			break;
			case 9:
			for (i=0;i<8;i++){
					A1[i]=A1_9[i];
					A2[i]=A2_9[i];
					B1_[i]=B1_9[i];
					B2[i]=B2_9[i];
					C1[i]=C1_9[i];
					C2[i]=C2_9[i];
					D1[i]=D1_9[i];
					D2[i]=D2_9[i];
				}			
			break;
		}
    
	for (i=0;i<8;i++){
		A1_R_buffer[96-(p*8)+i]=A1[i]*R;
		A1_G_buffer[96-(p*8)+i]=A1[i]*G;
		A1_B_buffer[96-(p*8)+i]=A1[i]*B;
		A2_R_buffer[96-(p*8)+i]=A2[i]*R;
		A2_G_buffer[96-(p*8)+i]=A2[i]*G;
		A2_B_buffer[96-(p*8)+i]=A2[i]*B;
     
		B1_R_buffer[96-(p*8)+i]=B1_[i]*R;
		B1_G_buffer[96-(p*8)+i]=B1_[i]*G;
		B1_B_buffer[96-(p*8)+i]=B1_[i]*B;
		B2_R_buffer[96-(p*8)+i]=B2[i]*R;
		B2_G_buffer[96-(p*8)+i]=B2[i]*G;
		B2_B_buffer[96-(p*8)+i]=B2[i]*B;
     
		C1_R_buffer[96-(p*8)+i]=C1[i]*R;
		C1_G_buffer[96-(p*8)+i]=C1[i]*G;
		C1_B_buffer[96-(p*8)+i]=C1[i]*B;
		C2_R_buffer[96-(p*8)+i]=C2[i]*R;
		C2_G_buffer[96-(p*8)+i]=C2[i]*G;
		C2_B_buffer[96-(p*8)+i]=C2[i]*B;

		D1_R_buffer[96-(p*8)+i]=D1[i]*R;
		D1_G_buffer[96-(p*8)+i]=D1[i]*G;
		D1_B_buffer[96-(p*8)+i]=D1[i]*B;
		D2_R_buffer[96-(p*8)+i]=D2[i]*R;
		D2_G_buffer[96-(p*8)+i]=D2[i]*G;
		D2_B_buffer[96-(p*8)+i]=D2[i]*B; 
	}
	
	
  /*
  painel.ativarLinha('A');
  for (i=0;i<6;i++){
     painel.enviarSPI(A2[i]);
  }
  for(i=0;i<90;i++){
    painel.enviarSPI(0x00);
  }
  for (i=0;i<6;i++){
     painel.enviarSPI(A1[i]);
  }
  
  painel.latch();
   painel.flushDisplay();
  
  painel.ativarLinha('B');
  //delay(10);
  for (i=0;i<6;i++){
     painel.enviarSPI(B2[i]);
  }
  for(i=0;i<90;i++){
    painel.enviarSPI(0x00);
  }
  for (i=0;i<6;i++){
     painel.enviarSPI(B1_[i]);
  }
  painel.latch();
   painel.flushDisplay();
  painel.ativarLinha('C');
  for (i=0;i<6;i++){
     painel.enviarSPI(C2[i]);
  }
  for(i=0;i<90;i++){
    painel.enviarSPI(0x00);
  }
  for (i=0;i<6;i++){
     painel.enviarSPI(C1[i]);
  }
  painel.latch();
   painel.flushDisplay();
  painel.ativarLinha('D');
  for (i=0;i<6;i++){
     painel.enviarSPI(D2[i]);
  }
  for(i=0;i<90;i++){
    painel.enviarSPI(0x00);
  }
  for (i=0;i<6;i++){
     painel.enviarSPI(D1[i]);
  }
  painel.latch();
   painel.flushDisplay();*/
}

void Painel::letra(char car, int p,bool R,bool G, bool B){
		
		uint8_t A1[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		uint8_t A2[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		uint8_t B1_[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		uint8_t B2[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		uint8_t C1[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		uint8_t C2[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		uint8_t D1[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		uint8_t D2[9]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	int i=0;
	
	switch (car){
		case 'B':
			for (i=0;i<8;i++){
						A1[i]=A1_B[i];
						A2[i]=A2_B[i];
						B1_[i]=B1_B[i];
						B2[i]=B2_B[i];
						C1[i]=C1_B[i];
						C2[i]=C2_B[i];
						D1[i]=D1_B[i];
						D2[i]=D2_B[i];
			}
		break;
		
		case 'C':
			for (i=0;i<8;i++){
						A1[i]=A1_C[i];
						A2[i]=A2_C[i];
						B1_[i]=B1_C[i];
						B2[i]=B2_C[i];
						C1[i]=C1_C[i];
						C2[i]=C2_C[i];
						D1[i]=D1_C[i];
						D2[i]=D2_C[i];
			}
		break;
		case 'D':
			for (i=0;i<8;i++){
						A1[i]=A1_D[i];
						A2[i]=A2_D[i];
						B1_[i]=B1_D[i];
						B2[i]=B2_D[i];
						C1[i]=C1_D[i];
						C2[i]=C2_D[i];
						D1[i]=D1_D[i];
						D2[i]=D2_D[i];
			}
		break;
		case 'E':
			for (i=0;i<8;i++){
						A1[i]=A1_E[i];
						A2[i]=A2_E[i];
						B1_[i]=B1_E[i];
						B2[i]=B2_E[i];
						C1[i]=C1_E[i];
						C2[i]=C2_E[i];
						D1[i]=D1_E[i];
						D2[i]=D2_E[i];
			}
		break;
		case 'K':
			for (i=0;i<8;i++){
						A1[i]=A1_K[i];
						A2[i]=A2_K[i];
						B1_[i]=B1_K[i];
						B2[i]=B2_K[i];
						C1[i]=C1_K[i];
						C2[i]=C2_K[i];
						D1[i]=D1_K[i];
						D2[i]=D2_K[i];
			}
		break;
		
		case 'O':
			for (i=0;i<8;i++){
						A1[i]=A1_O[i];
						A2[i]=A2_O[i];
						B1_[i]=B1_O[i];
						B2[i]=B2_O[i];
						C1[i]=C1_O[i];
						C2[i]=C2_O[i];
						D1[i]=D1_O[i];
						D2[i]=D2_O[i];
			}
		break;
		
		case 'S':
			for (i=0;i<8;i++){
						A1[i]=A1_S[i];
						A2[i]=A2_S[i];
						B1_[i]=B1_S[i];
						B2[i]=B2_S[i];
						C1[i]=C1_S[i];
						C2[i]=C2_S[i];
						D1[i]=D1_S[i];
						D2[i]=D2_S[i];
			}
		break;
		
		case 'V':
			for (i=0;i<8;i++){
						A1[i]=A1_V[i];
						A2[i]=A2_V[i];
						B1_[i]=B1_V[i];
						B2[i]=B2_V[i];
						C1[i]=C1_V[i];
						C2[i]=C2_V[i];
						D1[i]=D1_V[i];
						D2[i]=D2_V[i];
			}
		break;
		
		case 'X':
			for (i=0;i<8;i++){
						A1[i]=A1_X[i];
						A2[i]=A2_X[i];
						B1_[i]=B1_X[i];
						B2[i]=B2_X[i];
						C1[i]=C1_X[i];
						C2[i]=C2_X[i];
						D1[i]=D1_X[i];
						D2[i]=D2_X[i];
			}
		break;
		
		case 's':
			for (i=0;i<8;i++){
						A1[i]=A1_s[i];
						A2[i]=A2_s[i];
						B1_[i]=B1_s[i];
						B2[i]=B2_s[i];
						C1[i]=C1_s[i];
						C2[i]=C2_s[i];
						D1[i]=D1_s[i];
						D2[i]=D2_s[i];
			}
		break;
		
		case 'v':
			for (i=0;i<8;i++){
						A1[i]=A1_v[i];
						A2[i]=A2_v[i];
						B1_[i]=B1_v[i];
						B2[i]=B2_v[i];
						C1[i]=C1_v[i];
						C2[i]=C2_v[i];
						D1[i]=D1_v[i];
						D2[i]=D2_v[i];
			}
		break;
		
	}
	
	for (i=0;i<8;i++){
		A1_R_buffer[96-(p*8)+i]=A1[i]*R;
		A1_G_buffer[96-(p*8)+i]=A1[i]*G;
		A1_B_buffer[96-(p*8)+i]=A1[i]*B;
		A2_R_buffer[96-(p*8)+i]=A2[i]*R;
		A2_G_buffer[96-(p*8)+i]=A2[i]*G;
		A2_B_buffer[96-(p*8)+i]=A2[i]*B;
     
		B1_R_buffer[96-(p*8)+i]=B1_[i]*R;
		B1_G_buffer[96-(p*8)+i]=B1_[i]*G;
		B1_B_buffer[96-(p*8)+i]=B1_[i]*B;
		B2_R_buffer[96-(p*8)+i]=B2[i]*R;
		B2_G_buffer[96-(p*8)+i]=B2[i]*G;
		B2_B_buffer[96-(p*8)+i]=B2[i]*B;
     
		C1_R_buffer[96-(p*8)+i]=C1[i]*R;
		C1_G_buffer[96-(p*8)+i]=C1[i]*G;
		C1_B_buffer[96-(p*8)+i]=C1[i]*B;
		C2_R_buffer[96-(p*8)+i]=C2[i]*R;
		C2_G_buffer[96-(p*8)+i]=C2[i]*G;
		C2_B_buffer[96-(p*8)+i]=C2[i]*B;

		D1_R_buffer[96-(p*8)+i]=D1[i]*R;
		D1_G_buffer[96-(p*8)+i]=D1[i]*G;
		D1_B_buffer[96-(p*8)+i]=D1[i]*B;
		D2_R_buffer[96-(p*8)+i]=D2[i]*R;
		D2_G_buffer[96-(p*8)+i]=D2[i]*G;
		D2_B_buffer[96-(p*8)+i]=D2[i]*B; 
	}
	
}

void Painel::decodeMsg(String msg){
	Serial.print("decodificando mensagem: ");
	Serial.println(msg);
  int kart[3]={};
  int pun[2]={};
  char punType;
  int k=0;
  //Serial.print("a mensagem é: ");
  //Serial.println(msg);
  
  int R=0;
  int G=1;
  int B=2;
  
  if (msg.equals("redFlag")){								//bandeira vermelha
	showBuffer=false;
	ativarLinha('X');
    Serial.println("Bandeira Vermelha");
    fillBufferRGB(true,false,false);
	showBuffer=true;
  }else if (msg.equals("checkeredFlag")){					//bandeira quadriculada
	showBuffer=false;
	ativarLinha('X');
    Serial.println("Bandeira Quadriculada");
    checkeredFlag();
	showBuffer=false;
  }else if (msg.equals("whiteFlag")){						//bandeira branca
	showBuffer=false;
	ativarLinha('X');
    Serial.println("Bandeira Branca");
    fillBufferRGB(true,true,true);
	showBuffer=false;
	showBuffer=true;
  }else if (msg.equals("yellowFlag")){						//bandeira amarela
	showBuffer=false;
	ativarLinha('X');
    Serial.println("Bandeira Amarela");
    fillBufferRGB(true,true,false);
	showBuffer=true;
  }else if (msg[0]=='a'&& msg[1]=='d'&& msg[2]=='v'){  		//advertencia para kart
	showBuffer=false;
	ativarLinha('X');
    Serial.print("advertência para o kart: ");
    kart[0]=msg[4]-48;
    kart[1]=msg[5]-48;
    kart[2]=msg[6]-48;
  
    //pun[0]=msg[9]-48;
    //pun[1]=msg[10]-48;
    //punType=msg[8];
    Serial.print(kart[0]);Serial.print(kart[1]);Serial.print(kart[2]);
    Serial.print(" -> ");
    Serial.print(pun[0]);Serial.print(pun[1]);Serial.print(punType);
	fillBufferRGB(false,false,false);
    advertencia();
    letra('K',2,white[R],white[G],white[B]);
    numero(kart[0],5,white[R],white[G],white[B]);
    numero(kart[1],8,white[R],white[G],white[B]);
    numero(kart[2],11,white[R],white[G],white[B]);
	showBuffer=true;
  }else if (msg[0]=='p'&& msg[1]=='u'&& msg[2]=='n'){		//punição para kart
	showBuffer=false;
	ativarLinha('X');
    Serial.print("punição para o kart: ");
    kart[0]=msg[4]-48;
    kart[1]=msg[5]-48;
    kart[2]=msg[6]-48;
  
    pun[0]=msg[9]-48;
    pun[1]=msg[10]-48;
    punType=msg[8];
    Serial.print(kart[0]);Serial.print(kart[1]);Serial.print(kart[2]);
    Serial.print(" -> ");
    Serial.print(pun[0]);Serial.print(pun[1]);Serial.print(punType);
	fillBufferRGB(false,false,false);
    advertencia();
    letra('K',2,yellow[R],yellow[G],yellow[B]);
    numero(kart[0],5,yellow[R],yellow[G],yellow[B]);
    numero(kart[1],8,yellow[R],yellow[G],yellow[B]);
    numero(kart[2],11,yellow[R],yellow[G],yellow[B]);
    letra(punType,10,yellow[R],yellow[G],yellow[B]);
    numero(pun[0],4,yellow[R],yellow[G],yellow[B]);
    numero(pun[1],7,yellow[R],yellow[G],yellow[B]);
	showBuffer=true;
  }else if (msg[0]=='d'&& msg[1]=='e'&& msg[2]=='s'){			//desclassificacao de kart
	showBuffer=false;
	ativarLinha('X');
    Serial.print("Desclassificação para o kart: ");
    kart[0]=msg[4]-48;
    kart[1]=msg[5]-48;
    kart[2]=msg[6]-48;
    Serial.print(kart[0]);Serial.print(kart[1]);Serial.print(kart[2]);
    Serial.print(" -> ");
    Serial.print(pun[0]);Serial.print(pun[1]);Serial.print(punType);
	fillBufferRGB(false,false,false);
    desclassificacao();
    letra('K',2,red[R],red[G],red[B]);
    numero(kart[0],5,red[R],red[G],red[B]);
    numero(kart[1],8,red[R],red[G],red[B]);
    numero(kart[2],11,red[R],red[G],red[B]);
    letra('D',1,red[R],red[G],red[B]);
	letra('E',4,red[R],red[G],red[B]);
	letra('S',7,red[R],red[G],red[B]);
	letra('C',10,red[R],red[G],red[B]);
	showBuffer=true;
  }else if (msg[0]=='b'&& msg[1]=='o'&& msg[2]=='x'){	//chamada de box
	showBuffer=false;
	ativarLinha('X');
    Serial.print("Box para o kart: ");
    kart[0]=msg[4]-48;
    kart[1]=msg[5]-48;
    kart[2]=msg[6]-48;
    Serial.print(kart[0]);Serial.print(kart[1]);Serial.print(kart[2]);
	fillBufferRGB(false,false,false);
    box();
    letra('K',2,red[R],red[G],red[B]);
    numero(kart[0],5,red[R],red[G],red[B]);
    numero(kart[1],8,red[R],red[G],red[B]);
    numero(kart[2],11,red[R],red[G],red[B]);
	letra('B',4,red[R],red[G],red[B]);
	letra('O',7,red[R],red[G],red[B]);
	letra('X',10,red[R],red[G],red[B]);
	showBuffer=true;
  
  
    
  }else if (msg.equals("OFF")){							//apagar painel
	  showBuffer=false;
	  ativarLinha('X');
	  Serial.println("apagando painel");
	  
  }else if (msg[0]=='m'&& msg[1]=='u'&& msg[2]=='x'){
		kart[0]=msg[4]-48;
		kart[1]=msg[5]-48;
		kart[2]=msg[6]-48;
		muxdelay=kart[0]*100+kart[1]*10+kart[2];
		Serial.print("delay = ");
		Serial.println(muxdelay);
    
  }else if (msg.equals("greenFlag")){  					//aciona bandeira Verde
	  showBuffer=false;
	  ativarLinha('X');
    Serial.println("Bandeira verde");
    fillBufferRGB(false,true,false);
	showBuffer=true;
  }else if (msg.equals("blueFlag")){					//aciona bandeira azul
	  showBuffer=false;
	  ativarLinha('X');
    Serial.println("Bandeira Azul");
    fillBufferRGB(false,false,true);
	showBuffer=true;
  }else{												//não reconheceu nenhuma mensagem
	  Serial.println("entrou no else");
	  
  }  
}
