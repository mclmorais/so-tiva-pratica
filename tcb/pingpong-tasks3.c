// PingPongOS - PingPong Operating System
// Prof. Carlos A. Maziero, DINF UFPR
// Versão 1.1 -- Julho de 2016

// Teste da gestão básica de tarefas

#include <stdio.h>
#include <stdlib.h>
#include "ppos.h"
#include "../drivers/uartstdio.h"

#define MAXTASK 20

task_t task;

// corpo das threads
void BodyTask()
{
  UARTprintf("Estou na tarefa %5d\n", task_id());
  task_exit(0);
}

void TestePingPong3()
{
  int i;

  UARTprintf("main: inicio\n");

  ppos_init();

  // cria MAXTASK tarefas, ativando cada uma apos sua criacao
  for (i = 0; i < MAXTASK; i++)
  {
    task_create(&task, BodyTask, NULL);
    task_switch(&task);
  }

  UARTprintf("main: fim\n");
}