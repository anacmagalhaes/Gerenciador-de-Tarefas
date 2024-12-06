#ifndef ORDENACAO_H
#define ORDENACAO_H

#include "tarefa.h"      // Inclus�o do arquivo que define a estrutura Tarefa
#include "arvore_avl.h"  // Inclus�o do arquivo que define a �rvore AVL

// Estrutura que representa uma lista de tarefas
typedef struct {
    Tarefa* tarefas;   // Vetor de tarefas
    int quantidade;    // N�mero atual de tarefas na lista
    int capacidade;    // Capacidade m�xima da lista
} ListaTarefas;

// Fun��es para manipular e ordenar a lista de tarefas
void inicializarLista(ListaTarefas* lista, int capacidade);          // Inicializa a lista de tarefas
void liberarLista(ListaTarefas* lista);                              // Libera a mem�ria da lista de tarefas
void inserirNaLista(ListaTarefas* lista, Tarefa tarefa);             // Insere uma tarefa na lista
void ordenarPorData(ListaTarefas* lista);                            // Ordena as tarefas por data
void coletarTarefasEmOrdem(No* raiz, ListaTarefas* lista);           // Coleta tarefas em ordem da �rvore AVL
void imprimirTarefasOrdenadas(No* raiz);                             // Imprime tarefas ordenadas em ordem crescente

#endif
