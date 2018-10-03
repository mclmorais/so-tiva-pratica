#include "ppos.h"

#define STACKSIZE 4096    /* tamanho de pilha das threads */
int task_number = 0;

task_t *current_task = NULL;

void ppos_init(void)
{
}

int task_switch(task_t *task)
{
  return 0; // Implementar!
}

void task_exit(int exitCode)
{
}

// Cria uma nova tarefa. Retorna um ID> 0 ou erro.
int task_create(task_t *task,               // descritor da nova tarefa
                void (*start_func)(void *), // funcao corpo da tarefa
                void *arg)                  // argumentos para a tarefa
{

  // Inicializa a stack da task a ser criada (contida em seu contexto)
  char *stack = malloc(STACKSIZE);
  task->context.uc_stack.ss_sp = stack;
  task->context.uc_stack.ss_size = STACKSIZE;
  task->context.uc_stack.ss_flags = 0;
  task->context.uc_link = 0; // NEEDED: Descobrir uso deste parâmetro

  // Designa um id para a task e o incrementa pra a próxima task
  task->id = task_number;
  task_number++;


  // NEEDED: Verificar se cast para int funciona
  makecontext(&task->context, (int)start_func, 1, arg);

  // Retorna o id da task criada
  return task->id;
}