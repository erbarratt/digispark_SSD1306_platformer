#include "game.h"

struct player_t playerObj;

void GAME_init()
{
	playerObj.x = 8;
	playerObj.y = 8;
	playerObj.speedX = 0;
	playerObj.speedY = 0;
}
