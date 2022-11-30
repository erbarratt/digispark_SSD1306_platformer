#include "game.h"
//#include <stdlib.h>
//#include "../../SSD1306_tiny85/src/SSD1306_tiny85.h"

struct player_t playerObj;

//const unsigned char screen_1_collision[] PROGMEM =
const unsigned char screen_1_collision[] =
{
	0b00000000, 0b00000000,
	0b00000000, 0b00000000,
	0b00000001, 0b00000000,
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

	//perform x movement
		playerObj.x += playerObj.speedX;

	//limit x
		if(playerObj.x < 0){
			playerObj.x = 0;
			playerObj.speedX = 0;						//speed 0 stops collision checking below
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

		}

	//attempt to make the move
		playerObj.y += playerObj.speedY;

	//limit y
		if(playerObj.y < 0){
			playerObj.y = 0;
			playerObj.speedY = 0;
			playerObj.onGround = 0;
		} else if(playerObj.y > 40){
			playerObj.y = 40;
			playerObj.speedY = 0;			//speed 0 stops collision checking below
			playerObj.onGround = 1;
		}

	//set player tile byte index
		playerObj.tileByteIndex = (playerObj.x / 64) + ((playerObj.y / 8) *2);

	//set player bit index
		if(playerObj.x >= 64){
			playerObj.tileBitIndex = (playerObj.x - 64) /8;
		} else {
			playerObj.tileBitIndex = playerObj.x / 8;
		}

		//char c[4];
		//itoa(playerObj.x, c, 10);
		//OLED_defineMemAddressArea(0, 1, 127, 7);
		//OLED_printString(c);

	//floor + walking of edge
		{

			unsigned char colByteIndex = playerObj.tileByteIndex+2;
			unsigned char nextBitIndex = (playerObj.tileBitIndex == 7) ? 0 : playerObj.tileBitIndex+1;
			char nextByte = (playerObj.tileBitIndex == 7) ? 1 : 0;
			unsigned char nextColByteIndex = colByteIndex + nextByte;

			if(playerObj.speedY >= 0 && !playerObj.onGround){

				if(
					(
						(screen_1_collision[colByteIndex] & bitIndexLookup[playerObj.tileBitIndex]) && 					//tile directly below blocked
						playerObj.x % 8 == 0
					)||
					(
						(screen_1_collision[colByteIndex] & bitIndexLookup[playerObj.tileBitIndex]) ||
						(screen_1_collision[nextColByteIndex] & bitIndexLookup[nextBitIndex])

					) 																									//tile directly below + 1 blocked, if x % 8 != 0
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

	//cieling
		if(playerObj.speedY < 0 && !playerObj.onGround){

			unsigned char nextBitIndex = (playerObj.tileBitIndex == 7) ? 0 : playerObj.tileBitIndex+1;
			char nextByte = (playerObj.tileBitIndex == 7) ? 1 : 0;
			unsigned char nextColByteIndex = playerObj.tileByteIndex + nextByte;

			if(
				(
					(screen_1_collision[playerObj.tileByteIndex] & bitIndexLookup[playerObj.tileBitIndex]) && 					//tile directly above blocked
					playerObj.x % 8 == 0
				)||
				(
					(screen_1_collision[playerObj.tileByteIndex] & bitIndexLookup[playerObj.tileBitIndex]) ||
					(screen_1_collision[nextColByteIndex] & bitIndexLookup[nextBitIndex])

				) 																									//tile directly above + 1 blocked, if x % 8 != 0
			){

				playerObj.y = ((playerObj.y / 8) * 8) + 8 ; //revert to first bit vertically...
				playerObj.speedY = 0;

			}

		}

	//collisions to right
		if(playerObj.speedX > 0){

			//tile 1 to right
				unsigned char nextBitIndex = (playerObj.tileBitIndex == 7) ? 0 : playerObj.tileBitIndex + 1;
				unsigned char nextByte = (playerObj.tileBitIndex == 7) ? 1 : 0;
				unsigned char colByteIndex = playerObj.tileByteIndex + nextByte;

			//tile 1 to right and 1 below
				unsigned char nextNextBitIndex = (playerObj.tileBitIndex == 7) ? 0 : playerObj.tileBitIndex + 1;
				unsigned char nextNextByte = (playerObj.tileBitIndex == 7) ? 1 : 0;
				unsigned char nextColByteIndex = playerObj.tileByteIndex + 2 + nextNextByte;

			if(
				(
					screen_1_collision[colByteIndex] & bitIndexLookup[nextBitIndex] &&					//if on ground, then only check tile to right
					playerObj.onGround) ||
				(
					playerObj.onGround == 0 &&															//if not on ground, i.e. between 2 tiles vertically, then check both.
					(
						screen_1_collision[colByteIndex] & bitIndexLookup[nextBitIndex] ||
						screen_1_collision[nextColByteIndex] & bitIndexLookup[nextNextBitIndex]
					)
				)
				//also need to check tile below to stop jump / fall clips
			){

				playerObj.x = (playerObj.x / 8) * 8 ; //revert to first bit of previous tile
				playerObj.speedX = 0;

			}

		}

	//collisions to left
		else if(playerObj.speedX < 0){

			//tile 1 to left and 1 to below
				unsigned char colByteIndex = playerObj.tileByteIndex + 2;

			if(
				screen_1_collision[playerObj.tileByteIndex] & bitIndexLookup[playerObj.tileBitIndex] 	//tile we moved into is blocked, ever
				||
				(
					screen_1_collision[colByteIndex] & bitIndexLookup[playerObj.tileBitIndex] &&		//when jumping, we also need to check tile below tile we're in.
					playerObj.onGround == 0
				)
			){

				playerObj.x = ((playerObj.x / 8) * 8) + 8 ; //revert to first bit of previous tile
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
