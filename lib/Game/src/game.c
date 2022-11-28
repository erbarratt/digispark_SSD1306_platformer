#include "game.h"

struct player_t playerObj;

//const unsigned char screen_1_collision[] PROGMEM =
const unsigned char screen_1_collision[] =
{
	0b00000000, 0b00000000,
	0b00000000, 0b00000000,
	0b00000000, 0b00000000,
	0b00000000, 0b00000000,
	0b00000000, 0b00000000,
	0b11111111, 0b11110111
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

void GAME_movePlayer(unsigned char button){

	if(playerObj.onGround == 0){

		playerObj.speedY++;
		if(playerObj.speedY > 3){
			playerObj.speedY = 3;
		}

		//attemp to make the move
			playerObj.y += playerObj.speedY;

	}

	////set player tile index
	//	playerObj.tileByteIndex = (playerObj.x / 8) + (playerObj.y * 2);
	//
	////set player tile byte index
	//	playerObj.tileIndex = (playerObj.x / 8) + ((playerObj.y / 8) *2);
	//
	////set player bit index
	//	playerObj.tileBitIndex = (playerObj.x/8) & 0b0111;
	//
	////check collisions
	//	if(playerObj.speedY > 0){
	//
	//		//if tile we're in now = blocked, move back up.
	//
	//		if(playerObj.y % 8 != 0){
	//
	//			unsigned char colByteIndex = playerObj.tileByteIndex+2;
	//
	//			if((screen_1_collision[colByteIndex] && (1 >> playerObj.tileBitIndex)) != 0){
	//
	//				playerObj.speedY = 0;
	//				playerObj.onGround = 1;
	//
	//			}
	//
	//		}
	//
	//	}

}
