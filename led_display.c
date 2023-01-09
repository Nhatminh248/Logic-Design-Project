/*
 * led_display.c
 *
 *  Created on: Dec 23, 2022
 *      Author: hotha
 */
#include "led_display.h"
int buffer = 1;//show which current 7-seg led is (use in displayled func)
int blink_flag = 0;//flag use in modify status to show user which led's value they are changing, if 1 turn on led otherwise
int led_buffer[6] = {0, 0, 0, 0, 0, 0};// array to store values for 6 7-segment leds
int led_flag = 0;//if flag is 0 write pin of the led according to mode
//Transfer sequence: gfedcba
//MSB=g, LSB=a <- Active low
//Ex: To display 0 -> sequence = 1000000
const uint8_t sevenSegTable[10] = {
		  0x40 //0
		, 0x79 //1
		, 0x24 //2
		, 0x30 //3
		, 0x19 //4
		, 0x12 //5
		, 0x02 //6
		, 0x78 //7
		, 0x00 //8
		, 0x10 /*9*/};
void turnOnLed(){
	if(led_flag == 0){
		switch(mode){
			case 1:
				HAL_GPIO_WritePin(LED_MODE1_GPIO_Port, LED_MODE1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(LED_MODE2_GPIO_Port, LED_MODE2_Pin, GPIO_PIN_SET);
				break;
			case 2:
				HAL_GPIO_WritePin(LED_MODE1_GPIO_Port, LED_MODE1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(LED_MODE2_GPIO_Port, LED_MODE2_Pin, GPIO_PIN_RESET);
				break;
			default:
				break;
		}
	}
}
void display7SEG(int num){
	HAL_GPIO_WritePin(seg_a_GPIO_Port, seg_a_Pin, ((sevenSegTable[num]>>0)&0x01));
	HAL_GPIO_WritePin(seg_b_GPIO_Port, seg_b_Pin, ((sevenSegTable[num]>>1)&0x01));
	HAL_GPIO_WritePin(seg_c_GPIO_Port, seg_c_Pin, ((sevenSegTable[num]>>2)&0x01));
	HAL_GPIO_WritePin(seg_d_GPIO_Port, seg_d_Pin, ((sevenSegTable[num]>>3)&0x01));
	HAL_GPIO_WritePin(seg_e_GPIO_Port, seg_e_Pin, ((sevenSegTable[num]>>4)&0x01));
	HAL_GPIO_WritePin(seg_f_GPIO_Port, seg_f_Pin, ((sevenSegTable[num]>>5)&0x01));
	HAL_GPIO_WritePin(seg_g_GPIO_Port, seg_g_Pin, ((sevenSegTable[num]>>6)&0x01));
}

void Invoke7SEG(int num, int led_array[]){//turn on the num th 7segment led, and display the number at 6 - num position in array
	switch(num){
			case 1:
				HAL_GPIO_WritePin(INI1_GPIO_Port, INI1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(INI2_GPIO_Port, INI2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(INI3_GPIO_Port, INI3_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(INI4_GPIO_Port, INI4_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(INI5_GPIO_Port, INI5_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(INI6_GPIO_Port, INI6_Pin, GPIO_PIN_RESET);
				display7SEG(led_array[5]);
				break;
			case 2:
				HAL_GPIO_WritePin(INI1_GPIO_Port, INI1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(INI2_GPIO_Port, INI2_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(INI3_GPIO_Port, INI3_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(INI4_GPIO_Port, INI4_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(INI5_GPIO_Port, INI5_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(INI6_GPIO_Port, INI6_Pin, GPIO_PIN_RESET);
				display7SEG(led_array[4]);
				break;
			case 3:
				HAL_GPIO_WritePin(INI1_GPIO_Port, INI1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(INI2_GPIO_Port, INI2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(INI3_GPIO_Port, INI3_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(INI4_GPIO_Port, INI4_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(INI5_GPIO_Port, INI5_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(INI6_GPIO_Port, INI6_Pin, GPIO_PIN_RESET);
				display7SEG(led_array[3]);
				break;
			case 4:
				HAL_GPIO_WritePin(INI1_GPIO_Port, INI1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(INI2_GPIO_Port, INI2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(INI3_GPIO_Port, INI3_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(INI4_GPIO_Port, INI4_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(INI5_GPIO_Port, INI5_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(INI6_GPIO_Port, INI6_Pin, GPIO_PIN_RESET);
				display7SEG(led_array[2]);
				break;
			case 5:
				HAL_GPIO_WritePin(INI1_GPIO_Port, INI1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(INI2_GPIO_Port, INI2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(INI3_GPIO_Port, INI3_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(INI4_GPIO_Port, INI4_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(INI5_GPIO_Port, INI5_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(INI6_GPIO_Port, INI6_Pin, GPIO_PIN_RESET);
				display7SEG(led_array[1]);
				break;
			case 6:
				HAL_GPIO_WritePin(INI1_GPIO_Port, INI1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(INI2_GPIO_Port, INI2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(INI3_GPIO_Port, INI3_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(INI4_GPIO_Port, INI4_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(INI5_GPIO_Port, INI5_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(INI6_GPIO_Port, INI6_Pin, GPIO_PIN_SET);
				display7SEG(led_array[0]);
				break;
			default:
				break;
	}
}
void updateBuffer(){//load value in temporary array to led_buffer array
	switch(mode){
		case 1:
			for(int i = 0; i < 6; i++)
				led_buffer[i] = time_tmp1[i];
			break;
		case 2:
			for(int i = 0; i < 6; i++)
				led_buffer[i] = time_tmp2[i];
			break;
		default:
			break;
	}
}
void BufferFeedBack(){//load value in to led_buffer array to temporary array
	switch(mode){
		case 1:
			for(int i = 0; i < 6; i++)
				time_tmp1[i] = led_buffer[i];
			break;
		case 2:
			for(int i = 0; i < 6; i++)
				time_tmp2[i] = led_buffer[i];
			break;
		default:
			break;
	}
}
void decClock(int led_array[]){//change value of 1 led may affect leds on the right. This func is use to decrease value at current position and handle the mentioned problem
	if(mode == 1){
		for(int i = position; i < 6; i++){
			led_array[i] -= 1;
			if(led_array[i] < 0){
				if(i % 2 == 0){
					led_array[i] = 9;
				}
				else{
					if(i == 5) led_array[i] = 9;
					else led_array[i] = 5;
				}
			}
			else break;
		}
	}
	if(mode == 2){
		for(int i = position; i < 6; i++){
			led_array[i] -= 1;
			if(led_array[i] < 0){
				if(i % 2 == 0){
					if(led_array[5] == 0 && i == 4) led_array[i] = 3;
					else led_array[i] = 9;
				}
				else{
					if(i == 5) led_array[i] = 2;
					else led_array[i] = 5;
				}
			}
			else break;
		}
	}
}
void incClock(int led_array[]){//like decClock but for increasing
	if(mode == 1){
		for(int i = position; i < 6; i++){
			led_array[i] += 1;
			if(i % 2 == 0){
				if(led_array[i] >= 10) led_array[i] = 0;
				else break;
			}else{
				if(i == 5){
					if(led_array[i] >= 10) led_array[i] = 0;
					else break;
				}
				else{
					if(led_array[i] >= 6) led_array[i] = 0;
					else break;
				}
			}
		}
	}
	if(mode == 2){
		for(int i = position; i < 6; i++){
			led_array[i] += 1;
			if(i % 2 == 0){
				if(led_array[5] == 2){
					if(i == 4){
						if(led_array[i] >= 4) led_array[i] = 0;
						else break;
					}
					else{
						if(led_array[i] >= 10) led_array[i] = 0;
						else break;
					}
				}else{
					if(led_array[i] >= 10) led_array[i] = 0;
					else break;
				}
			}else{
				if(i == 5){
					if(led_array[i] > 2) led_array[i] = 0;
					else break;
				}
				else{
					if(led_array[i] >= 6) led_array[i] = 0;
					else break;
				}
			}
		}
	}
}
void updateClock(){//increase if mode is 2, decrease if mode is 1, if status is RUN and mode is 1 stop at 00:00:00
	if(RunStatus == RUN && mode == 1 && ((led_buffer[0]+led_buffer[1]+led_buffer[2]+led_buffer[3]+led_buffer[4]+led_buffer[5]) == 0)) RunStatus = INIT;
	else{
		switch (mode){
		case 1:
			decClock(led_buffer);
			break;
		case 2:
			incClock(led_buffer);
			break;
		default:
			break;
		}
	}
}
void displayTime(){//display time
	if(timer2_flag == 1){
		if(RunStatus == STANDBY && buffer == (6 - position)){
			if(!blink_flag) blink_flag = 1;
			else{
				blink_flag = 0;
				Invoke7SEG(buffer, led_buffer);
			}
		}
		else Invoke7SEG(buffer, led_buffer);
		++buffer;
		if(buffer > 6) buffer = 1;
		setTimer2(5);
	}
}

