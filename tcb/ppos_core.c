#include "ppos.h"

#define STACKSIZE 4100 /* tamanho de pilha das threads */
int task_count = 0;

task_t *current_task = NULL;
task_t *queue_tasks = NULL;
task_t *user_task = NULL;

task_t main_task, dispatcher_task;

void ppos_init(void)
{
  // Inicializa a stack do contexto main
  // Retorna erro caso a alocação de memória falhe
  char *stack = malloc(STACKSIZE);

  //Configura a task main
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
  main_task.context.initialized = 1;
  current_task = &main_task;
  get_context_asm(&main_task.context);

  // Cria task do dispatcher e o remove da fila por não ser uma task de usuário.
  // TODO: Encontrar método melhor de criar tasks de sistema
  task_create(&dispatcher_task, dispatcher_body, "    Dispatcher");
  queue_remove((queue_t **)&queue_tasks, (queue_t *)&dispatcher_task);
}

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

  // Incrementa o contador de tasks e o utiliza como id para a task atual
  task_count++;
  task->id = task_count;

  // Designa a função inicial do contexto junto com seus parâmetros
  makecontext(&task->context, (int)start_func, 1, arg);

  // Coloca task atual na queue para ser escalonada
  queue_append((queue_t **)&queue_tasks, (queue_t *)task);

  // Retorna o id da task criada
  return task->id;
}

int task_switch(task_t *new_task)
{
  task_t *old_task = current_task;
  current_task = new_task;

  swap_context_asm(&old_task->context, &new_task->context);

  return 0;
}

int task_id(void)
{
  return current_task->id;
}

void task_exit(int exitCode)
{
  current_task->context.initialized = 0;

  user_task = current_task->prev;
  queue_remove((queue_t **)&queue_tasks, (queue_t *)current_task);

  task_count--;

  task_switch(queue_tasks ? &dispatcher_task : &main_task);
}

void dispatcher_body()
{
  task_t *next_task = NULL;

  while (task_count > 1)
  {
    next_task = scheduler();
    user_task = next_task;

    if (next_task)
      task_switch(next_task);
  }
  task_exit(0);
}

task_t *scheduler(void)
{
  if (user_task == NULL)
    return user_task = queue_tasks;
  else
    return user_task->next;
}

void task_yield(void)
{
  task_switch(&dispatcher_task);
}
