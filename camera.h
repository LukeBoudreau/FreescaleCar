#ifndef CAMERA_H_
#define CAMERA_H_

void init_FTM2(void);
void init_GPIO(void);
void init_PIT(void);
void init_ADC0(void);
void FTM2_IRQHandler(void);
void PIT1_IRQHandler(void);
void ADC0_IRQHandler(void);
void init_camera(void);
int * getPos(void);
void driveCar(void);

#endif /* CAMERA_H_ */
