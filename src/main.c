#include <avr/io.h>
#include "../lib/SSD1306_tiny85/src/SSD1306_tiny85.h"
#define PIN_LED 1

int main() {

	for (long i = 0; i < 500000; i++) {
		asm("");
	}
	OLED_init();   // init OLED display
	//OLED_clear();
	//return 0;
	//OLED_cursorTo(30, 0);
	//OLED_printString(" 2V");

	unsigned char row = 0;

	while (1) {
		OLED_clear();
		OLED_clipArea(0, row, 128 - 0, 8 - row);
		OLED_printString("Love You");
		row++;
		if(row > 7){
			row = 0;
		}
		//for (long i = 0; i < 500000; i++) {
		//	asm("");
		//}
	}
	
	// Initalize LED pin as output
	DDRB |= (1 << PIN_LED);
	unsigned char k = 0;
	while (k < 6) {
		PORTB ^= (1 << PIN_LED);
		for (long i = 0; i < 500000; i++) {
			asm("");
		}
		k++;
	}

}
