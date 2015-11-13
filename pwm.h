#ifndef PWM_H_
#define PWM_H_

void SetMotorDutyCycle(unsigned int DutyCycle, int motorRight);
void SetServoDutyCycle(unsigned int DutyCycle);
void InitPWM();
void PWM_ISR();

#endif /* PWM_H_ */
