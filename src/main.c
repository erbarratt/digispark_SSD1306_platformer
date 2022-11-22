#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdlib.h>
#include "../lib/flappy_tiny85/src/game.h"
#include "../lib/flappy_tiny85/src/draw.h"
#define BUTTON_PIN 4
#define PIN_LED 1

//blue section is 128 x 48

int main() {

	DRAW_init();
	GAME_init();


	unsigned char button;
	//char text[10];

	DDRB &= ~(1 << DDB4); 			//set Pin 4 as input (0)

	while (1) {



		_delay_ms(33);

		button = PINB & (1 << BUTTON_PIN);

		GAME_moveBird(button);
		GAME_moveWalls();
		DRAW_lower();

		//
		//
		//itoa(button, text, 10);
		//
		//OLED_printString(text);
		//
		//if(button){
		//	PINB |= (1 << PIN_LED);
		//} else {
		//	PINB &= ~(1 << PIN_LED);
		//}

	}


	//OLED_clear();
		//OLED_defineMemAddressArea(0, row, 128 - 0, 8 - row);
		//OLED_printString("ARSE");
		//for (long i = 0; i < 500000; i++) {
		//	asm("");
		//}


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
