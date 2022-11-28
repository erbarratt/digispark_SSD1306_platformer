#include "game.h"
#include <stdlib.h>
#include "../../SSD1306_tiny85/src/SSD1306_tiny85.h"

struct player_t playerObj;

//const unsigned char screen_1_collision[] PROGMEM =
const unsigned char screen_1_collision[] =
{
	0b00000000, 0b00000000,
	0b00000000, 0b00000000,
	0b00000000, 0b00000000,
	0b00000000, 0b00000000,
	0b00000000, 0b01000000,
	0b11111111, 0b11110111
};

const unsigned char bitIndexLookup[] = {
	0b10000000,
	0b01000000,
	0b00100000,
	0b00010000,
	0b00001000,
	0b00000100,
	0b00000010,
	0b00000001
};

void GAME_init()
{
	//starts at top left px
	playerObj.x = 0;
	playerObj.y = 0;
	playerObj.speedX = 0;
	playerObj.speedY = 0;
	playerObj.onGround = 0;
	playerObj.onWall = 0;
	playerObj.tileByteIndex = 0;
	playerObj.tileIndex = 0;
	playerObj.tileBitIndex = 0;
}

void GAME_movePlayer(unsigned char left, unsigned char right){

	if(left && right ){

		if(playerObj.onGround){
			//jump
			playerObj.speedY = -6;
			playerObj.onGround = 0;
		}

	} else if(left){
		playerObj.speedX--;
		if(playerObj.speedX < -3){
			playerObj.speedX = -3;
		}
	} else if(right){
		playerObj.speedX++;
		if(playerObj.speedX > 3){
			playerObj.speedX = 3;
		}
	} else {
		if(playerObj.speedX > 0){
			playerObj.speedX--;
		} else if(playerObj.speedX < 0){
			playerObj.speedX++;
		}
	}

	playerObj.x += playerObj.speedX;

	//limit x
		if(playerObj.x < 0){
			playerObj.x = 0;
		} else if(playerObj.x > 119){
			playerObj.x = 119;
		}

	//gravity
		if(playerObj.onGround == 0){

			playerObj.speedY++;
			if(playerObj.speedY > 3){
				playerObj.speedY = 3;
			}

			//attempt to make the move
				playerObj.y += playerObj.speedY;

		}

	//set player tile index
	//54
	//	playerObj.tileIndex = (playerObj.x / 8) + (playerObj.y * 2);

	//set player tile byte index
		playerObj.tileByteIndex = (playerObj.x / 64) + ((playerObj.y / 8) *2);

	//set player bit index
		if(playerObj.x >= 64){
			playerObj.tileBitIndex = (playerObj.x - 64) /8;
		} else {
			playerObj.tileBitIndex = playerObj.x / 8;
		}

		char c[4];
		itoa(12%8, c, 10);
		OLED_defineMemAddressArea(0, 1, 127, 7);
		OLED_printString(c);

	//check collisions
		if(playerObj.speedY > 0){

				unsigned char colByteIndex = playerObj.tileByteIndex+2;

				if(screen_1_collision[colByteIndex] & bitIndexLookup[playerObj.tileBitIndex]){

					playerObj.y = (playerObj.y / 8) * 8 ; //revert to first bit vertically...
					playerObj.speedY = 0;
					playerObj.onGround = 1;

				}

		}

		if(playerObj.speedX != 0){

			char nextByte = (playerObj.tileBitIndex == 7) ? 1 : 0;
			char nextByteIndex = (playerObj.tileBitIndex == 7) ? 0 : playerObj.tileBitIndex + 1;

			if(playerObj.speedX < 0){
				nextByte = (playerObj.tileBitIndex == 0) ? -1 : 0;
				nextByteIndex = (playerObj.tileBitIndex == 0) ? 7 : playerObj.tileBitIndex - 1;
			}

			unsigned char colByteIndex = playerObj.tileByteIndex + nextByte;

			if(screen_1_collision[colByteIndex] & bitIndexLookup[nextByteIndex]){

				playerObj.x = (playerObj.x / 8) * 8 ; //revert to first bit vertically...
				playerObj.speedX = 0;

			}

		}

}
