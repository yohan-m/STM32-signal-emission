/**
 * @file s_beaconSignal.h
 * @brief Beacon signal emission file header
 *
 *      This file contains the SERVICE beacon signal emission.
 *			Initializes, configurates and activates timers with PWM mode. 
 *
 * @author Martin
 * @version 0.0.1
 * @date 08 Nov 2013
 */


#ifndef S_BEACONSIGNAL_H
#define S_BEACONSIGNAL_H



/******************************************************************************
* 
*   INCLUDED FILES
*
******************************************************************************/

#include "stdint.h"
#include "stm32f10x.h"
#include "Timer_1234.h"
#include "GPIO.h"
#include "global.h"


/******************************************************************************
*
*   CONSTANTS AND ENUM TYPES
*
******************************************************************************/

/** Signal frequency PWM [KHz] */
#define FPWM1 39.5  
#define FPWM2 40.0       				 
#define FPWM3 40.5
#define FPWM4 41.0

/** Duty Cycle for PWM signal */
#define DUTYCYCLE_50 0.5
#define DUTYCYCLE_0 0.0

/** Type def for PWM State */
typedef enum
{
	PWM_PULSE,
	PWM_ZERO,
	PWM_RESET
	
} State_PWM;

/******************************************************************************
* 
*   GLOBAL VARIABLE
*
******************************************************************************/

/** pwm state */
extern State_PWM state_pwm;


/******************************************************************************
*
*   PRIVATE FUNCTIONS
*
******************************************************************************/

void s_beaconSignal_initialization(void);
void s_beaconSignal_emission_PWM(void);	
void s_beaconSignal_reset(void);
void s_beaconSignal_zero(void);
int GetStateTampButton();

#endif					/* S_BEACONSIGNAL_H */
