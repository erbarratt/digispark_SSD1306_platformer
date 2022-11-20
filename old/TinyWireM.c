/*!
* @file TinyWireM.c
*
* @mainpage Adafruit TinyWireM Library
*
* @section intro_sec Introduction
*
* TinyWireM.cpp - a wrapper class for TWI/I2C Master library for the ATtiny on
* Arduino 1/21/2011 BroHogan -  brohoganx10 at gmail dot com
*
* **** See TinyWireM.h for Credits and Usage information ****
*
* @section license License
*
* This library is free software; you can redistribute it and/or modify it under
* the terms of the GNU General Public License as published by the Free Software
* Foundation; either version 2.1 of the License, or any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
* FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
* details.
*/

//extern "C" {
//#include "USI_TWI_Master.h"
//#include <USI_TWI_Master.h>
//#include <USI_TWI_Master\USI_TWI_Master.h>
//#include <USI_TWI_Master/USI_TWI_Master.h>
//}

#include "TinyWireM.h"

// Initialize Class Variables //////////////////////////////////////////////////
unsigned char USI_Buf[USI_BUF_SIZE]; // holds I2C send and receive data
unsigned char USI_BufIdx = 0;     // current number of bytes in the send buff
//unsigned char USI_LastRead = 0;   // number of bytes read so far
//unsigned char USI_BytesAvail = 0; // number of bytes requested but not read

// Public Methods //////////////////////////////////////////////////////////////

// int peek(){}
// void flush(){}

	void tw_begin() { // initialize I2C lib
		USI_TWI_Master_Initialise();
	}

	void tw_setAddress( unsigned char slaveAddr) { // setup address & write bit
		USI_BufIdx = 0;
		USI_Buf[USI_BufIdx] = (slaveAddr << TWI_ADR_BITS) | USI_SEND;
	}

	size_t tw_write(unsigned char data) { // buffers up data to send
		if (USI_BufIdx >= USI_BUF_SIZE - 1){
			return 0;   // dont blow out the buffer
		}
		USI_BufIdx++; // inc for next byte in buffer
		USI_Buf[USI_BufIdx] = data;
		return 1;
	}

	//unsigned char endTransmission() { return endTransmission(1); }

	unsigned char tw_doTransmission(unsigned char stop) { // actually sends the buffer
		bool xferOK = false;
		unsigned char errorCode;
		xferOK = USI_TWI_Start_Read_Write( USI_Buf, USI_BufIdx + 1); // core func that does the work
		USI_BufIdx = 0;
		if (xferOK) {
			if (stop) {
				errorCode = USI_TWI_Master_Stop();
				if (errorCode == 0) {
					errorCode = USI_TWI_Get_State_Info();
					return errorCode;
				}
			}
			return 0;
		} else { // there was an error
			errorCode = USI_TWI_Get_State_Info(); // this function returns the error number
			return errorCode;
		}
	}

	//unsigned char tw_requestFrom(unsigned char slaveAddr, unsigned char numBytes) { // setup for receiving from slave
	//	bool xferOK = false;
	//	unsigned char errorCode = 0;
	//	USI_LastRead = 0;
	//	USI_BytesAvail = numBytes; // save this off in a global
	//	numBytes++;                // add extra byte to transmit header
	//	USI_Buf[0] = (slaveAddr << TWI_ADR_BITS) | USI_RCVE; // setup address & Rcve bit
	//	xferOK = USI_TWI_Start_Read_Write(USI_Buf, numBytes); // core func that does the work
	//	// USI_Buf now holds the data read
	//	if (xferOK) {
	//		errorCode = USI_TWI_Master_Stop();
	//		if (errorCode == 0) {
	//			errorCode = USI_TWI_Get_State_Info();
	//			return errorCode;
	//		}
	//		return 0;
	//	} else { // there was an error
	//		errorCode = USI_TWI_Get_State_Info(); // this function returns the error number
	//		return errorCode;
	//	}
	//}

	//unsigned char tw_receive(void) {
	//	int c = tw_read();
	//	if (c < 0){
	//		return 0;
	//	}
	//	return c;
	//}

	//int tw_read() { // returns the bytes received one at a time
	//	USI_LastRead++;     // inc first since first unsigned char read is in USI_Buf[1]
	//	return USI_Buf[USI_LastRead];
	//}
	//
	//int tw_available() { // the bytes available that haven't been read yet
	//	return USI_BytesAvail - (USI_LastRead);
	//}
	//
	//void tw_end() { USI_TWI_Master_Stop(); }
