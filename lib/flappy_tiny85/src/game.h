#ifndef DIGISPARK_ATT85_GAME_H
#define DIGISPARK_ATT85_GAME_H

	typedef struct bird_t {
		unsigned char x;
		unsigned char y;
		char speed;

	} bird_t;

	extern bird_t bird;

	typedef struct wall_t {
		unsigned char topRows;
		unsigned char gap;
		unsigned char x;
	} wall_t;

	extern wall_t walls[10];

	void GAME_init();
	void GAME_moveBird(unsigned char);
	void GAME_moveWalls();

#endif //DIGISPARK_ATT85_GAME_H
