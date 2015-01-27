/**
 * @file s_beaconSignal.h
 * @brief Beacon signal emission file header
 *
 *      This file contains the SERVICE beacon signal emission.
 *			Initialize, configurate and activate timers with PWM mode. 
 *
 * @author Guillaume
 * @version 0.0.1
 * @date 09 Jan 2015
 */

/**
 * @page STM32_SIGNAL_EMISSION STM32_SIGNAL_EMISSION
 * @section BEACON_SIGNAL_intro BEACON_SIGNAL
 *
 * Initialize, configurate and activate timers with PWM mode. 
 *
 * @section BEACON_SIGNAL_reference Module reference
 *  - @ref beaconSignal_Module
 *
 * @section BEACON_SIGNAL_exemples Example
 *  Example 1: Enable the systick interruption
 *
 *  @code
 *  #include "s_beaconSignal.h"
 *
 *  void main (void)
 *  {
 *  	enableSystick();
 *  }
 *
 *  @endcode
 *
 *	Example 2: Configuration of the function launched by the systick handler
 *
 * @code
 * #include "s_beaconSignal.h"
 * 
 *void function (void)
 *{
 *	int i;
 *	
 *	while (i< 1523)
 *	{
 *    	i++;
 *   	}
 *}
 *
 * void main (void)
 * {
 *	s_beaconSignal_initialization(function);
 *
 *    while(1)
 *   	{
 *  		//......
 *	}
 *}
 *
 * @endcode
 * 
 * @section EMISSION_intro EMISSION_APPLICATION
 *
 * This application provides functions to initialize and configure the periodic emission of the four transducers.
 *
 * @section EMISSION_reference Module reference
 *  - @ref Emission_Module
 *
 * @section EMISSION_exemples Example
 *  Example 1: Initialize the emission
 *
 *  @code
 *  #include "Emission.h"
 *
 *  void main (void)
 *  {
 *  	app_initialization();
 *  }
 *
 *  @endcode
 */
 
 
 */



#ifndef S_BEACONSIGNAL_H
#define S_BEACONSIGNAL_H



/******************************************************************************
* 
*   INCLUDED FILES
*
******************************************************************************/

#include "stm32f10x.h"
#include "core_cm3.h"
#include "Timer_Systick.h"
#include "clock.h"
#include "stdint.h"
#include "Timer_1234.h"
#include "GPIO.h"

/**
 * @addtogroup beaconSignal_Module BEACON_SIGNAL
 * @{
 * @brief This module contains :
 *        	- The Functions provided by this service
 *		- The Macro modifiable by the user to get this wanted configuration
 *		- An Enumeration, to simplify the use of the state machine
 */



/******************************************************************************
*
*   CONSTANTS 
*
******************************************************************************/

/** @addtogroup beaconSignal_Macro Macro
	* @{
	*/

/** Signal frequency PWM1 [KHz] */
#define FPWM1 39.5
/** Signal frequency PWM2 [KHz] */
#define FPWM2 40.0
/** Signal frequency PWM3 [KHz] */
#define FPWM3 40.5
/** Signal frequency PWM4 [KHz] */
#define FPWM4 41.0

/** Duty Cycle for PWM signal when the PWM is in pulse mode */
#define DUTYCYCLE_50 0.5
/** Duty Cycle for PWM signal when the PWM is in zero mode*/
#define DUTYCYCLE_0 0.0

/** Systick period in [us]*/
#define SYSTICK_PERIOD 1000.0 //100 ms

/** PWM On period in us **/
#define PwmOnPeriod 20*SYSTICK_PERIOD

/** PWM Off period in us **/
#define PwmOffPeriod 20*SYSTICK_PERIOD

/** Priority for beacons task */
#define PRIORITY_BEACONS 1

/** Number of systick period corresponding to the PWM on period */
#define PwmOnNumberPeriodSystick   (PwmOnPeriod/SYSTICK_PERIOD)
/** Number of systick period corresponding to the PWM off period */
#define PwmOffNumberPeriodSystick  (PwmOffPeriod/SYSTICK_PERIOD)

/**
	* @}
	*/


/******************************************************************************
*
*   ENUM 
*
******************************************************************************/

/** @addtogroup beaconSignal_Enum Enum
	* @{
	*/

/** 
 * @enum State_PWM
 * @brief PWM state
 *
 * Describe the three differents states for the Timer PWM
 *
 */
typedef enum
{
	PWM_PULSE, /*!< The PWM is on, sending a periodic square signal with a 50% duty cycle. */
	PWM_ZERO,  /*!< The PWM is off, sending a 0 signal. */
	PWM_RESET  /*!< The PWM is stopped*/
	
} State_PWM;

/**
	* @}
	*/


/******************************************************************************
* 
*   GLOBAL VARIABLE
*
******************************************************************************/

/** @addtogroup beaconSignal_GlobalVariable GlobalVariable 
	* @{
	*/

/** pwm state */
extern State_PWM state_pwm;

/**
	* @}
	*/



/******************************************************************************
*
*   PRIVATE FUNCTIONS
*
******************************************************************************/

/** @addtogroup beaconSignal_Function Function
	 * @{
	 */

/**
 * @fn 		void s_beaconSignal_initialization(void (*function) (void))
 * @brief Configure all clocks and registers.
 *				Initialize all GPIOs and Timers
 * 
 * @param void (*function) (void), The handler systick will run this function at each systick interruption
 * @return void
 */
     
void s_beaconSignal_initialization(void (*function) (void));

/**
 * @fn 		void s_beaconSignal_emission_PWM(void);	
 * @brief  Emission PWM to every Beacon for a pre-defined period of time
 * 					Mode ON on each GPIO (output with PWM signal)
 * 
 * @param void 
 * @return void
 */
     
void s_beaconSignal_emission_PWM(void);	

/**
 * @fn 		void s_beaconSignal_pulse(void);
 * @brief BeaconSignal service in mode PULSE
 *				State PWM in mode PULSE
 *				LED PB11 ON
 * 
 * @param void 
 * @return void
 */
     
void s_beaconSignal_pulse(void);

/**
 * @fn 		void s_beaconSignal_zero(void);
 * @brief beaconSignal service in mode ZERO
 *				State PWM in mode PULSE for next switch
 *				LED PB12 ON
 *
 * @param void 
 * @return void
 */
     
void s_beaconSignal_zero(void);

/**
 * @fn 		void enableSystick();
 * @brief Enable the systick timer and interruption
 * 
 * @param void 
 * @return void
 */
     
void enableSystick();

/**
 * @fn 		int GetStateTampButton();
 * @brief Notive the user if the "Tamp" button is pressed
 * 
 * @param void 
 * @return The state of the "Tamp" button
 * 			-0 if tamp is pressed
 *			-1 it tamp is not pressed	
 */
     
int GetStateTampButton();

/**
	* @}
	*/
	
/**
	* @}
	*/

#endif					/* S_BEACONSIGNAL_H */
