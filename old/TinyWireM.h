/*!
 * @file TinyWireM.h
 *
 * TinyWireM.h - a wrapper(+) class for TWI/I2C Master library for the ATtiny on
 *Arduino 1/21/2011 BroHogan -  brohoganx10 at gmail dot com
 *
 * Thanks to 'jkl' for the gcc version of Atmel's USI_TWI_Master code
 * http://www.cs.cmu.edu/~dst/ARTSI/Create/PC%20Comm/
 * I added Atmel's original Device dependant defines section back into
 *USI_TWI_Master.h
 *
 *
 * NOTE! - It's very important to use pullups on the SDA & SCL lines! More so
 *than with the Wire lib.
 *
 * USAGE is modeled after the standard Wire library . . .
 * Put in setup():
 *	TinyWireM.begin(){                               // initialize I2C lib
 * To Send:
 *	TinyWireM.beginTransmission(unsigned char slaveAddr){  // setup slave's
 *address (7 bit address - same as Wire) TinyWireM.send(unsigned char data){ // buffer
 *up bytes to send - can be called multiple times someByte =
 *TinyWireM.endTransmission(){          // actually send the bytes in the buffer
 *	                                                 // returns (optional) 0
 *= sucess or see USI_TWI_Master.h for error codes To Receive: someByte =
 *TinyWireM.requestFrom(unsigned char slaveAddr, unsigned char numBytes){      // reads
 *'numBytes' from slave's address
 *	                                                 // (usage optional)
 *returns 0= success or see USI_TWI_Master.h for error codes someByte =
 *TinyWireM.receive(){                  // returns the next byte in the received
 *buffer - called multiple times someByte = TinyWireM.available(){ // returns
 *the number of unread bytes in the received buffer
 *
 *	TODO:	(by others!)
 *	- merge this class with TinyWireS for master & slave support in one
 *library
 *
 *	This library is free software; you can redistribute it and/or modify it
 *under the terms of the GNU General Public License as published by the Free
 *Software Foundation; either version 2.1 of the License, or any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT
 *ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 *FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 *details.
 */

#ifndef TinyWireM_h
#define TinyWireM_h

	//#include "Arduino.h"
	#include "../../../.platformio/packages/toolchain-atmelavr/lib/gcc/avr/7.3.0/include/stdint.h"
	#include "../../../.platformio/packages/toolchain-atmelavr/lib/gcc/avr/7.3.0/include/stddef.h"
	#include "../../../.platformio/packages/toolchain-atmelavr/lib/gcc/avr/7.3.0/include/stdbool.h"
	#include "../lib/TinyWire/src/USI_TWI_Master.h"

	#define USI_SEND 0      //!< indicates sending to TWI
	#define USI_RCVE 1      //!< indicates receiving from TWI
	#define USI_BUF_SIZE 18 //!< bytes in message buffer

	extern unsigned char USI_Buf[];      // holds I2C send and receive data
	extern unsigned char USI_BufIdx;     // current number of bytes in the send buff
	//extern unsigned char USI_LastRead;   // number of bytes read so far
	//extern unsigned char USI_BytesAvail; // number of bytes requested but not read


	/*!
	* @brief Initialize library for main function
	*/
		void tw_begin();

	/*!
	* @brief Setup address & write bit
	* @param slaveAddr Secondary device address
	*/
		void tw_setAddress(unsigned char);

	/*!
	* @brief Buffers up data to send
	* @param data Data to send
	* @return Returns 1 when successful
	*/
		size_t tw_write(unsigned char);

	/*!
	* @brief Sends data
	* @param d Data buffer
	* @param n How much data to send
	* @return Returns 1 when successful
	*/
	//size_t write(unsigned char *d, unsigned char n) {
		//uint16_t i;
		//for (i = 0; i < n; i++){
		//	write(d[i]);
		//}
		//return (size_t) n;
	//}

	/*!
	* @brief Sends data
	* @param n Data to send
	* @return Returns 1 when successful
	*/
		//inline size_t write(unsigned long n) { return write((unsigned char)n); }

	/*!
	* @brief Sends data
	* @param n Data to send
	* @return Returns 1 when successful
	*/
		//inline size_t write(long n) { return write((unsigned char)n); }

	/*!
	* @brief Sends data
	* @param n Data to send
	* @return Returns 1 when successful
	*/
		//inline size_t write(unsigned int n) { return write((unsigned char)n); }

	/*!
	* @brief Sends data
	* @param n Data to send
	* @return Returns 1 when successful
	*/
		//inline size_t write(int n) { return write((unsigned char)n); }

	/*!
	* @brief Buffers up data to send
	* @param b Data to send
	* @return Returns 1 when successful
	*/
		//void tw_write(unsigned char b) { tw_write(b); }

	/*!
	* @brief Sends data
	* @param d Buffer to send from
	* @param n How much to send from buffer
	* @return Returns 1 when successful
	*/
		//void send(unsigned char *d, unsigned char n) { write(d, n); }

	/*!
	* @brief Sends data
	* @param n Data to send
	* @return Returns 1 when successful
	*/
		//void send(int n) { write((unsigned char)n); }

	/*!
	* @brief Ends the transmission
	* @return Returns the error code if there was one
	*/
		//unsigned char endTransmission();

	/*!
	* @brief Ends the transmission
	* @param stop Buffer to send to end the transmission
	* @return Returns the error code if there was one
	*/
		unsigned char tw_doTransmission(unsigned char);

	/*!
	* @brief Setup for receiving from secondary
	* @param slaveAddr Secondary device address
	* @param numBytes How many bytes to request
	* @return Returns 0, if there was an error, returns the error code
	*/
		//unsigned char tw_requestFrom(unsigned char, unsigned char);

	/*!
	* @brief Returns the bytes received one at a time
	* @return Returns the bytes received one at a time
	*/
		//int tw_read();

	/*!
	* @brief The bytes available htat haven't been read yet
	* @return Returns how many bytes are available
	*/
		//int tw_available();

	/*!
	* @brief Returns the top value
	* @return Returns the top value
	*/
		//int ptw_eek(void);

	/*!
	* @brief Flushes the buffer
	*/
		//void tw_flush(void);

	/*!
	* @brief Receives data from the device
	* @return Returns the data
	*/
		//unsigned char tw_receive(void);

	/*!
	* @brief Function for generating a TWI Stop Condition. Used to release
	* the TWI bus
	*/
	//void tw_end();

#endif
