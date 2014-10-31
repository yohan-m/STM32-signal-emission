/**
 * @file global.h
 * @brief Global file header
 *
 *      This file contains global variables and constants used in 
 *			the application.  
 *
 * @author Martin
 * @version 0.0.1
 * @date 14 Nov 2013
 */


#ifndef GLOBAL_H
#define GLOBAL_H


/******************************************************************************
* 
*   INCLUDED FILES
*
******************************************************************************/

#include "stm32f10x.h"
#include "stdint.h"
#include "stm32f10x.h"
#include "Clock.h"
#include "Timer_Systick.h"
#include "stdio.h"
#include "s_beaconSignal.h"
#include "s_serialComm.h"
#include "GUI.h"
#include "application.h"
#include "LCD.h"


/******************************************************************************
*
*   CONSTANTS
*
******************************************************************************/ 

/** Systick period in [us]*/
#define SYSTICK_PERIOD 2000.0 //100 ms

/** PWM On period in us **/
#define PwmOnPeriod 1*SYSTICK_PERIOD

/** PWM Off period in us **/
#define PwmOffPeriod 49*SYSTICK_PERIOD

/** priority for beacons task */
#define PRIORITY_BEACONS 1

/** Type def for Application State */
typedef enum
{
	APP_ON,
	APP_OFF,
	APP_START,
	APP_STOP
	
} State_APP;

/** Protocol Messages send to UART Server */
#define MSG_ON 'I'
#define MSG_OFF 'X'
#define MSG_START 'S'
#define MSG_STOP 'P'


#endif					/* GLOBAL_H */

