#include "ev3_tasks.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct taskInfo {
	void* (*taskFunction)(void*);
	pthread_t thread;
};

struct listElement {
	struct listElement *prev;
	struct taskInfo data;
	struct listElement *next;
};

struct listStruct {
	int count;
	struct listElement *first;
	struct listElement *last;
} taskList;

void ev3_tasks_init()
{
	taskList.count = 0;
	taskList.first = NULL;
	taskList.last = NULL;
}

void task_start(task (*task_func)(void*))
{
	pthread_t thread;
	if(pthread_create(&thread, NULL, task_func, NULL))
	{
		struct listElement *temp = malloc(sizeof(struct listElement));
		temp->next = NULL;
		temp->data.taskFunction = task_func;
		temp->data.thread = thread;
		if(taskList.first == NULL)
		{
			temp->prev = NULL;
			taskList.first = temp;
			taskList.last = temp;
		}
		else
		{
			struct listElement *oldLast = taskList.last;
			temp->prev = oldLast;
			oldLast->next = temp;
			taskList.last = temp;
		}
		taskList.count++;
	}
}

void task_yield()
{
	sched_yield();
}

void task_stop(task (*task_func)(void*))
{
	struct listElement *temp = taskList.last;
	while(temp != NULL && temp->data.taskFunction != task_func) { temp = temp->prev; }
	if(temp == NULL) return;
	if(temp->prev != NULL) temp->prev->next = temp->next;
	if(temp->next != NULL) temp->next->prev = temp->prev;
	if(taskList.first == temp) taskList.first = temp->next;
	if(taskList.last == temp) taskList.last = temp->prev;
	taskList.count--;
	pthread_cancel(temp->data.thread);
	free(temp);
}

void task_stop_all()
{
	struct listElement *temp = taskList.last;
	struct listElement *_temp;
	while(temp != NULL)
	{
		taskList.count--;
		pthread_cancel(temp->data.thread);
		_temp = temp;
		temp = temp->prev;
		free(_temp);
	}
	exit(0);
}

void ev3_tasks_uninit()
{
	struct listElement *temp = taskList.last;
	struct listElement *_temp;
	while(temp != NULL)
	{
		taskList.count--;
		pthread_cancel(temp->data.thread);
		_temp = temp;
		temp = temp->prev;
		free(_temp);
	}
}
