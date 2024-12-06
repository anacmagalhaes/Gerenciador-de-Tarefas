#ifndef PILHA_H
#define PILHA_H

#include "tarefa.h"       // Inclus�o do arquivo que define a estrutura Tarefa
#define MAX_PILHA 100     // Define o tamanho m�ximo da pilha

// Estrutura da pilha
typedef struct {
    Tarefa itens[MAX_PILHA];  // Array para armazenar as tarefas
    int topo;                 // �ndice do topo da pilha
} Pilha;

// Fun��es para manipula��o da pilha
void inicializarPilha(Pilha* pilha);        // Inicializa a pilha
int pilhaVazia(Pilha* pilha);               // Verifica se a pilha est� vazia
int pilhaCheia(Pilha* pilha);               // Verifica se a pilha est� cheia
void empilhar(Pilha* pilha, Tarefa tarefa); // Adiciona uma tarefa na pilha
Tarefa desempilhar(Pilha* pilha);          // Remove e retorna a tarefa do topo da pilha
void exibirHistorico(Pilha* pilha);        // Exibe o hist�rico de tarefas removidas

#endif
