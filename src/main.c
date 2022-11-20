#include <avr/io.h>
#include "../lib/SSD1306_tiny85/src/SSD1306_tiny85.h"
#define PIN_LED 1

int main() {

	OLED_init();   // init OLED display
	//OLED_clear();

	//analogRead on pin P5
	OLED_cursorTo(0, 0);
	OLED_printString("V0: ");
	OLED_cursorTo(30, 0);
	OLED_printString(" 2V");
	
	// Initalize LED pin as output
	DDRB |= (1 << PIN_LED);

	while (1) {
		PORTB ^= (1 << PIN_LED);
		for (long i = 0; i < 500000; i++) {
			asm("");
		}
	}
}
