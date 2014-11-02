/**
 * @file Emission.h
 * @brief Signal emission file header
 *
 *      This file contains the emission application.
 *			Initializes, configurates and the periodic emission of the four transducers. 
 *
 * @author Guillaume
 * @version 1.0.0
 * @date 02 Oct 2014
 */



#ifndef EMISSION_H
#define EMISSION_H


/******************************************************************************
* 
*   INCLUDED FILES
*
******************************************************************************/

#include "LCD.h"
#include "global.h"


/******************************************************************************
*
*   PUBLIC FUNCTIONS
*
******************************************************************************/

void app_serialCommHandler(char c);	
 
void app_commBeacons(void) ;

char app_initialization(void) ;

void UpdateStateMachineEmission();

#endif