#ifndef PWM_H_
#define PWM_H_

void SetMotorDutyCycle(unsigned int DutyCycle, int motorLeft, int dir);
void SetServoDutyCycle(double DutyCycle);
void InitPWM();
void PWM_ISR();

#endif /* PWM_H_ */
