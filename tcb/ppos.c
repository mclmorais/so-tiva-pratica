#include "ppos.h"
volatile int count_id = 0;
task_t *taskStack, *taskRunning;
task_t mainTask;
//ucontext_t mainContext;

void queue_append(queue_t **queue, queue_t *elem);

void ppos_init(void)
{
    taskStack = NULL;
    taskRunning = NULL;
    char *stack;
    stack = malloc(STACKSIZE);
    if (stack)
    {
        mainTask.context.uc_stack.ss_sp = stack;
        mainTask.context.uc_stack.ss_size = STACKSIZE;
        mainTask.context.uc_stack.ss_flags = 0;
        mainTask.context.uc_link = 0;
        count_id++;
        mainTask.id = count_id;
    }
    else
    {
        perror("Erro na criacao da pilha: ");
    }
    taskRunning = &mainTask;
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
    makecontext(&task->context, (int)(*start_routine), 1, arg);
    //queue_append((queue_t **)&taskStack, (queue_t *)task); // Insere na fila a task atual para futuramente escalonar
    return task->id;
}

int task_switch(task_t *task)
{
    if (taskRunning != NULL)
    {
        swap_context_asm(&taskRunning->context, &task->context);
        return 0;
    }
    return -1;
}

void startSwitcher(void)
{
    /*TASK MANANGER*/
    taskRunning = taskStack;
    //swap_context_asm(&mainContext, &taskRunning->context);
}

void task_exit(int exitCode)
{
    /*RETORNA O CONTROLE DA ATIVIDADE PARA A MAIN*/
    task_switch(&mainTask);
}