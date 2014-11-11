STM32-signal-emission
=====================

git repo for the ground STM32 source code

List of folder contains is this repository :
	- Keil project : Emission software
	- Hardware project : Emission PCB


Detailed explanations for each folder :
	- Keil project : STM32-signal-emission
		- Basic : Open the keil project (..\project\p_serverBeacons_stm32F103.uvproj), build all the project, load the executable on the STM32
		- What it does : It controls the emission of four ultrasound beacons.			
		- How it works
			- It creates a PWM connected to the beacons
			- For a period, the PWM have two states : ON and OFF, the duration of states is defined in a header file.
			- You can stop the emission by pressing the button "tamp", relaunch the program with the same button.
			- LED PB8 On : The software had correctly initialized and configured this peripheral.
			- LED PB11 On : The PWM is on.
			- LED PB12 On : The PWN is off.
			- LED PB13 On : The program is stopped.
		- What do you have to modify
			- The duration of the two PWM states (ON and OFF), find defines in the header file "s_beaconSignal.h" (path : ..\include\services)
				- PwmOnPeriod : Duration of the states On (Related to the period of the systick)
				- PwmOffPeriod : Duration of the states Off (Related to the period of the systick)
	- Hardware project : Hardware
		- Basic : Open the eagle project (..\Hardware\Project Eagle Ground Station[emission.pro)
		- What it contains : The PCB for the emission board
		
	











