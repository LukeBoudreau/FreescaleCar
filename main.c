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
#include "PID.h"

void initialize(void);
void en_interrupts(void);

int main(void)
{

	// Initialize UART and PWM
	initialize();

	// Print welcome over serial
	put("Running... \n\r");
	
	//Generate 20% duty cycle at 10kHz
	//SetMotorDutyCycle(50, 1, 1);
	//SetMotorDutyCycle(50, 0, 1);
	SetServoDutyCycle(7.85);
	init_camera();
	PID_LOOP();


	return 0;
}

void initialize()
{
	// Initialize UART
	uart_init();	
	
	// Initialize the FlexTimer
	InitPWM();
	
	//everything else
	//CAM_INIT();
}
