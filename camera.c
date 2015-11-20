/*
 * Line scan camera code
 * Takes in analog value from camera and feeds through ADC to 
 * get line positions
 * 
 * Author: Zack Teasdale and Luke Boudreau <zft6616@rit.edu, lgb9267@rit.edu>
 * Modified by: 
 * Created: 11/20/2015
 * Modified: 11/20/2015
 */
#include "MK64F12.h"
#include "camera.h"
#include "stdio.h"

/*From clock setup 0 in system_MK64f12.c*/
#define DEFAULT_SYSTEM_CLOCK 20485760u /* Default System clock value */
#define CLOCK					20485760u

static volatile unsigned int SI_TICKER = 0;

void CameraRead()
{
	// do stuff - such help...
}

void CAM_INIT(void){
	GPIO_INIT();
	PIT_INIT();
	PDB_INIT();
	ADC1_INIT();
}

void GPIO_INIT(void){
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK; // Clock
	PORTB_PCR9 |= PORT_PCR_MUX(1); //PTB9
	PORTB_PCR2 |= PORT_PCR_MUX(1); //PTB2
	GPIOB_PDDR |= (1 << 9)|(1 << 2); // output mode
	GPIOB_PDOR |= (1 << 9)|(1 << 2); // turn off
}
void PIT_INIT(void) {


	// Setup periodic interrupt timer (PIT)
	SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;
	// Enable clock for timers
	//PIT_MCR &= ~(PIT_MCR_MDIS_MASK); // I don't think we need this
	// Enable timers to continue in debug mode
	PIT_MCR = PIT_MCR_FRZ_MASK; // In case you need to debug
	// PIT clock frequency is the system clock
	// Load the value that the timer will count down from
	//PIT_LDVAL0 = 0x01389680; // about 1 second
	PIT_LDVAL0 = DEFAULT_SYSTEM_CLOCK/20486; // about 1 second
	// Enable timer interrupts
	PIT_TCTRL0 |= PIT_TCTRL_TIE_MASK;
	// Enable the timer
	PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
	
	// Clear interrupt flag
	PIT_TFLG0 |= PIT_TFLG_TIF_MASK; 
	// Enable PIT interrupt in the interrupt controller
	NVIC_EnableIRQ(PIT0_IRQn);
	
	for(;;){ // ever
	}
}
 
void PDB_INIT(void) {
    //Enable PDB Clock
    SIM_SCGC6 |= SIM_SCGC6_PDB_MASK;
    //PDB0_CNT = 0x0000;
    PDB0_MOD = 50000; // 50,000,000 / 50,000 = 1000
    PDB0_CH1DLY0 = 0;  
    PDB0_SC = PDB_SC_PDBEN_MASK | PDB_SC_CONT_MASK | PDB_SC_TRGSEL(0xf)
              | PDB_SC_LDOK_MASK;
    PDB0_CH1C1 = PDB_C1_EN(0x01) | PDB_C1_TOS(0x01);
}
 
void ADC1_INIT(void) {
    unsigned int calib;
 
    // Turn on ADC0
    SIM_SCGC3 |= SIM_SCGC3_ADC1_MASK;
 
    // Configure CFG Registers
    // Configure ADC to divide 50 MHz down to 6.25 MHz AD Clock, 16-bit single ended
    ADC1_CFG1 |= 0x0000006C;
 
    // Do ADC Calibration for Singled Ended ADC. Do NOT touch.
    ADC1_SC3 = ADC_SC3_CAL_MASK;
    while ( (ADC1_SC3 & ADC_SC3_CAL_MASK) != 0 );
    calib = ADC1_CLP0;
    calib += ADC1_CLP1;
    calib += ADC1_CLP2;
    calib += ADC1_CLP3;
    calib += ADC1_CLP4;
    calib += ADC1_CLPS;
    calib = calib >> 1;
    calib |= 0x8000;
    ADC1_PG = calib;
 
    // Configure SC registers.
    // Select hardware trigger.
    ADC1_SC2 |= 0x00000000;
 
 
    // Configure SC1A register.
    // Select ADC Channel and enable interrupts. Use ADC1 channel DAD3  in single ended mode.
    ADC1_SC1A = 0x00000043;
 
 
    // Enable NVIC interrupt
    NVIC_EnableIRQ(ADC1_IRQn);//ADC1 Interrupt
}
 
// ADC1 Conversion Complete ISR
void ADC1_IRQHandler(void) {
    // Read the result (upper 12-bits). This also clears the Conversion complete flag.
    unsigned short i = ADC1_RA >> 4;
 
    // Do stuff with the result here.
    //Set DAC output value (12bit)
    DAC0_DAT0L = (char)(i & 0x00FF);    //set low 8 bits
    DAC0_DAT0H = (char)(i >> 8);    //set high 4 bits
}

void PIT0_IRQHandler(void){
	if (SI_TICKER <= 265)
	{
		SI_TICKER++;
	}
	else if( SI_TICKER == 266)
	{
		//go high
		PTB->PSOR = (1 << 2);
		SI_TICKER++;
	}
	else
	{
		//go low
		PTB->PCOR = (1 << 2);
		SI_TICKER = 0;
	}
	
	// Clear interrupt
	PIT_TFLG0 |= PIT_TFLG_TIF_MASK;
	// Toggle LED
	PTB->PTOR = (1 << 9);
	return;
}
