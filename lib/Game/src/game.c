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
	0b11111111, 0b11110011
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

	//jump if on ground
		if(left && right ){

			if(playerObj.onGround){
				//jump
				playerObj.speedY = -6;
				playerObj.onGround = 0;
			}

	//move left
		} else if(left){
			playerObj.speedX--;
			if(playerObj.speedX < -3){
				playerObj.speedX = -3;
			}
	//move right
		} else if(right){
			playerObj.speedX++;
			if(playerObj.speedX > 3){
				playerObj.speedX = 3;
			}

	//slow down
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
			playerObj.speedX = 0;
		} else if(playerObj.x > 119){
			playerObj.x = 119;
			playerObj.speedX = 0;
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

		//char c[4];
		//itoa(12%8, c, 10);
		//OLED_defineMemAddressArea(0, 1, 127, 7);
		//OLED_printString(c);

	//floor
		{
			unsigned char colByteIndex = playerObj.tileByteIndex+2;

			unsigned char nextBitIndex = (playerObj.tileBitIndex == 7) ? 0 : playerObj.tileBitIndex+1;
			char nextByte = (playerObj.tileBitIndex == 7) ? 1 : 0;
			unsigned char nextColByteIndex = colByteIndex + nextByte;

			if(playerObj.speedY >= 0 && !playerObj.onGround){

				if(
					(
						(screen_1_collision[colByteIndex] & bitIndexLookup[playerObj.tileBitIndex]) && 			//tile directly below free
						playerObj.x % 8 == 0
					)||
					(
						(screen_1_collision[colByteIndex] & bitIndexLookup[playerObj.tileBitIndex]) ||
						(screen_1_collision[nextColByteIndex] & bitIndexLookup[nextBitIndex])

					) //tile directly below + 1 blocked, if x % 8 != 0
				){

					playerObj.y = (playerObj.y / 8) * 8 ; //revert to first bit vertically...
					playerObj.speedY = 0;
					playerObj.onGround = 1;

				}

			} else if (playerObj.onGround) {

				if(
					(
						(screen_1_collision[colByteIndex] & bitIndexLookup[playerObj.tileBitIndex]) == 0 && 			//tile directly below free
						playerObj.x % 8 == 0
					)||
					(
						(screen_1_collision[colByteIndex] & bitIndexLookup[playerObj.tileBitIndex]) == 0 &&
						(screen_1_collision[nextColByteIndex] & bitIndexLookup[nextBitIndex]) == 0

					) //tile directly below + 1 blocked, if x % 8 != 0
				){

					playerObj.onGround = 0;

				}

			}
		}

	//collisions to right
		if(playerObj.speedX > 0){


			char nextByte = (playerObj.tileBitIndex == 7) ? 1 : 0;
			char nextByteIndex = (playerObj.tileBitIndex == 7) ? 0 : playerObj.tileBitIndex + 1;

			unsigned char colByteIndex = playerObj.tileByteIndex + nextByte;

			if(
				screen_1_collision[colByteIndex] & bitIndexLookup[nextByteIndex]
			){

				playerObj.x = (playerObj.x / 8) * 8 ; //revert to first bit of previous tile
				playerObj.speedX = 0;

			}

		}

	//collisions to left
		else if(playerObj.speedX < 0){

			if(screen_1_collision[playerObj.tileByteIndex] & bitIndexLookup[playerObj.tileBitIndex]){

				playerObj.x = (playerObj.x / 8) * 9 ; //revert to first bit of previous tile
				playerObj.speedX = 0;

				if(playerObj.tileBitIndex == 7){
					playerObj.tileBitIndex = 0;
					playerObj.tileByteIndex++;
				} else {
					playerObj.tileBitIndex++;
				}

			}

		}
}
