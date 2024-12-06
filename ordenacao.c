#include "ordenacao.h"
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <string.h>

// Função para inicializar a lista de tarefas
void inicializarLista(ListaTarefas* lista, int capacidade) {
    setlocale(LC_ALL, "Portuguese"); // Ajusta a localidade para português
    // Aloca memória para a lista de tarefas
    lista->tarefas = (Tarefa*)malloc(capacidade * sizeof(Tarefa));
    if (lista->tarefas == NULL) {  // Verifica se deu erro na alocação de memória
        printf("Erro ao alocar memória para a lista!\n");
        exit(1);  // Encerra o programa se der erro
    }
    lista->quantidade = 0;  // Inicializa a quantidade de tarefas como 0
    lista->capacidade = capacidade;  // Define a capacidade inicial da lista
}

// Função para liberar a memória alocada para a lista
void liberarLista(ListaTarefas* lista) {
    if (lista->tarefas != NULL) {  // Se a lista não estiver vazia
        free(lista->tarefas);  // Libera a memória da lista
        lista->tarefas = NULL;  // Define o ponteiro como NULL para evitar erros
    }
    lista->quantidade = 0;  // Zera a quantidade de tarefas
    lista->capacidade = 0;  // Zera a capacidade da lista
}

// Função para adicionar uma tarefa à lista
void inserirNaLista(ListaTarefas* lista, Tarefa tarefa) {
    if (lista->quantidade >= lista->capacidade) {  // Se a lista estiver cheia
        lista->capacidade *= 2;  // Dobra a capacidade da lista
        // Tenta realocar memória para a nova capacidade
        Tarefa* temp = (Tarefa*)realloc(lista->tarefas, lista->capacidade * sizeof(Tarefa));
        if (temp == NULL) {  // Se a realocação falhar
            printf("Erro ao realocar memória para a lista!\n");
            exit(1);  // Encerra o programa
        }
        lista->tarefas = temp;  // Atribui o novo ponteiro à lista
    }
    lista->tarefas[lista->quantidade] = tarefa;  // Adiciona a tarefa na lista
    lista->quantidade++;  // Aumenta a quantidade de tarefas
}

// Função para comparar duas tarefas pelas datas (ano, mês, dia)
int compararDatas(Tarefa t1, Tarefa t2) {
    if (t1.ano != t2.ano) return t1.ano - t2.ano;  // Se os anos são diferentes, compara os anos
    if (t1.mes != t2.mes) return t1.mes - t2.mes;  // Se os meses são diferentes, compara os meses
    return t1.dia - t2.dia;  // Se os dias são diferentes, compara os dias
}

// Função de ordenação Bubble Sort
void bubbleSort(ListaTarefas* lista, long* comparacoes, long* trocas) {
    *comparacoes = 0;  // Inicializa o contador de comparações
    *trocas = 0;  // Inicializa o contador de trocas

    // Percorre todos os elementos da lista
    for (int i = 0; i < lista->quantidade - 1; i++) {
        for (int j = 0; j < lista->quantidade - i - 1; j++) {
            (*comparacoes)++;  // Conta a comparação
            // Se a tarefa da posição j é depois da tarefa de j+1
            if (compararDatas(lista->tarefas[j], lista->tarefas[j + 1]) > 0) {
                Tarefa temp = lista->tarefas[j];  // Troca as duas tarefas de lugar
                lista->tarefas[j] = lista->tarefas[j + 1];
                lista->tarefas[j + 1] = temp;
                (*trocas)++;  // Conta a troca
            }
        }
    }
}

// Função para particionar a lista durante o Quick Sort
int particionar(ListaTarefas* lista, int baixo, int alto, long* comparacoes, long* trocas) {
    Tarefa pivo = lista->tarefas[alto];  // O pivô é a última tarefa da lista
    int i = (baixo - 1);  // Inicializa o índice do menor elemento

    // Percorre a lista e faz a troca de elementos que são menores que o pivô
    for (int j = baixo; j <= alto - 1; j++) {
        (*comparacoes)++;  // Conta a comparação
        if (compararDatas(lista->tarefas[j], pivo) <= 0) {  // Se a tarefa for menor ou igual ao pivô
            i++;  // Aumenta o índice do menor elemento
            // Troca os elementos
            Tarefa temp = lista->tarefas[i];
            lista->tarefas[i] = lista->tarefas[j];
            lista->tarefas[j] = temp;
            (*trocas)++;  // Conta a troca
        }
    }
    // Troca o pivô com o elemento na posição i + 1
    Tarefa temp = lista->tarefas[i + 1];
    lista->tarefas[i + 1] = lista->tarefas[alto];
    lista->tarefas[alto] = temp;
    (*trocas)++;  // Conta a troca

    return (i + 1);  // Retorna a posição do pivô
}

// Função recursiva para o Quick Sort
void quickSortRecursivo(ListaTarefas* lista, int baixo, int alto, long* comparacoes, long* trocas) {
    if (baixo < alto) {
        // Divide a lista e ordena as duas partes
        int pi = particionar(lista, baixo, alto, comparacoes, trocas);
        quickSortRecursivo(lista, baixo, pi - 1, comparacoes, trocas);  // Ordena a parte esquerda
        quickSortRecursivo(lista, pi + 1, alto, comparacoes, trocas);  // Ordena a parte direita
    }
}

// Função para ordenar a lista usando o Quick Sort
void quickSort(ListaTarefas* lista, long* comparacoes, long* trocas) {
    *comparacoes = 0;  // Inicializa o contador de comparações
    *trocas = 0;  // Inicializa o contador de trocas
    quickSortRecursivo(lista, 0, lista->quantidade - 1, comparacoes, trocas);  // Chama a função recursiva
}


// Função para comparar o desempenho dos algoritmos de ordenação
void compararAlgoritmosOrdenacao(ListaTarefas* lista) {
    ListaTarefas copia1, copia2, copia3;
    inicializarLista(&copia1, lista->capacidade);  // Cria uma cópia da lista para o Bubble Sort
    inicializarLista(&copia2, lista->capacidade);  // Cria uma cópia da lista para o Quick Sort
    inicializarLista(&copia3, lista->capacidade);  // Cria uma cópia da lista para o Insertion Sort

    // Copia todos os elementos da lista original para as cópias
    for (int i = 0; i < lista->quantidade; i++) {
        inserirNaLista(&copia1, lista->tarefas[i]);
        inserirNaLista(&copia2, lista->tarefas[i]);
        inserirNaLista(&copia3, lista->tarefas[i]);
    }

    clock_t inicio, fim;
    double tempo;
    long comparacoes, trocas;



    // Testa o Bubble Sort
    inicio = clock();  // Marca o início do tempo
    bubbleSort(&copia1, &comparacoes, &trocas);  // Ordena com o Bubble Sort
    fim = clock();  // Marca o fim do tempo
    tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;  // Calcula o tempo
    printf("Bubble Sort:\n");
    printf("Tempo: %f segundos\n", tempo);

    // Testa o Quick Sort
    inicio = clock();
    quickSort(&copia2, &comparacoes, &trocas);
    fim = clock();
    tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Quick Sort:\n");
    printf("Tempo: %f segundos\n", tempo);
}

// Função para ordenar as tarefas pela data, usando Quick Sort
void ordenarPorData(ListaTarefas* lista) {
    long comparacoes, trocas;
    quickSort(lista, &comparacoes, &trocas);  // Chama o Quick Sort
}

// Função para coletar as tarefas da árvore em ordem e armazená-las na lista
void coletarTarefasEmOrdem(No* raiz, ListaTarefas* lista) {
    if (raiz == NULL) {
        return;  // Se a árvore está vazia ou chegou ao fim, não faz nada
    }

    // Percorre a subárvore esquerda
    coletarTarefasEmOrdem(raiz->esquerda, lista);

    // Insere a tarefa da raiz na lista
    inserirNaLista(lista, raiz->tarefa);

    // Percorre a subárvore direita
    coletarTarefasEmOrdem(raiz->direita, lista);
}
