/**
 * @file Emission.h
 * @brief Signal emission file header
 * @author Guillaume
 * @version 1.0.0
 * @date 09 Jan 2014
 *
 *      This file contains the emission application.
 *			Initialize, configurate the periodic emission of the four transducers. 
 */


#ifndef EMISSION_H
#define EMISSION_H


/******************************************************************************
* 
*   INCLUDED FILES
*
******************************************************************************/

#include "s_beaconSignal.h"

/******************************************************************************
*
*   PUBLIC FUNCTIONS
*
******************************************************************************/

/**
 * @addtogroup Emission_Module EMISSION
 * @{
 * @brief This module contains all the function provided by the emission application
 */

/** @addtogroup Emission_Function Function
	 * @{
	 */

/**
 * @fn 		void app_commBeacons(void)
 * @brief Called when timeout to systick timer
 *				Emission PWM to every Beacon for a pre-defined period of time
 * 
 * @param void
 * @return void
 */
 
void app_commBeacons(void) ;

/**
 * @fn 		char app_initialization(void)
 * @brief Initialize the beacon service
 * @param void
 * @return void
 */

char app_initialization(void) ;

/**
 * @fn 		void UpdateStateMachineEmission();
 * @brief Update the emission state machine when the button "Tamp" is pressed, disable/enable the emission
 *
 * @param void
 * @return void
 */

void UpdateStateMachineEmission();

	/**
	 * @}
	 */

/**
 * @}
 */

#endif