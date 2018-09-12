#define task void*

void ev3_tasks_init();
void task_start(task (*task_func)(void*));
void task_yield();
void task_stop(task (*task_func)(void*));
void task_stop_all();
void ev3_tasks_uninit();