#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdlib.h>
#include "../lib/flappy_tiny85/src/game.h"
#include "../lib/flappy_tiny85/src/draw.h"
#include <inttypes.h>
#include <avr/interrupt.h>
#define BUTTON_PIN 4
#define PIN_LED 1

//blue section is 128 x 48

/* some vars */
uint64_t _millis = 0;
uint16_t _1000us = 0;

uint64_t old_millis = 0;

/* interrupts routines */
// timer overflow occur every 0.256 ms
ISR(TIM0_OVF_vect) {
  _1000us += 128;
  //_1000us += 256;
  while (_1000us > 1000) {
    _millis++;
    _1000us -= 1000;
  }
}

// safe access to millis counter
uint64_t millis() {
  uint64_t m;
  cli();
  m = _millis;
  sei();
  return m;
}

static inline void fps(const int seconds){
  // Create static variables so that the code and variables can
  // all be declared inside a function
  static unsigned long lastMillis;
  static unsigned long frameCount;
  static unsigned int framesPerSecond;

  // It is best if we declare millis() only once
  unsigned long now = millis();
  frameCount ++;
  if (now - lastMillis >= seconds * 1000) {
    framesPerSecond = frameCount / seconds;
    frameCount = 0;
    lastMillis = now;

	char c[4];
	itoa(framesPerSecond, c, 10);
	OLED_defineMemAddressArea(70, 0, 128-70, 8);
	OLED_printString(c);

  }

}

int main() {

	/* interrup setup */
  // prescale timer0 to 1/8th the clock rate
  // overflow timer0 every 0.256 ms
  TCCR0B |= (1<<CS01);
  // enable timer overflow interrupt
  TIMSK  |= 1<<TOIE0;

  // Enable global interrupts
  sei();

	DRAW_init();
	GAME_init();


	//unsigned char button;
	//char text[10];

	DDRB &= ~(1 << DDB4); 			//set Pin 4 as input (0) for the button

	while (1) {

		_delay_ms(20);

		DRAW_lower();
		GAME_moveBird(PINB & (1 << BUTTON_PIN));
		GAME_moveWalls();

		//fps(1);

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
