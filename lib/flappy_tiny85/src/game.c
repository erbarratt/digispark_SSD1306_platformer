#include "game.h"

bird_t bird;

void GAME_init(){
	bird.y = 0;
	bird.x = 10;
	bird.speed = 0;
}

void GAME_moveBird(){

	bird.speed++;

	bird.y += bird.speed;
	if(bird.y > 47){
		bird.y = 0;
		bird.speed = 0;
	}

}

