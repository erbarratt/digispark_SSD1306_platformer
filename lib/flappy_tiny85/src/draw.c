#include "draw.h"

void DRAW_init(){
	_delay_ms(50);
	OLED_init();   // init OLED display
	OLED_clear();
	OLED_printString("FLPPY BRD");
}

void DRAW_lower(){

	OLED_clearBlue();

	//firugre out which of 6 blue rows bird is in
	unsigned char row = bird.y / 8;

	unsigned char posInByte = bird.y - (row*8);
	unsigned char drawByte = 0b00000000 | (1 << posInByte);

	row += 2;														//because first 2 rows are yellow rows
	OLED_clipArea(0, row, 128 - 0, 8 - row);
	OLED_addToUSIBuffer(SSD1306_Data_Mode);            		// data mode
	OLED_addToUSIBuffer(drawByte);
	OLED_xmitBuffer(1);

	//OLED_clipArea(0, 0, 128 - 0, 8 - 0);
	//char c[4];
	//itoa(bird.y, c, 10);
	//OLED_printString(c);
	//
	//OLED_clipArea(30, 0, 128 - 30, 8 - 0);
	//itoa(posInByte, c, 10);
	//OLED_printString(c);

}
