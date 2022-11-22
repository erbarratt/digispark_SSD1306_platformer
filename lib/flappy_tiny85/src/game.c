#include "game.h"

bird_t bird;
wall_t walls[10];

void GAME_init(){
	bird.y = 0;
	bird.x = 10;
	bird.speed = 0;

	wall_t wall1;
	wall1.x = 127;
	wall1.gap = 4;
	wall1.topRows = 1;
	walls[0] = wall1;

}

void GAME_moveBird(unsigned char button){

	if(button){
		bird.speed = -3;
	} else {
		bird.speed++;
		if(bird.speed > 3){
			bird.speed = 3;
		}
	}

	bird.y += bird.speed;

	if(bird.y > 47){
		bird.y = 0;
	}



}

void GAME_moveWalls(){

	walls[0].x--;

}

