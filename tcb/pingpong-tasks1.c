// PingPongOS - PingPong Operating System
// Prof. Carlos A. Maziero, DINF UFPR
// Versão 1.1 -- Julho de 2016

// Teste da gestão básica de tarefas

#include <stdio.h>
#include <stdlib.h>
#include "ppos.h"
#include "../drivers/uartstdio.h"

// TCBs que serão utilizados neste teste
task_t Ping, Pong;

// corpo da thread Ping
void BodyPing()
{
  int i;

  UARTprintf("BodyPing Inicio");
  for (i = 0; i < 4; i++)
  {
    UARTprintf("Ping: %d\n", i);
    task_switch(&Pong);
  }
  UARTprintf("Ping: fim\n");
  task_switch(&Pong);
}

// corpo da thread Pong
void BodyPong()
{
  int i;

  UARTprintf("BodyPong Inicio");
  for (i = 0; i < 4; i++)
  {
    UARTprintf("Pong: %d\n", i);
    task_switch(&Ping);
  }
  UARTprintf("Pong: fim\n");
  task_exit(0);
}                     

void TestePingPong1()
{
  UARTprintf("TestePingPong: Inicio\n");

  task_create(&Ping, BodyPing, "    Ping");
  task_create(&Pong, BodyPong, "        Pong");

  task_switch(&Ping);

  UARTprintf("TestePingPong: Fim\n");
}