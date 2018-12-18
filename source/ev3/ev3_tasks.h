#ifndef EV3_TASKS_H
#define EV3_TASKS_H

#ifdef __cplusplus
extern "C" {
#endif

#define task void*

void ev3_tasks_init();
void task_start(task (*task_func)(void*));
void task_yield();
void task_stop(task (*task_func)(void*));
void task_stop_all();
void ev3_tasks_uninit();

#ifdef __cplusplus
}
#endif

#endif

