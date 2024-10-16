/*
 * SCH.h
 *
 *  Created on: Oct 16, 2024
 *      Author: BilH
 */

#ifndef INC_SCH_H_
#define INC_SCH_H_

#include "main.h"

#define SCH_MAX_TASKS		10
#define TICK				10

typedef struct
{
	void (*pTasks)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t Runme;
	uint32_t TaskID;
} sTask;

void SCH_Init(void);
void SCH_Add_Task(void (*pFunc)(void), uint32_t DELAY, uint32_t PERIOD);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);
void SCH_Delete_Task(uint32_t taskID);

#endif /* INC_SCH_H_ */
