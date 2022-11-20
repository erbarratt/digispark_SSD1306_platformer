#include <avr/io.h>
#include "../lib/TinyWire/src/SSD1306_minimal.h"
#define PIN_LED 1

int main() {

	init();   // init OLED display
	clear();

	//analogRead on pin P5
	cursorTo(0, 0);
	printString( "V0: ");
	cursorTo(30, 0);
	printString(" 2V");
	
	// Initalize LED pin as output
	DDRB |= (1 << PIN_LED);

	while (1) {
		PORTB ^= (1 << PIN_LED);
		for (long i = 0; i < 500000; i++) {
			asm("");
		}
	}
}
