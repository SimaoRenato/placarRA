const uint8_t blank_buffer[96]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//bytes 0 a 7
								0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//bytes 8 a 15
								0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//bytes 15 a 23
								0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//bytes 24 a 31
								0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//bytes 32 a 39
								0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//bytes 40 a 47
								0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//bytes 48 a 55 
								0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//bytes 56 a 63
								0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//bytes 64 a 71
								0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//bytes 72 a 79
								0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//bytes 80 a 88
								0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};	//bytes 89 a 95
const uint8_t fill_buffer[96]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,		//bytes 0 a 7
								0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,	//bytes 8 a 15
								0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,	//bytes 15 a 23
								0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,	//bytes 24 a 31
								0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,	//bytes 32 a 39
								0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,	//bytes 40 a 47
								0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,	//bytes 48 a 55 
								0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,	//bytes 56 a 63
								0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,	//bytes 64 a 71
								0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,	//bytes 72 a 79
								0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,	//bytes 80 a 88
								0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};	//bytes 89 a 95


//Bandeira de Advertência

//painel 3

const uint8_t D2_P3[8]={0x8F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF3};
const uint8_t C2_P3[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x13};
const uint8_t B2_P3[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x17};
const uint8_t A2_P3[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x17};
const uint8_t D1_P3[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x30,0xFF};
const uint8_t C1_P3[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x30,0xFF};
const uint8_t B1_P3[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x71,0xFF};
const uint8_t A1_P3[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x71,0xFF};


//painel 6

const uint8_t D2_P6[8]={0x88,0x00,0x00,0x00,0x00,0x03,0xFF,0xFF};
const uint8_t C2_P6[8]={0x88,0x00,0x00,0x00,0x00,0x03,0xFF,0xFF};
const uint8_t B2_P6[8]={0x88,0x00,0x00,0x00,0x00,0x17,0xFF,0xFF};
const uint8_t A2_P6[8]={0x88,0x00,0x00,0x00,0x00,0x17,0xFF,0xFF};
const uint8_t D1_P6[8]={0x88,0x00,0x00,0x00,0x30,0xFF,0xFF,0xFF};
const uint8_t C1_P6[8]={0x88,0x00,0x00,0x00,0x30,0xFF,0xFF,0xFF};
const uint8_t B1_P6[8]={0x88,0x00,0x00,0x00,0x71,0xFF,0xFF,0xFF};
const uint8_t A1_P6[8]={0x88,0x00,0x00,0x00,0x71,0xFF,0xFF,0xFF};


//painel 9

const uint8_t D2_P9[8]={0x88,0x00,0x00,0x03,0xFF,0xFF,0xFF,0xFF};
const uint8_t C2_P9[8]={0x88,0x00,0x00,0x03,0xFF,0xFF,0xFF,0xFF};
const uint8_t B2_P9[8]={0x88,0x00,0x00,0x17,0xFF,0xFF,0xFF,0xFF};
const uint8_t A2_P9[8]={0x88,0x00,0x00,0x17,0xFF,0xFF,0xFF,0xFF};
const uint8_t D1_P9[8]={0x88,0x00,0x30,0xFF,0xFF,0xFF,0xFF,0xFF};
const uint8_t C1_P9[8]={0x88,0x00,0x30,0xFF,0xFF,0xFF,0xFF,0xFF};
const uint8_t B1_P9[8]={0x88,0x00,0x71,0xFF,0xFF,0xFF,0xFF,0xFF};
const uint8_t A1_P9[8]={0x88,0x00,0x71,0xFF,0xFF,0xFF,0xFF,0xFF};



//painel 12

const uint8_t D2_P12[8]={0x88,0x03,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
const uint8_t C2_P12[8]={0x88,0x03,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
const uint8_t B2_P12[8]={0x88,0x17,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
const uint8_t A2_P12[8]={0x88,0x17,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
const uint8_t D1_P12[8]={0xB8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
const uint8_t C1_P12[8]={0xB8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
const uint8_t B1_P12[8]={0xF9,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
const uint8_t A1_P12[8]={0xF9,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};



//Bandeira de Desclassificação

//painel 3
const uint8_t D2_P3_Desc[8]={0x8F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF1};
const uint8_t C2_P3_Desc[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t B2_P3_Desc[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t A2_P3_Desc[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t D1_P3_Desc[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t C1_P3_Desc[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t B1_P3_Desc[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t A1_P3_Desc[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};

//painel 6

const uint8_t D2_P6_Desc[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t C2_P6_Desc[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t B2_P6_Desc[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t A2_P6_Desc[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t D1_P6_Desc[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t C1_P6_Desc[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t B1_P6_Desc[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t A1_P6_Desc[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};

//painel 9

const uint8_t D2_P9_Desc[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t C2_P9_Desc[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t B2_P9_Desc[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t A2_P9_Desc[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t D1_P9_Desc[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t C1_P9_Desc[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t B1_P9_Desc[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t A1_P9_Desc[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};

//painel 12

const uint8_t D2_P12_Desc[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t C2_P12_Desc[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t B2_P12_Desc[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t A2_P12_Desc[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t D1_P12_Desc[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t C1_P12_Desc[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t B1_P12_Desc[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t A1_P12_Desc[8]={0xF8,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x1F};



//bandeira de box

//painel 3


const uint8_t D2_P3_Box[8]={0x8F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF1};
const uint8_t C2_P3_Box[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t B2_P3_Box[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t A2_P3_Box[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t D1_P3_Box[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t C1_P3_Box[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t B1_P3_Box[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t A1_P3_Box[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};

//painel 6


const uint8_t D2_P6_Box[8]={0x88,0x00,0x00,0x03,0xC0,0x00,0x00,0x11};
const uint8_t C2_P6_Box[8]={0x88,0x00,0x00,0x0F,0xF0,0x00,0x00,0x11};
const uint8_t B2_P6_Box[8]={0x88,0x00,0x30,0x0F,0xF0,0x0C,0x00,0x11};
const uint8_t A2_P6_Box[8]={0x88,0x00,0x70,0x0F,0xF0,0x0E,0x00,0x11};
const uint8_t D1_P6_Box[8]={0x88,0x07,0xFF,0xFF,0xFF,0xFF,0xE0,0x11};
const uint8_t C1_P6_Box[8]={0x88,0x17,0xFF,0xFF,0xFF,0xFF,0xE8,0x11};
const uint8_t B1_P6_Box[8]={0x88,0x3F,0xFF,0xFF,0xFF,0xFF,0xFC,0x11};
const uint8_t A1_P6_Box[8]={0x88,0x3F,0xFF,0xFF,0xFF,0xFF,0xFC,0x11};

//painel 9


const uint8_t D2_P9_Box[8]={0x88,0xF3,0xFF,0xFF,0xFF,0xFF,0xCF,0x11};
const uint8_t C2_P9_Box[8]={0x88,0xF3,0xFF,0xFF,0xFF,0xFF,0xCF,0x11};
const uint8_t B2_P9_Box[8]={0x88,0x71,0xFF,0xFF,0xFF,0xFF,0x8E,0x11};
const uint8_t A2_P9_Box[8]={0x88,0x70,0xFF,0xFF,0xFF,0xFF,0x0E,0x11};
const uint8_t D1_P9_Box[8]={0x88,0x00,0x07,0xF0,0x0F,0xE0,0x00,0x11};
const uint8_t C1_P9_Box[8]={0x88,0x00,0x03,0xF0,0x0F,0xC0,0x00,0x11};
const uint8_t B1_P9_Box[8]={0x88,0x00,0x00,0xF0,0x0F,0x00,0x00,0x11};
const uint8_t A1_P9_Box[8]={0x88,0x00,0x00,0x30,0x0C,0x00,0x00,0x11};

//painel12


const uint8_t D2_P12_Box[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t C2_P12_Box[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t B2_P12_Box[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t A2_P12_Box[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t D1_P12_Box[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t C1_P12_Box[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t B1_P12_Box[8]={0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
const uint8_t A1_P12_Box[8]={0xF8,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x1F};
