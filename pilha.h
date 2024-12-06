#ifndef PILHA_H
#define PILHA_H

#include "tarefa.h"       // Inclusão do arquivo que define a estrutura Tarefa
#define MAX_PILHA 100     // Define o tamanho máximo da pilha

// Estrutura da pilha
typedef struct {
    Tarefa itens[MAX_PILHA];  // Array para armazenar as tarefas
    int topo;                 // Índice do topo da pilha
} Pilha;

// Funções para manipulação da pilha
void inicializarPilha(Pilha* pilha);        // Inicializa a pilha
int pilhaVazia(Pilha* pilha);               // Verifica se a pilha está vazia
int pilhaCheia(Pilha* pilha);               // Verifica se a pilha está cheia
void empilhar(Pilha* pilha, Tarefa tarefa); // Adiciona uma tarefa na pilha
Tarefa desempilhar(Pilha* pilha);          // Remove e retorna a tarefa do topo da pilha
void exibirHistorico(Pilha* pilha);        // Exibe o histórico de tarefas removidas

#endif
