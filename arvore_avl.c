#include "arvore_avl.h"
#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

// Fun��o para criar um novo n�
No* criarNo(Tarefa tarefa) {
    No* novoNo = (No*)malloc(sizeof(No));  // Cria um espa�o na mem�ria para o novo n�

    if (novoNo != NULL) {
        novoNo->tarefa = tarefa;  // Coloca a tarefa no n�
        novoNo->esquerda = NULL;  // Deixa o lado esquerdo vazio
        novoNo->direita = NULL;   // Deixa o lado direito vazio
    }
    return novoNo;  // Retorna o n� criado
}

// Fun��o para inserir uma tarefa na �rvore
No* inserir(No* raiz, Tarefa tarefa) {
    // Se a �rvore estiver vazia, insere o n�
    if (raiz == NULL) {
        No* novoNo = criarNo(tarefa);  // Cria o novo n� com a tarefa
        printf("\nTarefa ID %d inserida com sucesso!\n", tarefa.id);  // Informa que a tarefa foi inserida
        return novoNo;  // Retorna o novo n�
    }

    // Se a tarefa tem ID menor, vai para o lado esquerdo
    if (tarefa.id < raiz->tarefa.id) {
        raiz->esquerda = inserir(raiz->esquerda, tarefa);
    }
    // Se a tarefa tem ID maior, vai para o lado direito
    else if (tarefa.id > raiz->tarefa.id) {
        raiz->direita = inserir(raiz->direita, tarefa);
    }

    // Aqui, a �rvore pode ter ficado desorganizada, ent�o a gente chama o balanceamento
    return balancearArvore(raiz);  // Retorna a �rvore ajustada
}

// Fun��o para calcular o fator de balanceamento (diferen�a de altura entre sub�rvores)
int fatorBalanceamento(No* no) {
    return altura(no->esquerda) - altura(no->direita);
}

// Fun��o para rota��o � direita
No* rotacionarDireita(No* y) {
    No* x = y->esquerda;
    No* T2 = x->direita;

    // Realiza a rota��o
    x->direita = y;
    y->esquerda = T2;

    return x;  // Retorna a nova raiz
}

// Fun��o para rota��o � esquerda
No* rotacionarEsquerda(No* x) {
    No* y = x->direita;
    No* T2 = y->esquerda;

    // Realiza a rota��o
    y->esquerda = x;
    x->direita = T2;

    return y;  // Retorna a nova raiz
}

// Fun��o para balancear a �rvore ap�s uma inser��o
No* balancearArvore(No* no) {
    int balanceamento = fatorBalanceamento(no);

    // Caso 1: Rota��o � direita
    if (balanceamento > 1 && fatorBalanceamento(no->esquerda) >= 0) {
        return rotacionarDireita(no);
    }

    // Caso 2: Rota��o � esquerda
    if (balanceamento < -1 && fatorBalanceamento(no->direita) <= 0) {
        return rotacionarEsquerda(no);
    }

    // Caso 3: Rota��o dupla (esquerda-direita)
    if (balanceamento > 1 && fatorBalanceamento(no->esquerda) < 0) {
        no->esquerda = rotacionarEsquerda(no->esquerda);
        return rotacionarDireita(no);
    }

    // Caso 4: Rota��o dupla (direita-esquerda)
    if (balanceamento < -1 && fatorBalanceamento(no->direita) > 0) {
        no->direita = rotacionarDireita(no->direita);
        return rotacionarEsquerda(no);
    }

    return no;  // Retorna o n� (sem altera��es)
}


// Fun��o para procurar um n� com um ID espec�fico
No* buscarNo(No* raiz, int id) {
    // Se a �rvore est� vazia, significa que a tarefa n�o foi encontrada
    if (raiz == NULL) {
        printf("Tarefa n�o encontrada.\n");
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
        return raiz;  // Retorna o n� que foi encontrado
    }

    // Se o ID da tarefa for menor, vamos para a esquerda, caso contr�rio, para a direita
    if (id < raiz->tarefa.id) {
        return buscarNo(raiz->esquerda, id);
    } else {
        return buscarNo(raiz->direita, id);
    }
}

// Fun��o para remover um n� da �rvore
No* removerNo(No* raiz, int id, Pilha* pilha) {
    // Se a �rvore estiver vazia, n�o tem nada para remover
    if (raiz == NULL) {
        return NULL;
    }

    // Se o ID for menor, tenta remover � esquerda
    if (id < raiz->tarefa.id) {
        raiz->esquerda = removerNo(raiz->esquerda, id, pilha);
    }
    // Se o ID for maior, tenta remover � direita
    else if (id > raiz->tarefa.id) {
        raiz->direita = removerNo(raiz->direita, id, pilha);
    } else {
        // Se encontramos o n�, vamos remov�-lo
        printf("Removendo tarefa com ID: %d\n", raiz->tarefa.id);
        empilhar(pilha, raiz->tarefa);  // Coloca a tarefa removida na pilha

        // Caso 1: O n� n�o tem filhos ou tem s� um filho
        if (raiz->esquerda == NULL) {
            No* temp = raiz->direita;  // Pega o filho da direita
            free(raiz);  // Libera a mem�ria do n�
            return temp;  // Retorna o filho
        } else if (raiz->direita == NULL) {
            No* temp = raiz->esquerda;  // Pega o filho da esquerda
            free(raiz);  // Libera a mem�ria do n�
            return temp;  // Retorna o filho
        }

        // Caso 2: O n� tem dois filhos
        No* temp = minimo(raiz->direita);  // Encontra o menor n� � direita
        raiz->tarefa = temp->tarefa;  // Substitui a tarefa do n� removido pela do sucessor
        raiz->direita = removerNo(raiz->direita, temp->tarefa.id, pilha);  // Remove o sucessor
    }
    return raiz;  // Retorna a raiz depois da remo��o
}

// Fun��o para encontrar o n� mais � esquerda (o m�nimo)
No* minimo(No* raiz) {
    // Vai at� o n� mais � esquerda
    while (raiz && raiz->esquerda != NULL) {
        raiz = raiz->esquerda;  // Continua indo para a esquerda
    }
    return raiz;  // Retorna o n� mais � esquerda
}

// Fun��o para calcular a altura de um n�
int altura(No* no) {
    if (no == NULL) {
        return 0;  // Se n�o tiver n�, a altura � 0
    }
    // Calcula a altura da sub�rvore esquerda e da sub�rvore direita
    int alturaEsquerda = altura(no->esquerda);
    int alturaDireita = altura(no->direita);
    return (alturaEsquerda > alturaDireita ? alturaEsquerda : alturaDireita) + 1;  // Retorna a maior altura
}

// Fun��o para desfazer a remo��o de uma tarefa
void desfazerRemocao(Pilha* pilha, No** raiz) {
    if (pilha->topo == -1) {
        printf("N�o h� tarefas removidas para desfazer.\n");
        return;
    }

    // Desempilha a tarefa removida
    Tarefa tarefaDesfeita = desempilhar(pilha);
    printf("Desfazendo remo��o da tarefa com ID %d...\n", tarefaDesfeita.id);

    // Reinseri a tarefa na �rvore
    *raiz = inserir(*raiz, tarefaDesfeita);
    printf("Tarefa com ID %d reinserida com sucesso!\n", tarefaDesfeita.id);
}

// Fun��o para imprimir os n�s da �rvore em ordem (in-order traversal)
void imprimirEmOrdem(No* raiz) {
    if (raiz != NULL) {
        // Recursivamente imprime a sub�rvore � esquerda
        imprimirEmOrdem(raiz->esquerda);

        // Imprime o n� atual
        printf("ID: %d\n", raiz->tarefa.id);
        printf("Descricao: %s\n", raiz->tarefa.descricao);
        printf("Prioridade: %s\n", raiz->tarefa.prioridade);
        printf("Data: %02d/%02d/%04d\n", raiz->tarefa.dia, raiz->tarefa.mes, raiz->tarefa.ano);
        printf("----------------------------\n");

        // Recursivamente imprime a sub�rvore � direita
        imprimirEmOrdem(raiz->direita);
    }
}
