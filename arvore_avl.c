#include "arvore_avl.h"
#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

// Função para criar um novo nó
No* criarNo(Tarefa tarefa) {
    No* novoNo = (No*)malloc(sizeof(No));  // Cria um espaço na memória para o novo nó

    if (novoNo != NULL) {
        novoNo->tarefa = tarefa;  // Coloca a tarefa no nó
        novoNo->esquerda = NULL;  // Deixa o lado esquerdo vazio
        novoNo->direita = NULL;   // Deixa o lado direito vazio
    }
    return novoNo;  // Retorna o nó criado
}

// Função para inserir uma tarefa na árvore
No* inserir(No* raiz, Tarefa tarefa) {
    // Se a árvore estiver vazia, insere o nó
    if (raiz == NULL) {
        No* novoNo = criarNo(tarefa);  // Cria o novo nó com a tarefa
        printf("\nTarefa ID %d inserida com sucesso!\n", tarefa.id);  // Informa que a tarefa foi inserida
        return novoNo;  // Retorna o novo nó
    }

    // Se a tarefa tem ID menor, vai para o lado esquerdo
    if (tarefa.id < raiz->tarefa.id) {
        raiz->esquerda = inserir(raiz->esquerda, tarefa);
    }
    // Se a tarefa tem ID maior, vai para o lado direito
    else if (tarefa.id > raiz->tarefa.id) {
        raiz->direita = inserir(raiz->direita, tarefa);
    }

    // Aqui, a árvore pode ter ficado desorganizada, então a gente chama o balanceamento
    return balancearArvore(raiz);  // Retorna a árvore ajustada
}

// Função para calcular o fator de balanceamento (diferença de altura entre subárvores)
int fatorBalanceamento(No* no) {
    return altura(no->esquerda) - altura(no->direita);
}

// Função para rotação à direita
No* rotacionarDireita(No* y) {
    No* x = y->esquerda;
    No* T2 = x->direita;

    // Realiza a rotação
    x->direita = y;
    y->esquerda = T2;

    return x;  // Retorna a nova raiz
}

// Função para rotação à esquerda
No* rotacionarEsquerda(No* x) {
    No* y = x->direita;
    No* T2 = y->esquerda;

    // Realiza a rotação
    y->esquerda = x;
    x->direita = T2;

    return y;  // Retorna a nova raiz
}

// Função para balancear a árvore após uma inserção
No* balancearArvore(No* no) {
    int balanceamento = fatorBalanceamento(no);

    // Caso 1: Rotação à direita
    if (balanceamento > 1 && fatorBalanceamento(no->esquerda) >= 0) {
        return rotacionarDireita(no);
    }

    // Caso 2: Rotação à esquerda
    if (balanceamento < -1 && fatorBalanceamento(no->direita) <= 0) {
        return rotacionarEsquerda(no);
    }

    // Caso 3: Rotação dupla (esquerda-direita)
    if (balanceamento > 1 && fatorBalanceamento(no->esquerda) < 0) {
        no->esquerda = rotacionarEsquerda(no->esquerda);
        return rotacionarDireita(no);
    }

    // Caso 4: Rotação dupla (direita-esquerda)
    if (balanceamento < -1 && fatorBalanceamento(no->direita) > 0) {
        no->direita = rotacionarDireita(no->direita);
        return rotacionarEsquerda(no);
    }

    return no;  // Retorna o nó (sem alterações)
}


// Função para procurar um nó com um ID específico
No* buscarNo(No* raiz, int id) {
    // Se a árvore está vazia, significa que a tarefa não foi encontrada
    if (raiz == NULL) {
        printf("Tarefa não encontrada.\n");
        return NULL;
    }

    // Se encontramos a tarefa com o ID igual ao da raiz
    if (id == raiz->tarefa.id) {
        printf("Tarefa encontrada: \n");
        printf("\nID: %d\n", raiz->tarefa.id);
        printf("Descricao: %s\n", raiz->tarefa.descricao);
        printf("Prioridade: %s\n", raiz->tarefa.prioridade);
        printf("Data: %02d/%02d/%04d\n", raiz->tarefa.dia, raiz->tarefa.mes, raiz->tarefa.ano);
        printf("-----------------------\n");
        return raiz;  // Retorna o nó que foi encontrado
    }

    // Se o ID da tarefa for menor, vamos para a esquerda, caso contrário, para a direita
    if (id < raiz->tarefa.id) {
        return buscarNo(raiz->esquerda, id);
    } else {
        return buscarNo(raiz->direita, id);
    }
}

// Função para remover um nó da árvore
No* removerNo(No* raiz, int id, Pilha* pilha) {
    // Se a árvore estiver vazia, não tem nada para remover
    if (raiz == NULL) {
        return NULL;
    }

    // Se o ID for menor, tenta remover à esquerda
    if (id < raiz->tarefa.id) {
        raiz->esquerda = removerNo(raiz->esquerda, id, pilha);
    }
    // Se o ID for maior, tenta remover à direita
    else if (id > raiz->tarefa.id) {
        raiz->direita = removerNo(raiz->direita, id, pilha);
    } else {
        // Se encontramos o nó, vamos removê-lo
        printf("Removendo tarefa com ID: %d\n", raiz->tarefa.id);
        empilhar(pilha, raiz->tarefa);  // Coloca a tarefa removida na pilha

        // Caso 1: O nó não tem filhos ou tem só um filho
        if (raiz->esquerda == NULL) {
            No* temp = raiz->direita;  // Pega o filho da direita
            free(raiz);  // Libera a memória do nó
            return temp;  // Retorna o filho
        } else if (raiz->direita == NULL) {
            No* temp = raiz->esquerda;  // Pega o filho da esquerda
            free(raiz);  // Libera a memória do nó
            return temp;  // Retorna o filho
        }

        // Caso 2: O nó tem dois filhos
        No* temp = minimo(raiz->direita);  // Encontra o menor nó à direita
        raiz->tarefa = temp->tarefa;  // Substitui a tarefa do nó removido pela do sucessor
        raiz->direita = removerNo(raiz->direita, temp->tarefa.id, pilha);  // Remove o sucessor
    }
    return raiz;  // Retorna a raiz depois da remoção
}

// Função para encontrar o nó mais à esquerda (o mínimo)
No* minimo(No* raiz) {
    // Vai até o nó mais à esquerda
    while (raiz && raiz->esquerda != NULL) {
        raiz = raiz->esquerda;  // Continua indo para a esquerda
    }
    return raiz;  // Retorna o nó mais à esquerda
}

// Função para calcular a altura de um nó
int altura(No* no) {
    if (no == NULL) {
        return 0;  // Se não tiver nó, a altura é 0
    }
    // Calcula a altura da subárvore esquerda e da subárvore direita
    int alturaEsquerda = altura(no->esquerda);
    int alturaDireita = altura(no->direita);
    return (alturaEsquerda > alturaDireita ? alturaEsquerda : alturaDireita) + 1;  // Retorna a maior altura
}

// Função para desfazer a remoção de uma tarefa
void desfazerRemocao(Pilha* pilha, No** raiz) {
    if (pilha->topo == -1) {
        printf("Não há tarefas removidas para desfazer.\n");
        return;
    }

    // Desempilha a tarefa removida
    Tarefa tarefaDesfeita = desempilhar(pilha);
    printf("Desfazendo remoção da tarefa com ID %d...\n", tarefaDesfeita.id);

    // Reinseri a tarefa na árvore
    *raiz = inserir(*raiz, tarefaDesfeita);
    printf("Tarefa com ID %d reinserida com sucesso!\n", tarefaDesfeita.id);
}

// Função para imprimir os nós da árvore em ordem (in-order traversal)
void imprimirEmOrdem(No* raiz) {
    if (raiz != NULL) {
        // Recursivamente imprime a subárvore à esquerda
        imprimirEmOrdem(raiz->esquerda);

        // Imprime o nó atual
        printf("ID: %d\n", raiz->tarefa.id);
        printf("Descricao: %s\n", raiz->tarefa.descricao);
        printf("Prioridade: %s\n", raiz->tarefa.prioridade);
        printf("Data: %02d/%02d/%04d\n", raiz->tarefa.dia, raiz->tarefa.mes, raiz->tarefa.ano);
        printf("----------------------------\n");

        // Recursivamente imprime a subárvore à direita
        imprimirEmOrdem(raiz->direita);
    }
}
