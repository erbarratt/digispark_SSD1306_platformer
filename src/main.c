#define F_CPU 16000000UL
#include <avr/io.h>

#include "../lib/flappy_tiny85/src/game.h"
#include "../lib/flappy_tiny85/src/draw.h"
#define PIN_LED 1

//blue section is 128 x 48

int main() {

	DRAW_init();
	GAME_init();

	while (1) {

		_delay_ms(66);
		GAME_moveBird();
		DRAW_lower();

		//OLED_clear();
		//OLED_clipArea(0, row, 128 - 0, 8 - row);
		//OLED_printString("ARSE");
		//for (long i = 0; i < 500000; i++) {
		//	asm("");
		//}

	}
	
	// Initalize LED pin as output
	//DDRB |= (1 << PIN_LED);
	//unsigned char k = 0;
	//while (k < 6) {
	//	PORTB ^= (1 << PIN_LED);
	//	for (long i = 0; i < 500000; i++) {
	//		asm("");
	//	}
	//	k++;
	//}

}
