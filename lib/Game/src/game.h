#ifndef DIGISPARK_SSD1306_PLATFORMER_GAME_H
#define DIGISPARK_SSD1306_PLATFORMER_GAME_H

	struct player_t {
		unsigned char x;
		unsigned char y;
		unsigned char speedX;
		unsigned char speedY;
	} player_t;

	extern struct player_t playerObj;

	struct screen_t {

	} screen_t;

	void GAME_init();

#endif
