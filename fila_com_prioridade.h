#ifndef FILA_COM_PRIORIDADE_H
#define FILA_COM_PRIORIDADE_H

#include "tarefa.h"

// Estrutura que representa a fila com prioridade
typedef struct {
    Tarefa* tarefas;   // Vetor de tarefas
    int tamanho;       // Número atual de tarefas na fila
    int capacidade;    // Capacidade máxima da fila
} FilaComPrioridade;

// Funções para manipular a fila com prioridade
void inicializarFila(FilaComPrioridade* fila, int capacidade);  // Inicializa a fila
void inserirFila(FilaComPrioridade* fila, Tarefa tarefa);       // Insere uma tarefa na fila
Tarefa removerFila(FilaComPrioridade* fila);                    // Remove uma tarefa da fila
void imprimirFila(FilaComPrioridade* fila);                     // Imprime as tarefas na fila
void liberarFila(FilaComPrioridade* fila);                      // Libera a memória da fila

#endif


