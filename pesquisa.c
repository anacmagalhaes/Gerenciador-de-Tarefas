#include "pesquisa.h"
#include <stdio.h>
#include <locale.h>

// Fun��o para verificar se a lista est� ordenada por ID
int estaOrdenadaPorId(Tarefa* lista, int tamanho) {
    // Percorre a lista verificando se cada ID est� em ordem crescente
    for (int i = 0; i < tamanho - 1; i++) {
        if (lista[i].id > lista[i + 1].id) {  // Se encontrar um ID maior que o pr�ximo, a lista n�o est� ordenada
            return 0;  // Retorna 0 (falso) se n�o estiver ordenada
        }
    }
    return 1;  // Retorna 1 (verdadeiro) se a lista estiver ordenada
}

// Fun��o para realizar a busca bin�ria na lista ordenada por ID
int buscaBinaria(Tarefa* lista, int tamanho, int idBuscado) {
    int inicio = 0;
    int fim = tamanho - 1;
    int comparacoes = 0;  // Contador de compara��es feitas


    // Enquanto o intervalo de busca for v�lido
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;  // Calcula o meio do intervalo
        comparacoes++;  // Conta a compara��o

        if (lista[meio].id == idBuscado) {  // Se o ID no meio for o buscado

            return meio;  // Retorna o �ndice onde o ID foi encontrado
        }
        if (lista[meio].id < idBuscado) {  // Se o ID do meio for menor que o buscado

            inicio = meio + 1;  // Ajusta o in�cio para a metade superior
        } else {  // Se o ID do meio for maior que o buscado
            fim = meio - 1;  // Ajusta o fim para a metade inferior
        }
    }

    return -1;  // Retorna -1 se n�o encontrar o ID na lista
}

// Fun��o para realizar a busca linear na lista
int buscaLinear(Tarefa* lista, int tamanho, int idBuscado) {
    int comparacoes = 0;  // Contador de compara��es feitas

    // Percorre toda a lista procurando pelo ID
    for (int i = 0; i < tamanho; i++) {
        comparacoes++;  // Conta cada compara��o


        if (lista[i].id == idBuscado) {  // Se encontrar o ID buscado
            return i;  // Retorna o �ndice onde o ID foi encontrado
        }
    }

    return -1;  // Retorna -1 se n�o encontrar o ID na lista
}

// Fun��o para buscar uma tarefa na lista, usando a busca apropriada
Tarefa* buscarTarefa(ListaTarefas* lista, int idBuscado) {
    int indice;

    if (estaOrdenadaPorId(lista->tarefas, lista->quantidade)) {
        // Se a lista estiver ordenada, usa busca bin�ria
        indice = buscaBinaria(lista->tarefas, lista->quantidade, idBuscado);
    } else {
        // Se a lista n�o estiver ordenada, usa busca linear
        indice = buscaLinear(lista->tarefas, lista->quantidade, idBuscado);
    }

    if (indice != -1) {
        // Se encontrou a tarefa, exibe suas informa��es
        printf("Tarefa encontrada:\n");
        printf("ID: %d\n", lista->tarefas[indice].id);
        printf("Descricao: %s\n", lista->tarefas[indice].descricao);
        printf("Prioridade: %s\n", lista->tarefas[indice].prioridade);
        printf("Data: %02d/%02d/%04d\n",
               lista->tarefas[indice].dia,
               lista->tarefas[indice].mes,
               lista->tarefas[indice].ano);
        return &lista->tarefas[indice];  // Retorna um ponteiro para a tarefa encontrada
    } else {
        // Se n�o encontrou, exibe mensagem de erro
        printf("Tarefa n�o encontrada!\n");
        return NULL;  // Retorna NULL se n�o encontrar a tarefa
    }
}
