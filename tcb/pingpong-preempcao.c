// PingPongOS - PingPong Operating System
// Prof. Carlos A. Maziero, DINF UFPR
// Versão 1.1 -- Julho de 2016

// Teste da preempção por tempo

#include <stdio.h>
#include <stdlib.h>
#include "pingpong-preempcao.h"

#define WORKLOAD 2000

task_t Pang, Peng, Ping, Pong, Pung;

// simula um processamento pesado
int hardwork(int n)
{
  int i, j, soma;

  soma = 0;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      soma += j;
  return (soma);
}

// corpo das threads
void PingPongPreempcaoBody(void *arg)
{
  int i;

  UARTprintf("%s: inicio\n", (char *)arg);
  for (i = 0; i < 10; i++)
  {
    UARTprintf("%s: %d\n", (char *)arg, i);
    hardwork(WORKLOAD);
  }
  UARTprintf("%s: fim\n", (char *)arg);
  task_exit(0);
}

void PingPongPreempcao()
{
  UARTprintf("main: inicio\n");

  ppos_init();

  //   task_create (&Pang, PingPongPreempcaoBody, "    Pang") ;
  //   task_create (&Peng, PingPongPreempcaoBody, "        Peng") ;
  //   task_create (&Ping, PingPongPreempcaoBody, "            Ping") ;
  //   task_create (&Pong, PingPongPreempcaoBody, "                Pong") ;
  //   task_create (&Pung, PingPongPreempcaoBody, "                    Pung") ;

  task_create(&Pang, PingPongPreempcaoBody, "    Pang");
  task_setprio(&Pang, 0);

  task_create(&Peng, PingPongPreempcaoBody, "        Peng");
  task_setprio(&Peng, 2);

  task_create(&Ping, PingPongPreempcaoBody, "            Ping");
  task_setprio(&Ping, 4);

  task_create(&Pong, PingPongPreempcaoBody, "                Pong");
  task_setprio(&Pong, 6);

  task_create(&Pung, PingPongPreempcaoBody, "                    Pung");
  task_setprio(&Pung, 8);

  task_yield();

  UARTprintf("main: fim\n");
  exit(0);
}
