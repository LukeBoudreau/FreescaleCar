/*
 * Pulse-Width-Modulation Code for K64
 * PWM signal can be connected to output pins PC3 and PC4
 * 
 * Author: Zack Teasdale and Luke Boudreau
 * Modified by: 
 * Created: 11/20/2015
 * Modified: 12/3/2015
 */
#include "MK64F12.h"
#include "pwm.h"

/*From clock setup 0 in system_MK64f12.c*/
#define DEFAULT_SYSTEM_CLOCK 20485760u /* Default System clock value */
#define CLOCK					20485760u
#define PWM_FREQUENCY			10000
#define SERVO_FREQUENCY   6400
#define FTM0_MOD_VALUE			(CLOCK/PWM_FREQUENCY)
#define FTM3_MOD_VALUE      (CLOCK/SERVO_FREQUENCY)

static volatile unsigned int PWMTick = 0;
static volatile unsigned int PWMTick2 = 0;


/*
 * Change the Motor Duty Cycle and Frequency
 * @param DutyCycle (0 to 100)
 * @param motorRight 0 for Right motor, 1 for Left motor
 * @param dir: 1 for forward, else backwards 
 */
void SetMotorDutyCycle(unsigned int DutyCycle, int motorLeft, int dir)
{
	// Calculate the new cutoff value
	uint16_t mod = (uint16_t) (((CLOCK/PWM_FREQUENCY) * DutyCycle) / 100);
	
	// Set outputs
	if( motorLeft ){
		if(dir){
			FTM0_C2V = 0;
			FTM0_C7V = mod;
		} 
		else {
			FTM0_C7V = 0;
			FTM0_C2V = mod;
		}
	}
	else{
		if(dir){
			FTM0_C3V = mod; 
			FTM0_C6V = 0;
		}
		else{
			FTM0_C6V = mod;
			FTM0_C3V = 0;
		}
	}

	// Update the clock to the new frequency
	FTM0_MOD = (CLOCK/PWM_FREQUENCY);
}

/*
 * Change the Servo Duty Cycle
 * @param DutyCycle (6.25 (left) to 9.5 (right),  7.85 means steer straight)
 */
void SetServoDutyCycle(double DutyCycle)
{
	// Calculate the new cutoff value
	uint16_t mod = (uint16_t) (((CLOCK/SERVO_FREQUENCY) * DutyCycle) / 100);
	
	// Set output
	FTM3_C4V = mod;
	
	// Update the clock to the new frequency
	FTM3_MOD = (CLOCK/SERVO_FREQUENCY);
}


/*
 * Initialize the FlexTimer for PWM
 */
void InitPWM(void)
{
	// 12.2.13 Enable the Clock to the FTM0 Module
	SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK;
	SIM_SCGC3 |= SIM_SCGC3_FTM3_MASK;
	
	// Enable clock on PORT A so it can output
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK;
	
	// 11.4.1 Route the output of TPM channel 0 to the pins
	// Use drive strength enable flag to high drive strength
	//These port/pins may need to be updated for the K64 <Yes, they do. Here are two that work.>
    PORTC_PCR3  = PORT_PCR_MUX(4)  | PORT_PCR_DSE_MASK; //FTM0 Ch2
    PORTC_PCR4  = PORT_PCR_MUX(4)  | PORT_PCR_DSE_MASK; //FTM0 Ch3
	PORTA_PCR2  = PORT_PCR_MUX(3)  | PORT_PCR_DSE_MASK; //FTM0 Ch7
	PORTA_PCR1  = PORT_PCR_MUX(3)  | PORT_PCR_DSE_MASK; //FTM0 Ch6
	PORTC_PCR8  = PORT_PCR_MUX(3)  | PORT_PCR_DSE_MASK; //FTM3 Ch4
	
	// 39.3.10 Disable Write Protection
	FTM0_MODE |= FTM_MODE_WPDIS_MASK;
	FTM3_MODE |= FTM_MODE_WPDIS_MASK;
	
	// 39.3.4 FTM Counter Value
	// Initialize the CNT to 0 before writing to MOD
	FTM0_CNT = 0;
	FTM3_CNT = 0;
	
	// 39.3.8 Set the Counter Initial Value to 0
	FTM0_CNTIN = 0;
	FTM3_CNTIN = 0;
	
	// 39.3.5 Set the Modulo register
	FTM0_MOD = FTM0_MOD_VALUE;
	FTM3_MOD = FTM3_MOD_VALUE;
	//FTM0->MOD = (DEFAULT_SYSTEM_CLOCK/(1<<7))/1000;

	// 39.3.6 Set the Status and Control of both channels
	// Used to configure mode, edge and level selection
	// See Table 39-67,  Edge-aligned PWM, High-true pulses (clear out on match)
	FTM0_C3SC |= FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;
	FTM0_C3SC &= ~FTM_CnSC_ELSA_MASK;
	
	// See Table 39-67,  Edge-aligned PWM, Low-true pulses (clear out on match)
	FTM0_C2SC |= FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;
	FTM0_C2SC &= ~FTM_CnSC_ELSA_MASK;
	
	FTM0_C7SC |= FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;
	FTM0_C7SC &= ~FTM_CnSC_ELSA_MASK;
	
	FTM0_C6SC |= FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;
	FTM0_C6SC &= ~FTM_CnSC_ELSA_MASK;
	
	// Use Channel 4 on FTM3, goes to PTC8
	FTM3_C4SC |= FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;
	FTM3_C4SC &= ~FTM_CnSC_ELSA_MASK;
	
	// 39.3.3 FTM Setup
	// Set prescale value to 1 
	// Chose system clock source
	// Timer Overflow Interrupt Enable
	FTM0_SC = FTM_SC_PS(0) | FTM_SC_CLKS(1) | FTM_SC_TOIE_MASK;
	FTM3_SC = FTM_SC_PS(7) | FTM_SC_CLKS(1) | FTM_SC_TOIE_MASK;

	// Enable Interrupt Vector for FTM
  NVIC_EnableIRQ(FTM0_IRQn);
	NVIC_EnableIRQ(FTM3_IRQn);
	
}

/*OK to remove this ISR?*/
void FTM0_IRQHandler(void){ //For FTM timer

  FTM0_SC &= ~FTM_SC_TOF_MASK;
  
	//if motor tick less than 255 count up... 
	if (PWMTick < 0xff)
		PWMTick++;
  
	
}

void FTM3_IRQHandler(void){
	FTM3_SC &= ~FTM_SC_TOF_MASK;
	
	if (PWMTick2 < 0xff)
		PWMTick2++;
}
