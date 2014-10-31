/******************************************************************************
* 
*   INCLUDED FILES
*
******************************************************************************/

#include "application.h"

/******************************************************************************
*
*   GLOBAL VARIABLES
*
******************************************************************************/

/** application state */
State_APP state = APP_OFF;
State_APP prev_state = APP_OFF;


/******************************************************************************
*
*   FUNCTIONS
*
******************************************************************************/

/**
 *******************************************************************************
 * app_serialCommHandler
 *
 *      Called when serial comm interruption takes place
 *			Analyze received character and update app state
 * 			If character is not valid (protocol not respected)
 *			then the application state rest the same as before
 *
 * @sa main()
 ******************************************************************************/
 
void app_serialCommHandler(char c)		
{
	switch (c)
	{
		case MSG_ON :
			if (state == APP_OFF)
			{
				prev_state = state;
				state = APP_ON;
			}
			break;
			
		case MSG_START :
			if (state != APP_OFF)
			{
				prev_state = state;
				state = APP_START;
				s_beaconSignal_reset();
				SysTick_On;
				SysTick_Enable_IT;
			}
			break;
		
		case MSG_STOP :
			if (state == APP_START)
			{
				prev_state = state;
				state = APP_STOP;
				s_beaconSignal_zero();
				SysTick_Disable_IT;
				SysTick_Off;
			}
			break;
		
		default :
			prev_state = state;
			state = APP_OFF;
			s_beaconSignal_zero();
			SysTick_Disable_IT;
			SysTick_Off;
			break ;		
	}
}


/**
 *******************************************************************************
 * app_commBeacons
 *
 *      Called when timeout to systick timer
 *			Emission PWM to every Beacon for a pre-defined period of time
 * 			
 * @sa main()
 ******************************************************************************/
 
void app_commBeacons(void)		
{
	// PWM emission for pre-defined time interval [ms] 
	s_beaconSignal_emission_PWM();
}


/**
 *******************************************************************************
 * app_initialization
 *
 *      Configures all clocks and registers.
 *			Initializes all Services
 * 			Configures Systick Timer
 *
 * @sa main()
 ******************************************************************************/

char app_initialization(void)
{			
	// Clock's configuration
	CLOCK_Configure();

	//lcd_init();
	//lcd_clear();
	
	// service initialization
	s_beaconSignal_initialization();
	
	// Systick clock configuration
	Systick_Period(SYSTICK_PERIOD); //[us]   // Useless variable ? Never used 
	Systick_Prio_IT(PRIORITY_BEACONS, app_commBeacons); // Priority 2 for Emission_PWM, PRIORITY_BEACONS = 2
	
	state_pwm = PWM_RESET;
		
	return 0;
}




