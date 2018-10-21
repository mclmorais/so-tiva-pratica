// PingPongOS - PingPong Operating System
// Prof. Carlos A. Maziero, DINF UFPR
// Versão 1.1 -- Julho de 2016

// Teste do escalonador por prioridades dinâmicas

#include <stdio.h>
#include <stdlib.h>
#include "ppos.h"
#include "../drivers/uartstdio.h"


task_t Pang, Peng, Ping, Pong, Pung;

// corpo das threads
void teste_scheduler_body(void *arg)
{
  int i;

  UARTprintf("%s: inicio (prioridade %d)\n", (char *)arg, task_getprio(NULL));

  for (i = 0; i < 10; i++)
  {
    UARTprintf("%s: %d\n", (char *)arg, i);
    task_yield();
  }
  UARTprintf("%s: fim\n", (char *)arg);
  task_exit(0);
}

void teste_scheduler()
{
  UARTprintf("main: inicio\n");

  ppos_init();

  task_create(&Pang, teste_scheduler_body, "    Pang");
  task_setprio(&Pang, 0);

  task_create(&Peng, teste_scheduler_body, "        Peng");
  task_setprio(&Peng, 2);

  task_create(&Ping, teste_scheduler_body, "            Ping");
  task_setprio(&Ping, 4);

  task_create(&Pong, teste_scheduler_body, "                Pong");
  task_setprio(&Pong, 6);

  task_create(&Pung, teste_scheduler_body, "                    Pung");
  task_setprio(&Pung, 8);

  task_yield();

  UARTprintf("main: fim\n");
}

/* Saída esperada:

main: inicio
    Pang: inicio (prioridade 0)
    Pang: 0
    Pang: 1
    Pang: 2
        Peng: inicio (prioridade 2)
        Peng: 0
    Pang: 3
            Ping: inicio (prioridade 4)
            Ping: 0
    Pang: 4
        Peng: 1
                Pong: inicio (prioridade 6)
                Pong: 0
    Pang: 5
                    Pung: inicio (prioridade 8)
                    Pung: 0
    Pang: 6
        Peng: 2
            Ping: 1
    Pang: 7
    Pang: 8
        Peng: 3
                Pong: 1
    Pang: 9
            Ping: 2
    Pang: fim
        Peng: 4
                    Pung: 1
        Peng: 5
            Ping: 3
                Pong: 2
        Peng: 6
        Peng: 7
            Ping: 4
        Peng: 8
                    Pung: 2
        Peng: 9
                Pong: 3
            Ping: 5
        Peng: fim
            Ping: 6
                Pong: 4
                    Pung: 3
            Ping: 7
            Ping: 8
                Pong: 5
            Ping: 9
            Ping: fim
                    Pung: 4
                Pong: 6
                Pong: 7
                Pong: 8
                    Pung: 5
                Pong: 9
                Pong: fim
                    Pung: 6
                    Pung: 7
                    Pung: 8
                    Pung: 9
                    Pung: fim
main: fim
*/