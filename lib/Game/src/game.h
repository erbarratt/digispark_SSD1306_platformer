#ifndef DIGISPARK_SSD1306_PLATFORMER_GAME_H
#define DIGISPARK_SSD1306_PLATFORMER_GAME_H

	#include <avr/pgmspace.h>

	extern const unsigned char screen_1_collision[];

	struct player_t {
		unsigned char x;
		unsigned char y;
		unsigned char speedX;
		unsigned char speedY;
		unsigned char onGround :1;
		unsigned char onWall : 1;
		unsigned char unused : 6;
		unsigned char tileByteIndex;
		unsigned char tileIndex;
		unsigned char tileBitIndex;
	} player_t;

	extern struct player_t playerObj;

	struct screen_t {

	} screen_t;

	void GAME_init();
	void GAME_movePlayer(unsigned char button);

#endif
