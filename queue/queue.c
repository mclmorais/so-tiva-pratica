
#include "queue.h"
#include <stdint.h>
#include "utils\uartstdio.h"

//------------------------------------------------------------------------------
// Insere um elemento no final da fila.
// Condicoes a verificar, gerando msgs de erro:
// - a fila deve existir
// - o elemento deve existir
// - o elemento nao deve estar em outra fila

void queue_append(queue_t **queue, queue_t *elem)
{
	// Se o elemento for nulo ou se ja fizer parte de outra fila retorna sem fazer nada
	if (elem == NULL || elem->prev != NULL || elem->next != NULL)
		return;
	

	// Se for o primeiro elemento, faz o elemento auxiliar apontar para o novo elemento
	// e faz este elemento apontar para si mesmo nas duas direções. Também faz o primeiro
	// elemento ser o mesmo deste que foi colocado
	if ((*queue) == NULL)
	{
		(*queue) = elem;
		(*queue)->next = elem;
		(*queue)->prev = elem;
	}
	// Para os próximos elementos,
	else
	{

		//Itera até chegar no final da fila
		queue_t *temp = *queue;
		while (temp->next != *queue)
		{
			temp = temp->next;
		}

		// Faz o next do ultimo elemento apontar para o novo elemento
		temp->next = elem;

		//Pega o first a partir do next do ultimo e bota no novo elemento
		elem->next = *queue;
		// Faz o prev do novo apontar para o auxiliar (que até agora era o último)
		elem->prev = temp;
		// Faz o previous do first apontar para o novo elemento
		(*queue)->prev = elem;
	}
}

//------------------------------------------------------------------------------
// Remove o elemento indicado da fila, sem o destruir.
// Condicoes a verificar, gerando msgs de erro:
// - a fila deve existir
// - a fila nao deve estar vazia
// - o elemento deve existir
// - o elemento deve pertencer a fila indicada
// Retorno: apontador para o elemento removido, ou NULL se erro

queue_t *queue_remove(queue_t **queue, queue_t *elem)
{

	if (*queue == NULL ||
			(*queue)->next == NULL ||
			(*queue)->prev == NULL ||
			elem == NULL)
	{
		return NULL;
	}

	struct queue_t *qpos = (*queue);

	while (qpos != elem)
	{
		qpos = qpos->next;
		if (qpos == *queue)
			return NULL; //Não está na fila!!
		
	};

	if ((*queue)->next == (*queue))
	{
		*queue = NULL;
		elem->next = NULL;
		elem->prev = NULL;
		return elem;
	}
	if (qpos == *queue)
	{
		*queue = (*queue)->next;
	}
	qpos->prev->next = elem->next;
	qpos->next->prev = elem->prev;
	elem->next = NULL;
	elem->prev = NULL;

	return elem;
}

//------------------------------------------------------------------------------
// Conta o numero de elementos na fila
// Retorno: numero de elementos na fila

//int queue_size (queue_t *queue){
//	struct queue_t *qpos;
//	int i = 0;
//	if (queue == NULL) return i;
//	qpos = queue;
//	do{
//		i++;
//		qpos = qpos->next;
//	}while(qpos->next != queue);
//	return i;
//}

int queue_size(queue_t *queue)
{
	queue_t *aux = queue;
	int ct = 0;
	if (aux != NULL)
	{
		ct = 1;
		while (aux->next != queue)
		{
			aux = aux->next;
			ct++;
		}
	}

	return ct;
}

//------------------------------------------------------------------------------
// Percorre a fila e imprime na tela seu conteúdo. A impressão de cada
// elemento é feita por uma função externa, definida pelo programa que
// usa a biblioteca.
//
// Essa função deve ter o seguinte protótipo:
//
// void print_elem (void *ptr) ; // ptr aponta para o elemento a imprimir

void queue_print(char *name, queue_t *queue, void print_elem(void *))
{

	UARTprintf(name);
	if (queue == NULL)
		return;
	
	struct queue_t *qpos = queue;
	while (qpos->next != queue)
	{
		print_elem(qpos);
		qpos = qpos->next;
	}
	UARTprintf("\n");
	 
}