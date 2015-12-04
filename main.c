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
#include "camera.h"
#include "pid.h"

void initialize(void);

int main(void)
{
	// Initialize UART, PWM, Camera
	initialize();

	
	//Generate 20% duty cycle at 10kHz
	//SetMotorDutyCycle(50, 1, 1);
	//SetMotorDutyCycle(50, 0, 1);
	//SetServoDutyCycle(7.85);

	//main loop();
	put("Waiting... \n\r");
//	while( 1 ) {
//		put("Entered loop \n\r");
//		if( (GPIOC_PDIR&(1<<6)) == 0 ){
//			break;
//		}
//		
//	}
	
		// Print welcome over serial
	put("Running... \n\r");
	
	for(;;){
			driveCar();
			//PID_LOOP();
	}

	//return 0;	//unnecessary
}

void initialize()
{
		// Button start enabled
	// Enable clock for Port C PTC6 button
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK; 
	
	// Configure the Mux for the button
	PORTC_PCR6 = PORT_PCR_MUX(1);
	GPIOC_PDDR &= ~(1<<6);

	// Set the push button as an input
	
	
	// Initialize UART
	uart_init();	
	
	// Initialize the FlexTimer
	InitPWM();
	
	//everything else
	init_camera();
	

}
