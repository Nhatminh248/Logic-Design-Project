/*
 * button.c
 *
 *  Created on: Dec 23, 2022
 *      Author: hotha
 */
#include "button.h"

int buttonList[NUM_OF_BUTTON] = {mode_Pin, set_Pin, increase_Pin, decrease_Pin};
// array chong rung cho nut
int KeyReg0[NUM_OF_BUTTON] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
int KeyReg1[NUM_OF_BUTTON] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
int KeyReg2[NUM_OF_BUTTON] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
int KeyReg3[NUM_OF_BUTTON] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};

int TimeForKeyPress =  100;
int button_flag[NUM_OF_BUTTON] = {0, 0, 0, 0};
int isButtonPressed(int index){
	return (button_flag[index])? 1 : 0;
}

void subKeyProcess(int index){ // tăng gt cờ lên 1
	button_flag[index] += 1;
}
void clearFlag(int index){// gán cờ = 0
	button_flag[index] = 0;
}
void getKeyInput(){
	for(int i=0; i<NUM_OF_BUTTON; i++){
	  KeyReg0[i] = KeyReg1[i];
	  KeyReg1[i] = KeyReg2[i];
	  KeyReg2[i] = HAL_GPIO_ReadPin(GPIOB, buttonList[i]);
	  if ((KeyReg1[i] == KeyReg0[i]) && (KeyReg1[i] == KeyReg2[i])){
		if (KeyReg3[i] != KeyReg2[i]){
		  if(KeyReg3[i] == PRESSED_STATE &&(i == 0 || i == 1)) DoEffectProcess(i);
		  KeyReg3[i] = KeyReg2[i];
		  clearFlag(i);
		  if (KeyReg2[i] == PRESSED_STATE){
			TimeForKeyPress = 100;
			subKeyProcess(i);
			buttonProcess(i);
		  }
		}else{
			if(KeyReg3[i] == PRESSED_STATE){
				TimeForKeyPress --;
				if (TimeForKeyPress == 0){
					subKeyProcess(i);
					buttonProcess(i);
					TimeForKeyPress = 50;
				}
			}
		}
	  }
	}
}
void DoEffectProcess(int i){//xử lý chức năng đầu tiên cho nút có nhiều chức năng
	switch(i){
		case 0:
			if(button_flag[i] == 1){ // chuyển mode
				mode = (mode+1 > 2)? 1 : mode + 1;
				led_flag = 0;
				updateBuffer();
			}
			break;
		case 1:
			if(button_flag[i] == 1){ // set value -> chạy mode
				syncTime(mode);
				updateBuffer();
				setTimer1(100);
				position = 0;
				RunStatus = RUN;
			}
			break;
		default:
			break;
	}
}
void DoProcess(int i){
	switch(i){
	case 0:
		if(button_flag[i] >= 2){ // chuyển vị trí led đang chỉnh
			position += 1;
			if(position >= 6) position = 0;
		}
		break;
	case 1:
		if(button_flag[i] == 3){ // clear gt về 0
			clearTime();
			updateBuffer();
		}
		if(button_flag[i] == 2){ // reset lại giá trị trước đó
			resetTime();
			updateBuffer();
		}
		break;
	case 2: // tăng giá trị tg
	    if(mode == 1) incClock(time_tmp1);
		else incClock(time_tmp2);
		updateBuffer();
		break;
	case 3: // giảm giá trị tg
		if(mode == 1) decClock(time_tmp1);
		else decClock(time_tmp2);
		updateBuffer();
		break;
	default:
		break;
	}
}
void buttonProcess(int i){ //sử lý khi có nút được nhấn
	if(RunStatus == RUN){ // nếu đang chạy chuyển về trạng thái chỉnh sửa tg
		RunStatus = STANDBY;
	}else{
		DoProcess(i);
	}
}



