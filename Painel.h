#ifndef Painel_h
#define Painel_h

#include "Arduino.h"


class Painel
{
  public:
    Painel(int _OE, int _A, int _B, int _C, int _D, int _LAT);
	
	
	void spiInit();
	void latch();
	void enviarSPI(uint8_t var);
	void ativarLinha(char linha);
	void fillDisplay();
	void configPanel(int width,int heigth,int panelRows,int colors,int panelsBytesRow,int _muxdelay);
	void checkeredFlag();
	void ConnectToWiFi(char ssid,char password);
	void flushDisplay();
	void brightness(int var);
	void fillBufferRGB(bool R,bool G, bool B);
	void sendBuffer();
	void advertencia();
	void desclassificacao();
	void numero(int num, int p,bool R,bool G, bool B);
	void letra(char car, int p,bool R,bool G, bool B);
	void decodeMsg(String msg);
	void box();
	
	int width;
	int heigth;
	int panelRows;
	int colors;
	int panelsBytesRow;
	int row_buffer_size;
	int _brightness;
	int muxdelay;
	bool showBuffer;
	
	bool black[3]={false,false,false};
	bool white[3]={true,true,true};
	bool red[3]={true,false,false};
	bool green[3]={false,true,false};
	bool blue[3]={false,false,true};
	bool yellow[3]={true,true,false};
	bool cyan[3]={false,true,true};
	bool magenta[3]={true,false,true};
	
  //private:
	int P_OE;
	int P_A;
	int P_B;
	int P_C;
	int P_D;
	int P_LAT;	
	uint8_t A1_R_buffer[96]={}; //buffer de bytes para a linha A1 do painel;
	uint8_t A2_R_buffer[96]={}; //buffer de bytes para a linha A2 do painel;
	uint8_t B1_R_buffer[96]={}; //buffer de bytes para a linha B1 do painel;
	uint8_t B2_R_buffer[96]={}; //buffer de bytes para a linha B2 do painel;
	uint8_t C1_R_buffer[96]={}; //buffer de bytes para a linha C1 do painel;
	uint8_t C2_R_buffer[96]={}; //buffer de bytes para a linha C2 do painel;
	uint8_t D1_R_buffer[96]={}; //buffer de bytes para a linha D1 do painel;
	uint8_t D2_R_buffer[96]={}; //buffer de bytes para a linha D2 do painel;
	//linhas Green
	uint8_t A1_G_buffer[96]={}; //buffer de bytes para a linha A1 do painel;
	uint8_t A2_G_buffer[96]={}; //buffer de bytes para a linha A2 do painel;
	uint8_t B1_G_buffer[96]={}; //buffer de bytes para a linha B1 do painel;
	uint8_t B2_G_buffer[96]={}; //buffer de bytes para a linha B2 do painel;
	uint8_t C1_G_buffer[96]={}; //buffer de bytes para a linha C1 do painel;
	uint8_t C2_G_buffer[96]={}; //buffer de bytes para a linha C2 do painel;
	uint8_t D1_G_buffer[96]={}; //buffer de bytes para a linha D1 do painel;
	uint8_t D2_G_buffer[96]={}; //buffer de bytes para a linha D2 do painel;
	//linhas Blue
	uint8_t A1_B_buffer[96]={}; //buffer de bytes para a linha A1 do painel;
	uint8_t A2_B_buffer[96]={}; //buffer de bytes para a linha A2 do painel;
	uint8_t B1_B_buffer[96]={}; //buffer de bytes para a linha B1 do painel;
	uint8_t B2_B_buffer[96]={}; //buffer de bytes para a linha B2 do painel;
	uint8_t C1_B_buffer[96]={}; //buffer de bytes para a linha C1 do painel;
	uint8_t C2_B_buffer[96]={}; //buffer de bytes para a linha C2 do painel;
	uint8_t D1_B_buffer[96]={}; //buffer de bytes para a linha D1 do painel;
	uint8_t D2_B_buffer[96]={}; //buffer de bytes para a linha D2 do painel;
};

#endif