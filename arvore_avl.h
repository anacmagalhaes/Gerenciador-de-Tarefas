#ifndef ARVORE_AVL_H
#define ARVORE_AVL_H

#include "pilha.h"  // Inclusão de pilha.h
#include "tarefa.h" // Inclusão de tarefa.h

// Estrutura de um nó da árvore
typedef struct No {
    Tarefa tarefa;           // A tarefa armazenada
    struct No* esquerda;     // Ponteiro para o filho à esquerda
    struct No* direita;      // Ponteiro para o filho à direita
} No;

// Funções básicas da árvore AVL
No* criarNo(Tarefa tarefa);                        // Cria um novo nó com a tarefa fornecida
No* inserir(No* raiz, Tarefa tarefa);              // Insere uma nova tarefa na árvore
No* removerNo(No* raiz, int id, Pilha* pilha);     // Remove uma tarefa e salva na pilha
No* buscarNo(No* raiz, int id);                    // Busca uma tarefa pelo ID
No* balancearArvore(No* raiz);                     // Balanceia a árvore AVL
No* minimo(No* raiz);                              // Encontra o nó com o menor valor
void imprimirEmOrdem(No* raiz);                    // Imprime a árvore em ordem crescente
void desfazerRemocao(Pilha* pilha, No** raiz);     // Restaura a última tarefa removida

#endif
