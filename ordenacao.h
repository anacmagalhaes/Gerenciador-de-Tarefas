#ifndef ORDENACAO_H
#define ORDENACAO_H

#include "tarefa.h"      // Inclusão do arquivo que define a estrutura Tarefa
#include "arvore_avl.h"  // Inclusão do arquivo que define a árvore AVL

// Estrutura que representa uma lista de tarefas
typedef struct {
    Tarefa* tarefas;   // Vetor de tarefas
    int quantidade;    // Número atual de tarefas na lista
    int capacidade;    // Capacidade máxima da lista
} ListaTarefas;

// Funções para manipular e ordenar a lista de tarefas
void inicializarLista(ListaTarefas* lista, int capacidade);          // Inicializa a lista de tarefas
void liberarLista(ListaTarefas* lista);                              // Libera a memória da lista de tarefas
void inserirNaLista(ListaTarefas* lista, Tarefa tarefa);             // Insere uma tarefa na lista
void ordenarPorData(ListaTarefas* lista);                            // Ordena as tarefas por data
void coletarTarefasEmOrdem(No* raiz, ListaTarefas* lista);           // Coleta tarefas em ordem da árvore AVL
void imprimirTarefasOrdenadas(No* raiz);                             // Imprime tarefas ordenadas em ordem crescente

#endif
