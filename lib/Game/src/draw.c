#include "draw.h"
#include "game.h"
#include "../../SSD1306_tiny85/src/SSD1306_tiny85.h"

/**
* Draw the background tiles
* @return void
*/
	void DRAW_bg()
	{

		//OLED_defineMemAddressArea(0,0,127,0);
		//OLED_printString("PLATFORMER");

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

/**
* clear the player 8x8 px tile, anywhere on screen
* @return void
*/
	void DRAW_clearPlayer()
	{
		unsigned char clearBytes = (playerObj.y % 8 != 0) ? 16 : 8;
		OLED_defineMemAddressArea(playerObj.x, (playerObj.y/8)+2, playerObj.x+7, 7);
		CommandMode = 0;
		OLED_addToUSIBuffer(SSD1306_Data_Mode);
		for(unsigned char i = 0; i < clearBytes; i++){
			OLED_addToUSIBuffer(0x00);
		}
		OLED_xmitBuffer(1);
	}

/**
* Draw the player 8x8 px tile, anywhere on screen
* @return void
*/
	void DRAW_player()
	{

		//the player position might mean we need to draw across 2 rows

		unsigned char offsetY = playerObj.y % 8;

		OLED_defineMemAddressArea(playerObj.x, (playerObj.y/8)+2, playerObj.x+7, 7);

		CommandMode = 0;
		OLED_addToUSIBuffer(SSD1306_Data_Mode);

		if(offsetY){

			//instead of doing lots of bitshifts, do 4 here, 2 each for the upper and lower rows
				unsigned char sideTop = 0b01111110 << offsetY;
				unsigned char sideBottom = 0b01111110 >> (8-offsetY);
				unsigned char midTop = 0b11111111 << offsetY;
				unsigned char midBottom = 0b11111111 >> (8-offsetY);

				OLED_addToUSIBuffer(sideTop);
				OLED_addToUSIBuffer(midTop);
				OLED_addToUSIBuffer(midTop);
				OLED_addToUSIBuffer(midTop);
				OLED_addToUSIBuffer(midTop);
				OLED_addToUSIBuffer(midTop);
				OLED_addToUSIBuffer(midTop);
				OLED_addToUSIBuffer(sideTop);

				OLED_addToUSIBuffer(sideBottom);
				OLED_addToUSIBuffer(midBottom);
				OLED_addToUSIBuffer(midBottom);
				OLED_addToUSIBuffer(midBottom);
				OLED_addToUSIBuffer(midBottom);
				OLED_addToUSIBuffer(midBottom);
				OLED_addToUSIBuffer(midBottom);
				OLED_addToUSIBuffer(sideBottom);

		} else {

			OLED_addToUSIBuffer(0b01111110);
			OLED_addToUSIBuffer(0xff);
			OLED_addToUSIBuffer(0xff);
			OLED_addToUSIBuffer(0xff);
			OLED_addToUSIBuffer(0xff);
			OLED_addToUSIBuffer(0xff);
			OLED_addToUSIBuffer(0xff);
			OLED_addToUSIBuffer(0b01111110);

		}

		OLED_xmitBuffer(1);

	}
