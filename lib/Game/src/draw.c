#include "draw.h"
#include "game.h"
#include "../../SSD1306_tiny85/src/SSD1306_tiny85.h"

	void DRAW_bg()
	{

		OLED_defineMemAddressArea(0,0,127,0);
		OLED_printString("PLATFORMER");

		//clear all of the blue rows
			OLED_clearBlue();

		//might not need this as clear blue will roll over to this point anyway
			OLED_defineMemAddressArea(0, 2, 127, 7);

		CommandMode = 0;
		OLED_addToUSIBuffer(SSD1306_Data_Mode);

		//tile byte space
		//loop through screen array where each byte is 8 horizontal tiles of 8x8px
		for(unsigned char i = 0; i < 12; i++){

			//unsigned char thisByte = pgm_read_byte(&screen_1_collision[i]);
			unsigned char thisByte = screen_1_collision[i];

			//tilespace
			//loop through the byte to see if each of the 8 tiles is filled or not
			for(unsigned char k = 7; k >= 0; k--){

				unsigned char fill = (thisByte & (1 << k)) ? 0xff : 0x00;

				//8x8 space
				//write the 8 bytes of this tile
				for(unsigned char j = 0; j < 8; j++){
					OLED_addToUSIBuffer(fill);
				}

				if(k == 0){
					break;
				}

			}

		}

		OLED_xmitBuffer(1);

	}

	void DRAW_player()
	{
		OLED_defineMemAddressArea(playerObj.x, (playerObj.y/8)+2, 127, 7);

		CommandMode = 0;
		OLED_addToUSIBuffer(SSD1306_Data_Mode);
		OLED_addToUSIBuffer(0xff);
		OLED_xmitBuffer(1);
	}
