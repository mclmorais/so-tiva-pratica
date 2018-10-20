#include "ppos.h"

#define STACKSIZE 4100 /* tamanho de pilha das threads */
int task_number = 0;

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

  task_create(&dispatcher_task, dispatcher_body, "    Dispatcher");
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

  // Designa um id para a task e o incrementa pra a próxima task
  task_number++;
  task->id = task_number;

  // Designa a função inicial do contexto junto com seus parâmetros
  makecontext(&task->context, (int)start_func, 1, arg);

  // Coloca task atual na queue para ser escalonada
  queue_append((queue_t **)&queue_tasks, (queue_t *)task);

  // Retorna o id da task criada
  return task->id;
}

int task_switch(task_t *new_task)
{
  task_t* old_task = current_task;
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
  queue_remove((queue_t **)&queue_tasks, (queue_t *)current_task); //retira a task atual da queue
                                                                   //para que ela não seja mais escalonada
  task_number--;
  if (queue_tasks == NULL)
  {
    task_switch(&main_task);
  }
  else
  {
    task_switch(&dispatcher_task);
  }
}

void dispatcher_body()
{
  task_t *next_task = NULL;
  user_task = queue_tasks;
  while (task_number > 1)
  {
    next_task = scheduler(); // scheduler é uma função
    user_task = next_task;		// Para toda vez chamar o anterior
		if (next_task)
    {
      // ações antes de lançar a tarefa "next", se houverem
      task_switch(next_task); // transfere controle para a tarefa "next"
      // ações após retornar da tarefa "next", se houverem
    }
    next_task = NULL;
  }
  task_exit(0); // encerra a tarefa dispatcher
}

task_t *scheduler(void)
{
  if (user_task != NULL)
  {
    return user_task->next;
  }
  return NULL;
}

void task_yield(void)
{
  task_switch(&dispatcher_task);
}

