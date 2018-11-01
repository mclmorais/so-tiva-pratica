#include "ppos.h"

#define STACKSIZE 4100 /* tamanho de pilha das threads */
int task_count = 0;

task_t *current_task = NULL;
task_t *queue_tasks = NULL;
task_t *user_task = NULL;

int yield_counter = 0;

int led_blink = 0;


#define ALPHA 1

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

  // Task começa com prioridade 0 por padrão
  task_setprio(task, 0);

  // Designa a função inicial do contexto junto com seus parâmetros
  makecontext(&task->context, (int)start_func, 1, arg);

  // Coloca task atual na queue para ser escalonada
  queue_append((queue_t **)&queue_tasks, (queue_t *)task);

  // Retorna o id da task criada
  return task->id;
}

int task_switch(task_t *new_task)
{
    UARTprintf ("Current Task: %s\n", current_task->context.arg);
    UARTprintf ("Next Task: %s\n", new_task->context.arg);

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
       UARTprintf ("DISPATCHER!\n");

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

  int new_task_found = 0;

  // Seleciona a primeira task da fila se não houver nenhuma ou escolhe uma
  // baseado em prioridades
  if (user_task == NULL)
    return user_task = queue_tasks;
  else
  {
    //Iterador começa no começo da fila de tasks de usuário
    task_t *i = queue_tasks;

    //Task selecionada começa na task atual (assim se nenhuma task for
    //selecionada a escolhida continua na atual)
    task_t *selected_task = user_task;

    // Seleciona a próxima task verificando prioridades (sendo a estática a
    // prioridade designada da task e a dinâmica a prioridade levando em
    // consideração quanto tempo faz que a task não é escalonada)
    do
    {
      // Task atual não precisa ser verificada
      if (i == selected_task)
      {
        i = i->next;
        continue;
      }

      // Decide se há uma task mais prioritária que a atual (levando em conta idade)
      if (i->dynamic_priority <= user_task->static_priority)
      {
        // Troca de task e reinicia sua idade; Flag é setada para este processo
        // ocorrer apenas uma vez por loop
        if (!new_task_found)
        {
          selected_task = i;
          selected_task->dynamic_priority = selected_task->static_priority;
          new_task_found = 1;
        }
      }
      else
      {
        // Se a task iterada não foi selecionada, a envelhece até uma
        // prioridade máxima de zero
        if(i->dynamic_priority - ALPHA >= 0)
          i->dynamic_priority -= ALPHA;
        else
          i->dynamic_priority = 0;
      }

      i = i->next;
    } while (i != queue_tasks);

    return selected_task;
  }
}

void task_yield(void)
{
    task_switch(&dispatcher_task);


}

void task_interrupt(void)
{
  if (++yield_counter > 5000)
  {
    UARTprintf ("INTERRUPT INSIDE!\n");
    LEDWrite(CLP_D1, led_blink);
    LEDWrite(CLP_D2, !led_blink);
    led_blink = !led_blink;

    task_switch(&dispatcher_task);
    yield_counter = 0;
  }
}

void task_debug(void)
{
    UARTprintf ("DEBUG!!!\n");

}

void task_setprio(task_t *task, int prio)
{
  task->static_priority = prio;
  task->dynamic_priority = prio;
}

int task_getprio(task_t *task)
{
  return task ? task->static_priority : current_task->static_priority;
}