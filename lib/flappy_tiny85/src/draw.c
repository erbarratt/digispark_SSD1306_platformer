#include "draw.h"

void DRAW_init(){
	_delay_ms(50);
	OLED_init();   // init OLED display
	OLED_clear();
	OLED_defineMemAddressArea(0, 0, 128, 8);
	OLED_printString("FLPPY BRD");
}

void DRAW_lower(){

	OLED_clearBlue();

	//walls
		OLED_defineMemAddressArea(walls[0].x, 2, 1, 6);
		OLED_addToUSIBuffer(SSD1306_Data_Mode);            		// data mode
		for(unsigned char i = 0; i < walls[0].topRows; i++){
			OLED_addToUSIBuffer(0xff);
		}
		for(unsigned char i = 0; i < walls[0].gap; i++){
			OLED_addToUSIBuffer(0x00);
		}
		for(unsigned char i = 0; i < 6 - (walls[0].topRows + walls[0].gap); i++){
			OLED_addToUSIBuffer(0xff);
		}

		OLED_xmitBuffer(1, 1);

	//firugre out which of 6 blue rows bird is in
		unsigned char row = bird.y / 8;

		unsigned char posInByte = bird.y - (row*8);
		unsigned char drawByte = 0b00000000 | (1 << posInByte);

		row += 2;														//because first 2 rows are yellow rows
		OLED_defineMemAddressArea(0, row, 128 - 0, 8 - row);
		OLED_addToUSIBuffer(SSD1306_Data_Mode);            		// data mode
		OLED_addToUSIBuffer(drawByte);

		OLED_xmitBuffer(1, 1);

	//OLED_defineMemAddressArea(0, 0, 128 - 0, 8 - 0);
	//char c[4];
	//itoa(bird.y, c, 10);
	//OLED_printString(c);
	//
	//OLED_defineMemAddressArea(30, 0, 128 - 30, 8 - 0);
	//itoa(posInByte, c, 10);
	//OLED_printString(c);

}
