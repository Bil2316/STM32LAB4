/*
 * SCH.c
 *
 *  Created on: Oct 16, 2024
 *      Author: BilH
 */

#include "SCH.h"

sTask SCH_tasks_G[SCH_MAX_TASKS];

void Timer_init()
{

}

void Watchdog_init()
{

}

void SCH_Init(void)
{
	for (uint8_t i = 0; i < SCH_MAX_TASKS; i++)
	{
		SCH_Delete_Task(i);
	}
	Timer_init();
	Watchdog_init();
}

void SCH_Add_Task(void (*pFunc)(void), uint32_t DELAY, uint32_t PERIOD)
{
	uint8_t index = 0;

	while ((SCH_tasks_G[index].pTasks != 0) && (index < SCH_MAX_TASKS))
	{
		index++;
	}
	if (index == SCH_MAX_TASKS)
	{
		return SCH_MAX_TASKS;
	}
	SCH_tasks_G[index].pTasks = pFunc;
	SCH_tasks_G[index].Delay = DELAY / TICK;
	SCH_tasks_G[index].Period = PERIOD / TICK;
	SCH_tasks_G[index].Runme = 0;
}

void SCH_Update(void)
{
	for (uint8_t i = 0; i < SCH_MAX_TASKS; i++)
	{
		if (SCH_tasks_G[i].Delay == 0)
		{
			SCH_tasks_G[i].Runme++;
			if (SCH_tasks_G[i].Period)
			{
				SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
			}
		}
		else
		{
			SCH_tasks_G[i].Delay--;
		}
	}
}

void SCH_Dispatch_Tasks(void)
{
	for (uint8_t i = 0; i < SCH_MAX_TASKS; i++)
	{
		if (SCH_tasks_G[i].Runme > 0)
		{
			(*SCH_tasks_G[i].pTasks)();
			SCH_tasks_G[i].Runme--;
			if (SCH_tasks_G[i].Period == 0)
			{
				SCH_Delete_Task(i);
			}
		}
	}
}

void SCH_Delete_Task(uint32_t taskID)
{
	if (SCH_tasks_G[taskID].pTasks != 0 && taskID < SCH_MAX_TASKS)
	{
		SCH_tasks_G[taskID].pTasks = 0;
		SCH_tasks_G[taskID].Delay = 0;
		SCH_tasks_G[taskID].Period = 0;
		SCH_tasks_G[taskID].Runme = 0;
	}
}
