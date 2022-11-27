#include "USI_TWI_Master.h"

/**
 * @brief USI TWI single master initialization function
 */
	void USI_TWI_Master_Initialise()
	{

		//set pin B0 and B2 to 1 (high)
		PORT_USI |= (1 << PIN_USI_SDA);                        		// Enable pullup on SDA, to set high as released state.
		PORT_USI |= (1 << PIN_USI_SCL);                        		// Enable pullup on SCL, to set high as released state.

		//set the data direction register for port B as outputs for pin B0 and B2
		DDR_USI |= (1 << PIN_USI_SCL);                            	// Enable SCL as output.
		DDR_USI |= (1 << PIN_USI_SDA);                            	// Enable SDA as output.

		//set USI Data Register with 255
		USIDR = 0xFF;                                            	// Preload dataregister with "released level" data.

		//set USI Control Register
		USICR = (0 << USISIE) | (0 << USIOIE) |                		// Disable Interrupts.
			(1 << USIWM1) | (0 << USIWM0) |                    		// Set USI in Two-wire mode.
			(1 << USICS1) | (0 << USICS0) |
			(1 << USICLK) |                                    		// Software stobe as counter clock source
			(0 << USITC);

		//set USI status register
		USISR = (1 << USISIF) | (1 << USIOIF) | (1 << USIPF) |
			(1 << USIDC) |                                    		// Clear flags,
			(0x0 << USICNT0);                                		// and reset counter (4 bits)

	}
	
/**
 * @brief Function for generating a TWI Start Condition.
 * @return Returns 1 if the signal can be verified, otherwise returns 0
 */
	unsigned char USI_TWI_Master_Start(void)
	{

		/*
					1	2	3	4
				   	 _______
			SCL 	/		\_______
				 	____		 ___
			SDA		    \_______/


			1 - Ensure SCL high
			2 - Pull SDA low
			3 - Pull SCL low
			4 - SDA back to high

		*/

		//bring SCL (Serial Clock) high in case it wasn't already.
		PORT_USI |= (1 << PIN_USI_SCL); 					// Release SCL.
		while(!(PORT_USI & (1 << PIN_USI_SCL))){} 			// Verify that SCL becomes high.
		//_delay_us(T2_TWI);

		/* Generate Start Condition */
		PORT_USI &= ~(1 << PIN_USI_SDA); 					// Force SDA LOW.
		//_delay_us(T4_TWI);
		PORT_USI &= ~(1 << PIN_USI_SCL); 					// Pull SCL LOW.
		PORT_USI |= (1 << PIN_USI_SDA);  					// Release SDA.

		return (1);
	}

/**
 * @brief Function for generating a TWI Stop Condition. Used to release
 * the TWI bus.
 * @return Returns 1 if it was successful
 */
	void USI_TWI_Master_Stop()
	{

		/*
					1	2	3
				   	 	_________
			SCL 	___/

			SDA		\_______/


			1 - Pull SDA low
			2 - SCL high
			3 - SDA high

		*/

		PORT_USI &= ~(1 << PIN_USI_SDA); // Pull SDA low.
		PORT_USI |= (1 << PIN_USI_SCL);  // Release SCL.
		while(!(PIN_USI & (1 << PIN_USI_SCL))){} // Wait for SCL to go high.
		//_delay_us(T4_TWI);
		PORT_USI |= (1 << PIN_USI_SDA); // Release SDA.
		//_delay_us(T2_TWI);

	}

/**
 * @brief Core function for shifting data in and out from the USI.
 * Data to be sent has to be placed into the USIDR prior to calling
 * this function. Data read, will be return'ed f
 * @return Returns the read read from the device
 */
	void USI_TWI_Transfer_byte(unsigned char byte)
	{

		//transferbyte.png

		/*
					1	  2...
				   	     ___	 ___
			SCL 	\___/	\___/	\___
				 		 _______ _______
			SDA		____X_______X_______


			1 - SCL pulled low
			2 - SCL pulsed 9 X - 8 for each bit in the byte, and 1 acknkowledge pulse

		*/

		PORT_USI &= ~(1 << PIN_USI_SCL);         				// Pull SCL LOW.
		USIDR = byte;                        				// Put data in data register

		//USI Status register to match sent settings
		USISR = (1 << USISIF) | (1 << USIOIF) | (1 << USIPF) |
		(1 << USIDC) |    // Prepare register value to: Clear flags, and
		(0x0 << USICNT0); // set USI to shift 8 bits i.e. count 16 clock edges.

		//at this point the SCL is low
		//toggle clock back and forth until USIOIF flag reads high - 1 byte of data is thusly transferred.

		for(unsigned char i = 0; i < 8; i++){
			PORT_USI |= (1 << PIN_USI_SCL);
			while(!(PIN_USI & (1 << PIN_USI_SCL))){} 					// Wait for SCL to go high.
			PORT_USI &= ~(1 << PIN_USI_SCL); 							// Pull SCL LOW.
		}


		//_delay_us(T2_TWI);
		//USI_general_byte = USIDR;                  					// Read out data.
		USIDR = 0xFF;                  									// Clear / Release the data register
		//DDR_USI |= (1 << PIN_USI_SDA); 								// Enable SDA as output.

		//one more clock cycle for the ack bit, that we're ignoring here
		PORT_USI |= (1 << PIN_USI_SCL);
		while(!(PIN_USI & (1 << PIN_USI_SCL))){} 						// Wait for SCL to go high.
		PORT_USI &= ~(1 << PIN_USI_SCL); 								// Pull SCL LOW.

	}

