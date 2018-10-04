#include "ppos.h"
volatile int count_id = 0;
task_t *taskStack, *taskRunning;
ucontext_t mainContext;

void queue_append (queue_t **queue, queue_t *elem) ;

void ppos_init(void)
{
    taskStack = NULL;
    taskRunning = NULL;
}

int task_create(task_t *task, void (*start_routine)(void *), void *arg)
{
    char *stack;
    stack = malloc(STACKSIZE);
    if (stack)
    {
        task->context.uc_stack.ss_sp = stack;
        task->context.uc_stack.ss_size = STACKSIZE;
        task->context.uc_stack.ss_flags = 0;
        task->context.uc_link = 0;
        count_id++;
        task->id = count_id;
    }
    else
    {
        perror("Erro na criacao da pilha: ");
        return -1;
    }

    //   makecontext (&ContextPing,  (void*)(*BodyPing), 1, "    Ping");
    makecontext(&task->context, (int)(*start_routine), 1, arg);
    queue_append((queue_t **)&taskStack, (queue_t *)task);
    return task->id;
}

int task_switch(task_t *task)
{
    if (taskRunning != NULL){
        swap_context_asm(&taskRunning->context, &task->context);
        return 0;
    }
    return -1;
}

void startSwitcher(void)
{
    taskRunning = taskStack;
    swap_context_asm(&mainContext, &taskRunning->context);
}

void yieldmain(void){
    swap_context_asm(&taskRunning->context, &mainContext);
}