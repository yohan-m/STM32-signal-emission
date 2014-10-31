
#ifndef APPLICATION_H
#define APPLICATION_H

#include "LCD.h"
#include "global.h"

void app_serialCommHandler(char c);	
 
void app_commBeacons(void) ;

char app_initialization(void) ;

#endif