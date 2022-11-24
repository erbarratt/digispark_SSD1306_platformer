#ifndef DIGISPARK_ATT85_GAME_H
#define DIGISPARK_ATT85_GAME_H

	#define WALL_AMOUNT 4

	typedef struct bird_t {
		unsigned char x;
		unsigned char y;
		char speed;
		unsigned char currentRow;
		unsigned char score;
		unsigned char updateScore;
		unsigned char hitWall;

	} bird_t;

	extern bird_t bird;

	typedef struct wall_t {
		signed char topRows;
		unsigned char gap;
		unsigned char x;
	} wall_t;

	extern wall_t walls[WALL_AMOUNT];

	void GAME_init();
	void GAME_moveBird(unsigned char);
	void GAME_moveWalls();

#endif //DIGISPARK_ATT85_GAME_H
