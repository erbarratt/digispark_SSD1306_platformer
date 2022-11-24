#include "game.h"

bird_t bird;
wall_t walls[WALL_AMOUNT];

void GAME_init(){
	bird.y = 0;
	bird.x = 10;
	bird.speed = 0;
	bird.currentRow = 0;
	bird.updateScore = 0;
	bird.hitWall = 0;
	bird.score = 0;

	for(unsigned char i = 0; i < WALL_AMOUNT; i++){
		wall_t wall;
		wall.x = 127 - (32*i);
		wall.gap = 4;
		wall.topRows = 1;
		walls[i] = wall;
	}

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

	//update current row to use in draw and for collisions
	//this is the floor() of the division, i.e. removing the remainder as it's not a float
	bird.currentRow = bird.y / 8;


}

void GAME_moveWalls(){

	for(unsigned char i = 0; i < WALL_AMOUNT; i++){
		walls[i].x--;
		if(walls[i].x == 0){

			//check for collision
				if(
					bird.currentRow+1 <= walls[i].topRows ||
					bird.currentRow+1 > (walls[i].topRows + walls[i].gap)
				){
					bird.hitWall = 1;
				} else {
					bird.updateScore = 1;
					bird.score++;

					//modify wall
						if(bird.score % 20 == 0){
							walls[i].gap--;
						}

						if(bird.score % 2 == 0){
							walls[i].topRows--;
							if(walls[i].topRows < 0){
								walls[i].topRows = 0;
							}
						} else {
							walls[i].topRows++;
							if(walls[i].topRows + walls[i].gap > 6){
								walls[i].gap--;
							}
						}

				}

			walls[i].x = 127;

		}
	}

}

