/*----------------------------------------------------------------------------
 * Name:    s_beaconSignal.c
 * Purpose: This file contains the SERVICE beacon signal emission.
 *					Initializes, configurates and activates timers with PWM mode.  
 *
 * Version: V1.0
 * Ahthor: G.Fauxpoint
 */


/******************************************************************************
* 
*   INCLUDED FILES
*
******************************************************************************/

#include "s_beaconSignal.h"

/******************************************************************************
*
*   GLOBAL VARIABLES
*
******************************************************************************/

/** Timer's Resolution */
vu16 resolution_pwm1;
vu16 resolution_pwm2;
vu16 resolution_pwm3;
vu16 resolution_pwm4;

/** pwm state */
State_PWM state_pwm = PWM_ZERO;

/******************************************************************************
*
*   PRIVATE FUNCTIONS
*
******************************************************************************/

void enableSystick()
{
	SysTick_On;
	SysTick_Enable_IT;
}

void s_beaconSignal_initialization(void (*function) (void))
{	
	// Clock's configuration
	CLOCK_Configure();	
	
	// GPIOs configuration
	GPIO_Configure(GPIOA, 8, OUTPUT, ALT_PPULL); 		// PWM1, TIM1_CH1
	GPIO_Configure(GPIOA, 0, OUTPUT, ALT_PPULL); 		// PWM2, TIM2_CH2 
	GPIO_Configure(GPIOA, 6, OUTPUT, ALT_PPULL); 		// PWM3, TIM3_CH1 
	GPIO_Configure(GPIOB, 6, OUTPUT, ALT_PPULL); 		// PWM4, TIM4_CH2 
	
	GPIO_Configure(GPIOB, 8, OUTPUT, OUTPUT_PPULL);	// LED (On/Off)
	GPIO_Configure(GPIOB, 9, OUTPUT, OUTPUT_PPULL);	// LED (On/Off)
	GPIO_Configure(GPIOB, 10, OUTPUT, OUTPUT_PPULL);	// LED (On/Off)
	GPIO_Configure(GPIOB, 11, OUTPUT, OUTPUT_PPULL);	// LED (On/Off)
	GPIO_Configure(GPIOB, 12, OUTPUT, OUTPUT_PPULL);	// LED (On/Off)
	GPIO_Configure(GPIOB, 13, OUTPUT, OUTPUT_PPULL);	// LED (On/Off)
	GPIO_Configure(GPIOB, 14, OUTPUT, OUTPUT_PPULL);	// LED (On/Off)
	GPIO_Configure(GPIOB, 15, OUTPUT, OUTPUT_PPULL);	// LED (On/Off)
	
	GPIO_Configure(GPIOC, 13, INPUT, INPUT_PULL_DOWN_UP);	// LED (On/Off)
	
	GPIO_Set(GPIOB,8);	// set ON
	
	// PWM signals configuration
	resolution_pwm1 = PWM_Init(TIM1, 1, FPWM1);	// timer1 channel2 configuration : mode PWM with Fpwm 
	resolution_pwm1 = resolution_pwm1 + 1;	// (ARRresolution + 1)
	resolution_pwm2 = PWM_Init(TIM2, 1, FPWM2);	// timer1 channel2 configuration : mode PWM with Fpwm 
	resolution_pwm2 = resolution_pwm2 + 1;	// (ARRresolution + 1)
	resolution_pwm3 = PWM_Init(TIM3, 1, FPWM3);	// timer1 channel2 configuration : mode PWM with Fpwm 
	resolution_pwm3 = resolution_pwm2 + 1;	// (ARRresolution + 1)
	resolution_pwm4 = PWM_Init(TIM4, 1, FPWM4);	// timer1 channel2 configuration : mode PWM with Fpwm 
	resolution_pwm4 = resolution_pwm4 + 1;	// (ARRresolution + 1)
	
	
	// Systick clock configuration
	Systick_Period(SYSTICK_PERIOD); //[us]  
	Systick_Prio_IT(PRIORITY_BEACONS, function); // Priority 2 for Emission_PWM, PRIORITY_BEACONS = 2
	
	state_pwm = PWM_PULSE;
					
	enableSystick();
}
 
void s_beaconSignal_emission_PWM()		
{
	static char PwmPulsePeriod = 0;
	static char PwmZeroPeriod = 0;
		
	// pwm emission
	switch (state_pwm)
	{
		case PWM_PULSE:
		s_beaconSignal_pulse();
		
		GPIO_Set(GPIOB,11);
		GPIO_Clear(GPIOB,12);
		GPIO_Clear(GPIOB,13);
		
		PwmPulsePeriod ++;
		
		if (PwmPulsePeriod >= PwmOnNumberPeriodSystick)
		{
			state_pwm = PWM_ZERO;
			PwmPulsePeriod = 0;
		}
		break;
		
		case PWM_ZERO:
		s_beaconSignal_zero();
		
		GPIO_Set(GPIOB,12);
		GPIO_Clear(GPIOB,11);
		GPIO_Clear(GPIOB,13); 	
	
		PwmZeroPeriod ++;
		
		if (PwmZeroPeriod >= PwmOffNumberPeriodSystick)
		{
			state_pwm = PWM_PULSE;
			PwmZeroPeriod = 0;
		}
		break;
		
		case PWM_RESET:
		s_beaconSignal_zero();	
		GPIO_Set(GPIOB,13);
		GPIO_Clear(GPIOB,12);
		GPIO_Clear(GPIOB,11);	
		
		PwmZeroPeriod = 0;
		PwmPulsePeriod = 0;
		
		break;
	}
}	

void s_beaconSignal_pulse(void)
{
	// PWM emission before the first Systick interruption
	PWM_Valeur(TIM1,1)=(resolution_pwm1*DUTYCYCLE_50);
	PWM_Valeur(TIM2,1)=(resolution_pwm2*DUTYCYCLE_50);
	PWM_Valeur(TIM3,1)=(resolution_pwm3*DUTYCYCLE_50);
	PWM_Valeur(TIM4,1)=(resolution_pwm4*DUTYCYCLE_50);
}

void s_beaconSignal_zero(void)
{
	// PWM emission before the first Systick interruption
	PWM_Valeur(TIM1,1)=(resolution_pwm1*DUTYCYCLE_0);
	PWM_Valeur(TIM2,1)=(resolution_pwm2*DUTYCYCLE_0);
	PWM_Valeur(TIM3,1)=(resolution_pwm3*DUTYCYCLE_0);
	PWM_Valeur(TIM4,1)=(resolution_pwm4*DUTYCYCLE_0);
	
}


int GetStateTampButton()
{
	return GPIO_Read(GPIOC,13);
}