/*
 * fsm_automatic.c
 *
 *  Created on: Dec 23, 2022
 *      Author: hotha
 */

#include "fsm_automatic.h"

void fsm_automatic_run(){
	turnOnLed();
	switch (RunStatus){
		case INIT: // chuẩn bị chuyển sang trạng thái chỉnh sửa
			setTimer2(5); // các led sẽ được hiện lần lượt sau mỗi 50ms (tốn 300ms để hiện hết 6 led)
			RunStatus = STANDBY;
		case STANDBY:// trạng thái chỉnh sửa
			break;
		case RUN: // trang thái chạy
			if (timer1_flag == 1){ // sau mỗi giây thời gian sẽ tăng hoặc giảm tùy theo mode
				updateClock();
				setTimer1(100);
			}
			break;
		default:
			break;
	}
}

