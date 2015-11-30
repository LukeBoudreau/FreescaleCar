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
 
 void PID_LOOP(void) {
	 int xPos;
	 double kp,ki,kd;
	 double err;
	 
	 kp = KP;
	 ki = KI;
	 kd = KD;
	 
	 //err = "shit";
	 while(1){
		 xPos = getPos();
	 }
	 
}