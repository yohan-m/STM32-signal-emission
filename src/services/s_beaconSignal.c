/**
 * @file s_beaconSignal.c
 * @brief Beacon signal emission file core
 *
 *      This file contains the SERVICE beacon signal emission.
 *			Initializes, configurates and activates timers with PWM mode. 
 *
 * @author Martin
 * @version 0.0.1
 * @date 08 Nov 2013
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

/** ???*/
char PwmOnNumberPeriodSystick = PwmOnPeriod/SYSTICK_PERIOD;
char PwmOffNumberPeriodSystick = PwmOffPeriod/SYSTICK_PERIOD;

/******************************************************************************
*
*   PRIVATE FUNCTIONS
*
******************************************************************************/


/**
 *******************************************************************************
 * s_beaconSignal_initialization
 *
 *      Configure all clocks and registers.
 *			Initialize all GPIOs and Timers
 * 			
 * @param void
 * @return void
 ******************************************************************************/

void s_beaconSignal_initialization(void)
{	
	// GPIOs configuration
	GPIO_Configure(GPIOA, 8, OUTPUT, ALT_PPULL); 		// PWM, TIM1_CH1
	GPIO_Configure(GPIOA, 0, OUTPUT, ALT_PPULL); 		// PWM, TIM2_CH2 
	GPIO_Configure(GPIOA, 6, OUTPUT, ALT_PPULL); 		// PWM, TIM3_CH1 
	GPIO_Configure(GPIOB, 6, OUTPUT, ALT_PPULL); 		// PWM, TIM4_CH2 
	
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
}


/**
 *******************************************************************************
 * s_beaconSignal_emission_PWM
 *
 *			Emission PWM to every Beacon for a pre-defined period of time
 * 			Mode ON on each GPIO (output with PWM signal)
 * 			
 * @param int time of emission in [ms]
 * @return void
 ******************************************************************************/
 
void s_beaconSignal_emission_PWM()		
{
	static char PwmPulsePeriod = 0;
	static char PwmZeroPeriod = 0;
		
	// pwm emission
	switch (state_pwm)
	{
		case PWM_PULSE:
		s_beaconSignal_reset();
		
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


/**
 *******************************************************************************
 * s_beaconSignal_reset
 *
 *			Reset initial conditions in beaconSignal service
 *			State PWM in mode ZERO
 *			LED ON
 * 			
 ******************************************************************************/
 
void s_beaconSignal_reset(void)
{
	// PWM emission before the first Systick interruption
	PWM_Valeur(TIM1,1)=(resolution_pwm1*DUTYCYCLE_50);
	PWM_Valeur(TIM2,1)=(resolution_pwm2*DUTYCYCLE_50);
	PWM_Valeur(TIM3,1)=(resolution_pwm3*DUTYCYCLE_50);
	PWM_Valeur(TIM4,1)=(resolution_pwm4*DUTYCYCLE_50);
}


/**
 *******************************************************************************
 * s_beaconSignal_pwm
 *
 *			beaconSignal service in mode ZERO
 *			State PWM in mode PULSE for next switch
 *			LED OFF
 * 			
 ******************************************************************************/
 
void s_beaconSignal_zero(void)
{
	// PWM emission before the first Systick interruption
	PWM_Valeur(TIM1,1)=(resolution_pwm1*DUTYCYCLE_0);
	PWM_Valeur(TIM2,1)=(resolution_pwm2*DUTYCYCLE_0);
	PWM_Valeur(TIM3,1)=(resolution_pwm3*DUTYCYCLE_0);
	PWM_Valeur(TIM4,1)=(resolution_pwm4*DUTYCYCLE_0);
	
}