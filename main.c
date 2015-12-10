/*
 * Main Method for testing the PWM Code for the K64F
 * PWM signal can be connected to output pins are PC3 and PC4
 * 
 * Author:  Luke Boudreau and Zack Teasdale
 * Created:  10/7/2015
 * Modified:  12/3/2015
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

	//main loop();
	put("Waiting... \n\r");
	
	// Print welcome over serial
	put("Running... \n\r");
	
	for(;;){
			driveCar();
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

	// Initialize UART
	uart_init();	
	
	// Initialize the FlexTimer
	InitPWM();
	
	//everything else
	init_camera();
	

}
