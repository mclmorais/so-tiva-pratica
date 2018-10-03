#include "ppos.h"

#define STACKSIZE 4096 /* tamanho de pilha das threads */
int task_number = 0;

task_t *current_task = NULL;

task_t main_task;

void ppos_init(void)
{
  // Inicializa a stack do contexto main
  // Retorna erro caso a alocação de memória falhe
  char *stack = malloc(STACKSIZE);
  if (stack)
  {
    main_task.context.uc_stack.ss_sp = stack;
    main_task.context.uc_stack.ss_size = STACKSIZE;
    main_task.context.uc_stack.ss_flags = 0;
  }
  else
  {
    return;
  }

  main_task.id = 0;

  current_task = &main_task;
}

// Cria uma nova tarefa. Retorna um ID > 0 ou erro.
int task_create(task_t *task,               // descritor da nova tarefa
                void (*start_func)(void *), // funcao corpo da tarefa
                void *arg)                  // argumentos para a tarefa
{
  // Inicializa a stack da task a ser criada (contida em seu contexto).
  // Retorna erro caso a alocação de memória falhe
  char *stack = malloc(STACKSIZE);
  if (stack)
  {
    task->context.uc_stack.ss_sp = stack;
    task->context.uc_stack.ss_size = STACKSIZE;
    task->context.uc_stack.ss_flags = 0;
  }
  else
  {
    return -1;
  }

  // Designa um id para a task e o incrementa pra a próxima task
  task_number++;
  task->id = task_number;

  // NEEDED: Verificar se cast para int funciona
  makecontext(&task->context, (int)start_func, 1, arg);

  // Retorna o id da task criada
  return task->id;
}

void task_exit(int exitCode)
{
  task_switch(&main_task);
}

int task_switch(task_t *task)
{
  // Atualiza a task ativa com o contexto do controlador
  // e troca o contexto do controlador pelo contexto da task desejada
  getcontext(&current_task->context);
  setcontext(&task->context);

  current_task = task;
}

int task_id(void)
{
  return current_task->id;
}

