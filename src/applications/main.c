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
	int EmmissionOn = 0;
	// Initialization
	app_initialization();
	
	// Infinity loop 
	while(1)
	{
		if (!GPIO_Read(GPIOC,13)) 
		{
			if (EmmissionOn == 1)
			{
				EmmissionOn = 0;
				state_pwm = PWM_RESET;
				
				SysTick_On;
				SysTick_Enable_IT;
			}
			else
			{
				EmmissionOn = 1;
				state_pwm = PWM_PULSE;
				
				SysTick_On;
				SysTick_Enable_IT;
			}
			while (!GPIO_Read(GPIOC,13));
		}
	}
		
	return 0;
}


