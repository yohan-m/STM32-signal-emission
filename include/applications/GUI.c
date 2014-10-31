/**
 * @file GUI.c
 * @brief GUI Communication
 *
 *      This file contains the APPLICATION use to communicate with the GUI.
 *
 *	Last modification : 19 Oct 2014 
 *
 * @author Guillaume
 * @version 1.0.0
 * @date 19 Oct 2014 
 */


/******************************************************************************
* 
*   INCLUDED FILES
*
******************************************************************************/

#include "GUI.h"


/******************************************************************************
*
*   FUNCTIONS
*
******************************************************************************/

/**
 *******************************************************************************
 * app_updateGUI
 *
 *      Update GUI with special character
 *			Called in the main function
 *			Send special character that depends from the app state
 * 			
 * @sa main()
 ******************************************************************************/
 
void app_updateGUI()	
{
	switch (state)
	{
		case APP_ON:
			s_serialComm_sendChar(MSG_ON);
			break;
		case APP_START:
			s_serialComm_sendChar(MSG_START);	
			break;
		case APP_STOP:
			s_serialComm_sendChar(MSG_STOP);
			break;
		case APP_OFF:
		default:	
			break;
	}
}
