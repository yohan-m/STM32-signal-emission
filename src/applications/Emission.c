/*----------------------------------------------------------------------------
 * Name:    Emission.c
 * Purpose: Application for emmiting a periodic signal
 *
 * Version: V1.0
 * Ahthor: G.Fauxpoint
 */

/******************************************************************************
* 
*   INCLUDED FILES
*
******************************************************************************/

#include "Emission.h"

/******************************************************************************
*
*   PUBLIC FUNCTIONS
*
******************************************************************************/

void app_commBeacons(void)		
{
	// PWM emission for pre-defined time interval [ms] 
	s_beaconSignal_emission_PWM();
}

char app_initialization(void)
{			
	// service initialization
	s_beaconSignal_initialization(app_commBeacons);
		
	return 0;
}

void UpdateStateMachineEmission()
{
	static int EmmissionOn = 1;
	
	if (!GetStateTampButton()) 
		{
			if (EmmissionOn == 1)
				{
					EmmissionOn = 0;
					state_pwm = PWM_RESET;
					
					enableSystick();
				}
			else
				{
					EmmissionOn = 1;
					state_pwm = PWM_PULSE;
					
					enableSystick();
				}
			while (!GetStateTampButton()); //Waiting for the user to take off his finger of the button
		}
}


