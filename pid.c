/*
 * Freescale Cup PID control code
 *

 *
 * Author:  Zack Teasdale and Luke Boudreau
 * Created:  11/30/15
 * Modified:  11/30/15
 */
 
 #include "MK64F12.h"
 #include "camera.h"
 #include "pwm.h"
 #include "uart.h"
 #include "stdio.h"
 //#define KP 0.45
 //#define KI 0.15
 //#define KD 0.20
 //#define xCentered 0.0;
 
void PID_LOOP(void);
double getError(void);
void drivCar(void);
 
void driveCar(void){
	int *fovPos;
	int bLine;
	double duty, speed;
	char str[20];
	//Set DC motors
	SetMotorDutyCycle(38, 1, 1);
	SetMotorDutyCycle(38, 0, 1);
	fovPos = getPos(); // [0] left index, [1] right index (indexs are from 0 to 14);
	
	bLine = (fovPos[1]+fovPos[0])/2;
	bLine = bLine - 33;
	duty = 6.25 + 0.05343333333333*bLine;
	
//	if(bLine > 30){
//		speed = 60 - (1.0/3)*bLine;
//	} else {
//		speed = 40 + (1.0/3)*bLine;
//	}
	
	if( duty < 6.25 ){
		duty = 6.25;
	} else if( duty > 9.5) {
		duty = 9.5;
	}
	
	SetServoDutyCycle(duty);
//	SetMotorDutyCycle(speed, 1, 1);
//	SetMotorDutyCycle(speed, 0, 1);
	
	//sprintf(str, "%lf\r\n", speed);
	//put(str);
	//sprintf(str,"|%i|\r\n", bLine);
	//put(str);
	
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
		 
		 //ServoDutyCycle = clip(ServoDutyCycle,-40,40);
		 ServoDutyCycleOld = ServoDutyCycle;
		 
		 errOld2 = errOld;
		 errOld = xError;
	 }
	 
}
*/

// This function gets the five sections form the camera.
// and calculates the largest error of the five sections,
// and returns a the most incorrect value.
// 
/*
 double getError(void){
	 double xError,xActual;
	 //xActual = getPos();
	 //xError = xCentered - xActual; //Abstract of what we want to do
	 
	 return xError;
}
*/
