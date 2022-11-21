#ifndef DIGISPARK_ATT85_GAME_H
#define DIGISPARK_ATT85_GAME_H

	typedef struct bird_t {
		unsigned char x;
		unsigned char y;
		unsigned char speed;

	} bird_t;

	extern bird_t bird;

	void GAME_init();
	void GAME_moveBird();

#endif //DIGISPARK_ATT85_GAME_H
