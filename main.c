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

int main(void)
{
	uint16_t *fovPtr;
	//int i;
	// Initialize UART and PWM
	initialize();

	// Print welcome over serial
	put("Running... \n\r");
	
	//Generate 20% duty cycle at 10kHz
	//SetMotorDutyCycle(50, 1, 1);
	//SetMotorDutyCycle(50, 0, 1);
	//SetServoDutyCycle(7.85);

	//PID_LOOP();


	for(;;){
		driveCar();
//		fovPtr = getPos();	//7 is center
//		if(fovPtr[5]==0){
//			SetServoDutyCycle(9);
//			SetMotorDutyCycle(40, 1, 1);
//			SetMotorDutyCycle(40, 0, 1);
//		}
//		else if(fovPtr[6]==0){
//			SetServoDutyCycle(8.5);
//			SetMotorDutyCycle(40, 1, 1);
//			SetMotorDutyCycle(40, 0, 1);
//		}
//		else if(fovPtr[7]==0){
//			SetServoDutyCycle(7.85);
//			SetMotorDutyCycle(40, 1, 1);
//			SetMotorDutyCycle(40, 0, 1);
//		}
//		else if(fovPtr[8]==0){
//			SetServoDutyCycle(7);
//			SetMotorDutyCycle(40, 1, 1);
//			SetMotorDutyCycle(40, 0, 1);
//		}
//		else if(fovPtr[9]==0){
//			SetServoDutyCycle(6.5);
//			SetMotorDutyCycle(40, 1, 1);
//			SetMotorDutyCycle(40, 0, 1);
//		}
//		else{
//			SetServoDutyCycle(7.85);
//			SetMotorDutyCycle(40, 1, 0);
//			SetMotorDutyCycle(40, 0, 0);
//		}
	}

	return 0;
}

void initialize()
{
	// Initialize UART
	uart_init();	
	
	// Initialize the FlexTimer
	InitPWM();
	
	//everything else
	init_camera();
}
