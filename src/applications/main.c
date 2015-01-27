/*----------------------------------------------------------------------------
 * Name:    Main.c
 * Purpose: This file contains the main function that initializes, configurates
 * 					and starts all applications with their services. 
 *
 * Version: V1.0
 * Ahthor: G.Fauxpoint
 */

/******************************************************************************
* 
*   INCLUDED FILES
*
******************************************************************************/

#include "global.h"

/******************************************************************************
*
*   MAIN
*
******************************************************************************/

int main (void)
{	
	app_initialization();
	
	while(1)
	{
		UpdateStateMachineEmission();
	}
		
	return 0;
}


