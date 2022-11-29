#define F_CPU 16000000UL
#include <util/delay.h>
#include "../lib/SSD1306_tiny85/src/SSD1306_tiny85.h"
#include "../lib/Game/src/draw.h"
#include "../lib/Game/src/game.h"

#define LEFT_BUTTON_PIN 1
#define RIGHT_BUTTON_PIN 4

int main() {

	DDRB &= ~(1 << DDB1); 			//set Pin 3 as input (0) for the left button
	DDRB &= ~(1 << DDB4); 			//set Pin 4 as input (0) for the right button

	OLED_init();
	OLED_clear();

	GAME_init();
	DRAW_bg();

	while(1){
		_delay_ms(33);
		DRAW_clearPlayer();
		GAME_movePlayer(PINB & (1 << LEFT_BUTTON_PIN), PINB & (1 << RIGHT_BUTTON_PIN));
		DRAW_player();
	}

	//unsigned int textStart = 100;
	//unsigned int frames = 0;
	//
	//OLED_defineMemAddressArea(16,2,31,7);
	//
	//CommandMode = 0;
	//OLED_addToUSIBuffer(SSD1306_Data_Mode);            				// data mode
	//
	//for(unsigned char i = 0; i < 64; i++){
	//	OLED_addToUSIBuffer(0xFF);
	//}
	//
	//OLED_xmitBuffer(1);
	//
	//OLED_defineMemAddressArea(8,5,127,7);
	//OLED_addToUSIBuffer(SSD1306_Data_Mode);            				// data mode
	//OLED_addToUSIBuffer(0b00000001);
	//OLED_addToUSIBuffer(0b00000111);
	//OLED_addToUSIBuffer(0b00001111);
	//OLED_addToUSIBuffer(0b00111111);
	//OLED_addToUSIBuffer(0b01111111);
	//OLED_addToUSIBuffer(0b11111111);
	//OLED_addToUSIBuffer(0b11111111);
	//OLED_addToUSIBuffer(0b11111111);
	//OLED_xmitBuffer(1);
	//
	//OLED_defineMemAddressArea(32,5,127,7);
	//OLED_addToUSIBuffer(SSD1306_Data_Mode);            				// data mode
	//OLED_addToUSIBuffer(0b11111111);
	//OLED_addToUSIBuffer(0b11111111);
	//OLED_addToUSIBuffer(0b11111111);
	//OLED_addToUSIBuffer(0b01111111);
	//OLED_addToUSIBuffer(0b00111111);
	//OLED_addToUSIBuffer(0b00001111);
	//OLED_addToUSIBuffer(0b00000111);
	//OLED_addToUSIBuffer(0b00000001);
	//OLED_xmitBuffer(1);
	//
	//OLED_defineMemAddressArea(8,6,127,7);
	//OLED_addToUSIBuffer(SSD1306_Data_Mode);            				// data mode
	//OLED_addToUSIBuffer(0x00);
	//OLED_addToUSIBuffer(0x00);
	//OLED_addToUSIBuffer(0x00);
	//OLED_addToUSIBuffer(0x00);
	//OLED_addToUSIBuffer(0x00);
	//OLED_addToUSIBuffer(0b00000001);
	//OLED_addToUSIBuffer(0b00000011);
	//OLED_addToUSIBuffer(0b00001111);
	//OLED_xmitBuffer(1);
	//
	//OLED_defineMemAddressArea(32,6,127,7);
	//OLED_addToUSIBuffer(SSD1306_Data_Mode);            				// data mode
	//OLED_addToUSIBuffer(0b00001111);
	//OLED_addToUSIBuffer(0b00000011);
	//OLED_addToUSIBuffer(0b00000001);
	//OLED_addToUSIBuffer(0x00);
	//OLED_addToUSIBuffer(0x00);
	//OLED_addToUSIBuffer(0x00);
	//OLED_addToUSIBuffer(0x00);
	//OLED_addToUSIBuffer(0x00);
	//OLED_xmitBuffer(1);
	//
	//OLED_defineMemAddressArea(16,6,127,7);
	//OLED_addToUSIBuffer(SSD1306_Data_Mode);            				// data mode
	//OLED_addToUSIBuffer(0b00111111);
	//OLED_addToUSIBuffer(0b01111111);
	//OLED_addToUSIBuffer(0xff);
	//OLED_addToUSIBuffer(0xff);
	//OLED_addToUSIBuffer(0xff);
	//OLED_addToUSIBuffer(0xff);
	//OLED_addToUSIBuffer(0xff);
	//OLED_addToUSIBuffer(0xff);
	//OLED_xmitBuffer(1);
	//
	//OLED_defineMemAddressArea(24,6,127,7);
	//OLED_addToUSIBuffer(SSD1306_Data_Mode);            				// data mode
	//OLED_addToUSIBuffer(0xff);
	//OLED_addToUSIBuffer(0xff);
	//OLED_addToUSIBuffer(0xff);
	//OLED_addToUSIBuffer(0xff);
	//OLED_addToUSIBuffer(0xff);
	//OLED_addToUSIBuffer(0xff);
	//OLED_addToUSIBuffer(0b01111111);
	//OLED_addToUSIBuffer(0b00111111);
	//OLED_xmitBuffer(1);
	//
	//OLED_defineMemAddressArea(16,7,127,7);
	//OLED_addToUSIBuffer(SSD1306_Data_Mode);            				// data mode
	//OLED_addToUSIBuffer(0x00);
	//OLED_addToUSIBuffer(0x00);
	//OLED_addToUSIBuffer(0b00000001);
	//OLED_addToUSIBuffer(0b00000011);
	//OLED_addToUSIBuffer(0b00001111);
	//OLED_addToUSIBuffer(0b00011111);
	//OLED_addToUSIBuffer(0b01111111);
	//OLED_addToUSIBuffer(0b11111111);
	//OLED_xmitBuffer(1);
	//
	//OLED_defineMemAddressArea(24,7,127,7);
	//OLED_addToUSIBuffer(SSD1306_Data_Mode);            				// data mode
	//OLED_addToUSIBuffer(0b11111111);
	//OLED_addToUSIBuffer(0b01111111);
	//OLED_addToUSIBuffer(0b00011111);
	//OLED_addToUSIBuffer(0b00001111);
	//OLED_addToUSIBuffer(0b00000011);
	//OLED_addToUSIBuffer(0b00000001);
	//OLED_addToUSIBuffer(0x00);
	//OLED_addToUSIBuffer(0x00);
	//OLED_xmitBuffer(1);

	//while (1) {

		//_delay_ms(33);
		//
		//OLED_defineMemAddressArea(0,0,127,0);
		//
		//CommandMode = 0;
		//OLED_addToUSIBuffer(SSD1306_Data_Mode);            				// data mode
		//
		//for(unsigned char i = 0; i < textStart; i++){
		//	OLED_addToUSIBuffer(0x00);
		//}
		//
		//OLED_printString("FRESH RAT");
		//
		//if(textStart == 0){
		//
		//	textStart = 127;
		//
		//} else {
		//
		//	textStart--;
		//
		//}
		//
		//frames++;
		//if(frames > 30){
		//	frames = 0;
		//}

	//}
}
