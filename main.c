/*
 * Main Method for testing the PWM Code for the K64F
 * PWM signal can be connected to output pins are PC3 and PC4
 * 
 * Author:  luke Zach
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

	// Initialize UART and PWM
	initialize();

	// Print welcome over serial
	put("Running... \n\r");
	
	//Generate 20% duty cycle at 10kHz
	SetMotorDutyCycle(50,1);
	SetMotorDutyCycle(50 ,0);
	SetServoDutyCycle(10);
	
	for(;;) ;  //then loop forever
	

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