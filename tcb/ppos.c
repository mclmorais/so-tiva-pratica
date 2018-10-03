#include "ppos.h"

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
  return 0;
}