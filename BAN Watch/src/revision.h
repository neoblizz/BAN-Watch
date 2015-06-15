

//void BANTransfer(void) {
	//
	//BANTx_init();
	//
	//// START BITS
	//PORTA |= (1 << PORTA3);
	//PORTK |= (1 << PORTK1);
	//_delay_ms (10); // 10 ms delay
	//PORTA |= (1 << PORTA3);
	//PORTK |= (1 << PORTK1);
	//_delay_ms (10); // 10 ms delay
	//PORTA |= (1 << PORTA3);
	//PORTK |= (1 << PORTK1);
	//_delay_ms (10); // 10 ms delay
		//
	///* Prints the string to a pin PK & PA */
	//for (int j = 0; j < strlen(bruce); j++) {
			//
		///* Prints the characters to pin PK & PA */
		//for (int i = 0; i < 8; i++) {
//
			///* This algorithm is really important, as it
				//* sends data over a single pin on the port 
				//*/
					//
			//// DATA
			//PORTA = (1 << PORTA3) & (((bruce[j] >> i) & 1) << PORTA3);	// LED DEBUG
			//PORTK = (1 << PORTK1) & (((bruce[j] >> i) & 1) << PORTK1);	// PAD OUTPUT
			//
			///* Do not use software delays. */
			//_delay_ms (5); // 5 ms delay
			//
		//}
	//}
		//
	//// END BITS
	//PORTA &= ~(1 << PORTA3);
	//PORTK &= ~(1 << PORTK1);
	//_delay_ms (10); // 10 ms delay
	//PORTA &= ~(1 << PORTA3);
	//PORTK &= ~(1 << PORTK1);
	//_delay_ms (10); // 10 ms delay
	//PORTA &= ~(1 << PORTA3);
	//PORTK &= ~(1 << PORTK1);
	//_delay_ms (10); // 10 ms delay
//}
//
//char* BANReceival(void) {
	//
	//uint8_t receive[94];
	//uint8_t decipher_rx = 0;
	//char received[11];
	//
	//BANRx_init();
	//
	//// SEND BITS: DATA READY?
	//for (int i = 0; i < 3; i++) {
		//receive[i] = PORTK & 1;
		//_delay_ms(10);
	//}
	//
	//// ACTUAL DATA: Bruce Qiang
	//for (int j = 3; j < 90; j++) {
		//receive[j] = PORTK & 1;
		//_delay_ms(5);
	//}
	//
	//// END BITS: DATA DONE?
	//for (int k = 90; k < 94; k++) {
		//receive[k] = PORTK & 1;
		//_delay_ms(10);
	//}
	//
	//int letter = 3;
	//
	//if ((receive[0] == 1 && receive[1] == 1) && (receive[90] == 0 && receive[90] == 0)) {
		//for (int n = 0; n < 11; n++) {
			//
			//for (int m = 0; m < 8; m++) {
				//decipher_rx |= (receive[letter] << m);
				//letter++;
			//}
			//received[n] = (char) decipher_rx;
		//}
	//}
	//
	//_delay_ms(100);
	//
	//for (cnt = 0; cnt < strlen(received); cnt++) {
		//uart_putchar(received[cnt]);
	//}
	//_delay_ms(10);
//
	//return received;
//}
//
//void BANTx_init (void) {
	//// TIMER & LED (PORTK) AS OUTPUTS
	//DDRK = 0xFF;
	//PORTK = 0xFF;
	//PORTK = 0;
	//
	//// TIMER & LED (PORTA) AS OUTPUTS
	//DDRA = 0xFF;
	//PORTA = 0xFF;
	//PORTA = 0;
//}
//
//void BANRx_init (void) {
	//// TIMER & LED (PORTK) AS INPUTS
	//DDRK = 0x00;
	//PORTK = 0xFF;
	//PORTK = 0;
//}
//
//#ifdef PCICR
		///* Enable pin change interrupt for PD4 which is controlled by SW CTL
		 //* First we need to enable pin change interrupt for the wanted port.
		 //*/
		//PCICR = (1 << PCIE0);
//
		//// Then we need to set the pin change port mask to get the bit we want.
		//PCMSK0 = (1 << PCINT4);
	//#endif