/*
 * Freescale Cup PID control code
 *

 *
 * Author:  Zack Teasdale and Luke Boudreau
 * Created:  11/30/15
 * Modified:  12/3/15
 */
 
 #include "MK64F12.h"
 #include "camera.h"
 #include "pwm.h"
 #include "uart.h"
 #include "stdio.h"
 //#define KP 0.05343333333333
 //#define KI 0.0
 //#define KD 0.0
 #define xCentered 0.0;
 
void PID_LOOP(void);
double getError(void);
void drivCar(void);
 

void driveCar(void){
	int *fovPos;
	int bLine;
	double duty;
	char str[20];

	fovPos = getPos(); // [0] left index, [1] right index (indexs are from 0 to 14);
	
	bLine = (fovPos[1]+fovPos[0])/2;
	bLine = bLine - 33;
	sprintf(str, "%i\r\n", bLine);
	put(str);
	duty = 6.25 + 0.05343333333333*bLine;
	
	if( duty < 6.25 ){
		duty = 6.25;
		SetMotorDutyCycle(18, 1, 1);
		SetMotorDutyCycle(58, 0, 1);
	} else if( duty > 9.5) {
		duty = 9.5;
		SetMotorDutyCycle(18, 1, 1);
		SetMotorDutyCycle(58, 0, 1);
	} else {
		//Set DC motors
		SetMotorDutyCycle(38, 1, 1);	//left motor
		SetMotorDutyCycle(38, 0, 1);	//right motor
	}
	
	SetServoDutyCycle(duty);
	
}


/*
void PID_LOOP(void) {
	 double xError,errOld,errOld2;
	 double kp,ki,kd;
	 double ServoDutyCycleOld, ServoDutyCycle;
	 
	 //Initialize
	 kp = KP;
	 ki = KI;
	 kd = KD;
	 xError = 0.0;
	 errOld = 0.0;
	 errOld2 = 0.0;
	 ServoDutyCycleOld = 7.85; //straight
	 
	 while(1){
		 xError = getError();
		 ServoDutyCycle = ServoDutyCycleOld + kp*(xError-errOld) + 
											ki*(xError-errOld) +
											kd*(xError-2*errOld+errOld2);
		 
		 if( ServoDutyCycle < 6.25 ){
			 ServoDutyCycle = 6.25;
		 } else if( ServoDutyCycle > 9.5) {
			 ServoDutyCycle = 9.5;
		 } else {
			 SetMotorDutyCycle(42, 1, 1);	//left motor
			 SetMotorDutyCycle(42, 0, 1);	//right motor
		 }
		 ServoDutyCycleOld = ServoDutyCycle;
		 
		 errOld2 = errOld;
		 errOld = xError;
	 }
	 
}


// This function gets the five sections form the camera.
// and calculates the largest error of the five sections,
// and returns a the most incorrect value.
// 

 double getError(void){
	 int bLine;
	 int *fovPos;
	 double xError;

	 fovPos = getPos();
	 bLine = (fovPos[1]+fovPos[0])/2;
	 bLine = bLine - 33;
	 
	 xError = (30 - bLine)/100.0;
	 if( xError < 0.0 ){
		 xError = xError*-1.0;
	 }
	 
	 return xError;
}
*/
