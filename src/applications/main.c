/**
 * @file main.c
 * @brief Main function core
 *
 *      This file contains the main function that initializes, configurates
 * 			and starts all applications with their services. 
 *
 *	Last modification : 18 Nov 2013 
 *
 * @author Guillaume
 * @version 1.0.0
 * @date 10 Oct 2014
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


