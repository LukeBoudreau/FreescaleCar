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
 #define KP 0.45
 #define KI 0.15
 #define KD 0.20
 #define xCentered 0.0;
 
void PID_LOOP(void);
double getError(void);
 
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
		 
		 ServoDutyCycle = clip(ServoDutyCycle,-40,40);
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
	 double xError,xActual;
	 xActual = getPos();
	 xError = xCentered - xActual; //Abstract of what we want to do
	 
	 return xError;
}