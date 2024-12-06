#ifndef ARVORE_AVL_H
#define ARVORE_AVL_H

#include "pilha.h"  // Inclus�o de pilha.h
#include "tarefa.h" // Inclus�o de tarefa.h

// Estrutura de um n� da �rvore
typedef struct No {
    Tarefa tarefa;           // A tarefa armazenada
    struct No* esquerda;     // Ponteiro para o filho � esquerda
    struct No* direita;      // Ponteiro para o filho � direita
} No;

// Fun��es b�sicas da �rvore AVL
No* criarNo(Tarefa tarefa);                        // Cria um novo n� com a tarefa fornecida
No* inserir(No* raiz, Tarefa tarefa);              // Insere uma nova tarefa na �rvore
No* removerNo(No* raiz, int id, Pilha* pilha);     // Remove uma tarefa e salva na pilha
No* buscarNo(No* raiz, int id);                    // Busca uma tarefa pelo ID
No* balancearArvore(No* raiz);                     // Balanceia a �rvore AVL
No* minimo(No* raiz);                              // Encontra o n� com o menor valor
void imprimirEmOrdem(No* raiz);                    // Imprime a �rvore em ordem crescente
void desfazerRemocao(Pilha* pilha, No** raiz);     // Restaura a �ltima tarefa removida

#endif
