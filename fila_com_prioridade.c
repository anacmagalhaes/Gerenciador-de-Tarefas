#include "fila_com_prioridade.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Fun��o para inicializar a fila
void inicializarFila(FilaComPrioridade* fila, int capacidade) {
    fila->tarefas = (Tarefa*) malloc(capacidade * sizeof(Tarefa));  // Aloca a mem�ria para as tarefas
    if (fila->tarefas == NULL) {
        printf("Erro ao alocar memoria para a fila!\n");
        exit(1);  // Se n�o conseguir alocar, sai do programa
    }
    fila->tamanho = 0;  // No come�o, a fila est� vazia
    fila->capacidade = capacidade;  // Define a capacidade inicial da fila
}

// Fun��o para adicionar uma tarefa na fila
void inserirFila(FilaComPrioridade* fila, Tarefa tarefa) {
    // Se a fila estiver cheia, dobra o tamanho da fila
    if (fila->tamanho == fila->capacidade) {
        fila->capacidade *= 2;  // Dobrar a capacidade
        Tarefa* temp = (Tarefa*) realloc(fila->tarefas, fila->capacidade * sizeof(Tarefa));  // Realoca mais espa�o
        if (temp == NULL) {
            printf("Erro ao realocar memoria para a fila!\n");
            exit(1);  // Se n�o conseguir realocar, sai do programa
        }
        fila->tarefas = temp;  // Atualiza o ponteiro da fila
    }

    fila->tarefas[fila->tamanho] = tarefa;  // Adiciona a tarefa no final da fila
    fila->tamanho++;  // Aumenta o tamanho da fila
    printf("Tarefa inserida: %d - %s, Prioridade: %s\n", tarefa.id, tarefa.descricao, tarefa.prioridade);

    // Ordena a fila pela prioridade: Alta > M�dia > Baixa
    for (int i = fila->tamanho - 1; i > 0; i--) {
        int trocar = 0;
        // Se a prioridade for "Alta", e a tarefa anterior n�o for "Alta", troca
        if (strcmp(fila->tarefas[i].prioridade, "Alta") == 0) {
            if (strcmp(fila->tarefas[i-1].prioridade, "Alta") != 0) trocar = 1;
        }
        // Se a prioridade for "M�dia" e a anterior for "Baixa", troca
        else if (strcmp(fila->tarefas[i].prioridade, "Media") == 0) {
            if (strcmp(fila->tarefas[i-1].prioridade, "Baixa") == 0) trocar = 1;
          // Se a prioridade for "Baixa" e a anterior for "M�dia", troca
        } else if (strcmp(fila->tarefas[i].prioridade, "Baixa") == 0) {
            if (strcmp(fila->tarefas[i-1].prioridade, "Media") == 0) trocar = 1;
        }

        // Faz a troca se necess�rio
        if (trocar) {
            Tarefa temp = fila->tarefas[i];
            fila->tarefas[i] = fila->tarefas[i - 1];
            fila->tarefas[i - 1] = temp;
        }
    }
}

// Fun��o para remover a tarefa com maior prioridade
Tarefa removerFila(FilaComPrioridade* fila) {
    if (fila->tamanho == 0) {  // Se a fila estiver vazia
        printf("Fila vazia!\n");
        Tarefa erro = {-1, "", "", 0, 0, 0};  // Retorna um valor de erro
        return erro;
    }

    Tarefa tarefaRemovida = fila->tarefas[0];  // A tarefa com maior prioridade est� na frente

    // Move as outras tarefas uma posi��o para frente
    for (int i = 1; i < fila->tamanho; i++) {
        fila->tarefas[i - 1] = fila->tarefas[i];
    }

    fila->tamanho--;  // Diminui o tamanho da fila
    return tarefaRemovida;  // Retorna a tarefa removida
}

// Fun��o para imprimir todas as tarefas da fila
void imprimirFila(FilaComPrioridade* fila) {
    if (fila->tamanho == 0) {  // Se a fila estiver vazia
        printf("Fila vazia!\n");
        return;
    }

    // Imprime todas as tarefas da fila
    for (int i = 0; i < fila->tamanho; i++) {
        printf("Tarefa %d: %s, Prioridade: %s, Data: %02d/%02d/%04d\n",
               fila->tarefas[i].id,
               fila->tarefas[i].descricao,
               fila->tarefas[i].prioridade,
               fila->tarefas[i].dia,
               fila->tarefas[i].mes,
               fila->tarefas[i].ano);
    }
}

// Fun��o para liberar a mem�ria da fila
void liberarFila(FilaComPrioridade* fila) {
    if (fila->tarefas != NULL) {  // Se a fila tem mem�ria alocada
        free(fila->tarefas);  // Libera a mem�ria
        fila->tarefas = NULL;  // Faz o ponteiro apontar para NULL
    }
    fila->tamanho = 0;  // Zera o tamanho da fila
    fila->capacidade = 0;  // Zera a capacidade da fila
}
