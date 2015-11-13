/*
 * Main Method for testing the PWM Code for the K64F
 * PWM signal can be connected to output pins are PC3 and PC4
 * 
 * Author:  luke Zach and Anthony
 * Created:  10/7/2015
 * Modified:  today
 */

#include "MK64F12.h"
#include "uart.h"
#include "PWM.h"

void initialize();
void en_interrupts();
void delay();

int main(void)
{
	int forward = 1;
	int phase = 0;
	// Initialize UART and PWM
	initialize();

	// Print welcome over serial
	put("Running... \n\r");
	
	//Step 3
	//Generate 20% duty cycle at 10kHz
	//SetDutyCycle(20,10000,1);
	
	//for(;;) ;  //then loop forever
	
	//Step 9
//	for(;;)  //loop forever
//	{
//		uint16_t dc = 0;
//		uint16_t freq = 10000; /* Frequency = 10 kHz */
//		uint16_t dir = 0;
//		char c = 48;
//		int i=0;
//		
//		// 0 to 100% duty cycle in forward direction
//		for (i=0; i<100; i++){
//			SetDutyCycle(i, 10000, 1);
//			delay(10);
//		}
//		
//		// 100% down to 0% duty cycle in the forward direction
//		for (i=100; i>=0; i--){
//			SetDutyCycle(i, 10000, 1);
//			delay(10);
//		}
//		
//		// 0 to 100% duty cycle in reverse direction
//		for (i=0; i<100; i++){
//			SetDutyCycle(i, 10000, 0);
//			delay(10);
//		}
//		
//		// 100% down to 0% duty cycle in the reverse direction
//		for (i=100; i>=0; i--){
//			SetDutyCycle(i, 10000, 0);
//			delay(10);
//		}
//	}
	//Enable clocks on Port D
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;
	//Configure the signal mux for the Port D GPIO pins
	PORTD_PCR0 = PORT_PCR_MUX(1);
	PORTD_PCR1 = PORT_PCR_MUX(1);
	PORTD_PCR2 = PORT_PCR_MUX(1);
	PORTD_PCR3 = PORT_PCR_MUX(1);
	//Configure the GPIO Pins for Output
	GPIOD_PDDR = (1<<0)|(1<<1)|(1<<2)|(1<<3);
	forward=0;
	while(1) {
		//turn off all coils, set the GPIO pins to 0
		GPIOD_PCOR = (1<<0)|(1<<1)|(1<<2)|(1<<3);
		//Set one pin at a time to high
		if(forward){
			if (phase == 0) {
				// turn on coil A
				GPIOD_PSOR = (1<<0);
				phase++;
			}   //A,1a
			else if(phase == 1) {
				//turn on coil B
				GPIOD_PSOR = (1<<1);
				phase++;
			}   //B,2a
			else if(phase == 2) {
				//turn on coil C
				GPIOD_PSOR = (1<<2);
				phase++;
			}   //C,1b
			else { 
				//turn on coil D
				GPIOD_PSOR = (1<<3);
				phase=0;
			}   //D,2b
		}
		else {//reverse
			if (phase == 0) { 
			//turn on coil D
				GPIOD_PSOR = (1<<3);
				phase++;
			}   //D,2b
			else if(phase == 1) {
				//turn on coil C 
				GPIOD_PSOR = (1<<2);
				phase++;
			}  //C,1b
			else if(phase == 2) {
				//turn on coil B
				GPIOD_PSOR = (1<<1);
				phase++;
			}  //B,2a
			else { 
				//turn on coil A 
				GPIOD_PSOR = (1<<0);
				phase=0;
			}  //A,1a
		}
		//Note- you need to write your own delay function
		delay(5);	//smaller values = faster speed
	}
	return 0;
}


/**
 * Waits for a delay (in milliseconds)
 * 
 * del - The delay in milliseconds
 */
void delay(int del){
	int i;
	for (i=0; i<del*50000; i++){
		// Do nothing
	}
}

void initialize()
{
	// Initialize UART
	uart_init();	
	
	// Initialize the FlexTimer
	InitPWM();
}
