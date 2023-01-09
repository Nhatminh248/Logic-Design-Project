/*
 * global.c
 *
 *  Created on: Dec 23, 2022
 *      Author: hotha
 */

#include "global.h"

int mode = 0; // mode = 1 is counts down mode, 2 is counts up mode (work like a clock)
int position = 0;// indicate which 7-seg led user currently at (mostly use to help modify value process)
int	time_tmp1[6] = {0, 0, 0, 0, 0, 0};//to store temporary value for mode 1(before set)
int	time_tmp2[6] = {0, 0, 0, 0, 0, 0};//like above but for mode 2
int	time_mode1[6] = {0, 0, 0, 0, 0, 0};//to store value for mode 1(after set)
int	time_mode2[6] = {0, 0, 0, 0, 0, 0};//like above but for mode 2
int RunStatus = INIT;// INIT is the started status, STANDBY is modifying status, RUN is automatic running which current mode is status

void initVar(void){
	mode = MODE1;
	position = 0;
	RunStatus = INIT;
}
void syncTime(){// load value of time_tmp array to time_mode array
	switch(mode){
		case 1:
			for(int i = 0; i < 6; i++)
				time_mode1[i] = time_tmp1[i];
			break;
		case 2:
			for(int i = 0; i < 6; i++)
				time_mode2[i] = time_tmp2[i];
			break;
		default:
			break;
	}
}
void clearTime(){// change all values of time_mod and time_tmp arrays to 0
	switch(mode){
		case 1:
			for(int i = 0; i < 6; i++){
				time_mode1[i] = 0;
				time_tmp1[i] = 0;
			}
			break;
		case 2:
			for(int i = 0; i < 6; i++){
				time_mode2[i] = 0;
				time_tmp2[i] = 0;
			}
			break;
		default:
			break;
	}
}
void resetTime(){//like syncTime() but the other way
	switch(mode){
		case 1:
			for(int i = 0; i < 6; i++)
				time_tmp1[i] = time_mode1[i];
			break;
		case 2:
			for(int i = 0; i < 6; i++)
				time_tmp2 [i] = time_mode2[i];
			break;
		default:
			break;
	}
}

