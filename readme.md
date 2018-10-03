Contexts fazem a troca de registradores e pilha atuais no controlador por uma versão na fila de TCBs.

# ppos_init()

Cria *fila_0 apontando para null

# task_create()

  make_context()
  ```  task_create(&Ping, BodyPing, "    Ping");```  
  ```Ping``` -> struct de task que será iniciada  
  ```BodyPing``` -> Ponteiro inicial de função (enviado por makecontext para o contexto da task)
  ```"Ping"``` -> Argumento NYI

# task_switch(Ping)

```Ping``` -> próxima task inteira com contexto interno que será manuseado e que substituirá o atual.
 
 faz um getcontext (pega os dados rodando atualmente e coloca em um context). Isso atualiza
 o context da task atual.

 dá um setcontext com o contexto da proxima task a ser executada 

 
