#include "draw.h"
#include <stdlib.h>
void DRAW_init(){
	_delay_ms(50);
	OLED_init();   // init OLED display
	OLED_clear();
	OLED_defineMemAddressArea(0, 0, 128, 8);

	//FLPPY BRD
	unsigned char flppyBrd[] = {
		0x00,0x36, 0x09, 0x09, 0x00, 0x00,0x00, // char 'F' (0x46/70)
		0x00,0x36, 0x40, 0x40, 0x00, 0x00, 0x00,// char 'L' (0x4C/76)
		0x00,0x36, 0x09, 0x09, 0x36, 0x00, 0x00,// char 'A' (0x41/65)
		0x00,0x36, 0x09, 0x09, 0x06, 0x00, 0x00,// char 'P' (0x50/80)
		0x00,0x36, 0x09, 0x09, 0x06, 0x00,0x00, // char 'P' (0x50/80)
		0x00,0x06, 0x48, 0x48, 0x36, 0x00, 0x00,// char 'Y' (0x59/89)
		0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00,// char ' ' (0x20/32)
		0x00,0x77, 0x49, 0x49, 0x36, 0x00, 0x00,// char 'B' (0x42/66)
		0x00,0x36, 0x09, 0x19, 0x26, 0x00, 0x00,// char 'R' (0x52/82)
		0x00,0x77, 0x41, 0x41, 0x36, 0x00, 0x00,// char 'D' (0x44/68)
	};

	OLED_addToUSIBuffer(SSD1306_Data_Mode);
	CommandMode = 0;

	for(unsigned char i = 0; i <= 69; i+=7){

		OLED_addToUSIBuffer(flppyBrd[i]);
		OLED_addToUSIBuffer(flppyBrd[i+1]);
		OLED_addToUSIBuffer(flppyBrd[i+2]);
		OLED_addToUSIBuffer(flppyBrd[i+3]);
		OLED_addToUSIBuffer(flppyBrd[i+4]);
		OLED_addToUSIBuffer(flppyBrd[i+5]);
		OLED_addToUSIBuffer(flppyBrd[i+6]);

	}

	OLED_xmitBuffer(1);

}

void DRAW_lower(){

	OLED_clearBlue();

	//walls
		for(unsigned char i = 0; i < WALL_AMOUNT; i++){

			OLED_defineMemAddressArea(walls[i].x, 2, 1, 6);
			OLED_addToUSIBuffer(SSD1306_Data_Mode);            		// data mode
			for(unsigned char k = 0; k < walls[i].topRows; k++){
				OLED_addToUSIBuffer(0xff);
			}
			for(unsigned char k = 0; k < walls[i].gap; k++){
				OLED_addToUSIBuffer(0x00);
			}
			for(unsigned char k = 0; k < 6 - (walls[i].topRows + walls[i].gap); k++){
				OLED_addToUSIBuffer(0xff);
			}

			OLED_xmitBuffer(1);
		}

	//firugre out which of 6 blue rows bird is in
		unsigned char posInByte = bird.y - (bird.currentRow*8);
		unsigned char drawByte = 0b00000000 | (1 << posInByte);

		bird.currentRow += 2;														//because first 2 rows are yellow rows
		OLED_defineMemAddressArea(0, bird.currentRow, 1, 8 - bird.currentRow);
		OLED_addToUSIBuffer(SSD1306_Data_Mode);            					// data mode
		OLED_addToUSIBuffer(drawByte);
		bird.currentRow -= 2;														//reset back to correct row value

		OLED_xmitBuffer(1);

		if(bird.updateScore == 1){
			char c[4];
			itoa(bird.score, c, 10);
			OLED_defineMemAddressArea(90, 0, 128-90, 8);
			OLED_printString(c);
			bird.updateScore = 0;
		}

		if(bird.hitWall == 1){
			OLED_addToUSIBuffer(SSD1306_Command_Mode);
			OLED_addToUSIBuffer(SSD1306_Inverse_Display_Cmd);
			OLED_xmitBuffer(1);
			_delay_ms(100);
			OLED_addToUSIBuffer(SSD1306_Command_Mode);
			OLED_addToUSIBuffer(SSD1306_Normal_Display_Cmd);
			OLED_xmitBuffer(1);
			bird.hitWall = 0;
		}

	//OLED_defineMemAddressArea(0, 0, 128 - 0, 8 - 0);
	//char c[4];
	//itoa(bird.y, c, 10);
	//OLED_printString(c);
	//
	//OLED_defineMemAddressArea(30, 0, 128 - 30, 8 - 0);
	//itoa(posInByte, c, 10);
	//OLED_printString(c);

}
