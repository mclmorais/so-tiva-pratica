// PingPongOS - PingPong Operating System
// Prof. Carlos A. Maziero, DINF UFPR
// Versão 1.1 -- Julho de 2016

// Teste da contabilização - tarefas de mesma prioridade

#include <stdio.h>
#include <stdlib.h>
#include "ppos.h"

#define WORKLOAD 40000

task_t Pang, Peng, Ping, Pong, Pung ;

// simula um processamento pesado
int hardwork (int n)
{
   int i, j, soma ;

   soma = 0 ;
   for (i=0; i<n; i++)
      for (j=0; j<n; j++)
         soma += j ;
   return (soma) ;
}

// corpo das threads
void PingPongContabBody (void * arg)
{
   UARTprintf ("%s: inicio em %4d ms\n", (char *) arg, systime()) ;
   hardwork (WORKLOAD) ;
   UARTprintf ("%s: fim    em %4d ms\n", (char *) arg, systime()) ;
   task_exit (0) ;
}

void PingPongContab (void)
{
   UARTprintf ("main: inicio\n");

   ppos_init () ;

   task_create (&Pang, PingPongContabBody, "    Pang") ;
   task_create (&Peng, PingPongContabBody, "        Peng") ;
   task_create (&Ping, PingPongContabBody, "            Ping") ;
   task_create (&Pong, PingPongContabBody, "                Pong") ;
   task_create (&Pung, PingPongContabBody, "                    Pung") ;

   task_yield () ;

   UARTprintf ("main: fim\n");
   exit (0);
}
