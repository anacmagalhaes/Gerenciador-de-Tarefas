#include "ordenacao.h"
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <string.h>

// Fun��o para inicializar a lista de tarefas
void inicializarLista(ListaTarefas* lista, int capacidade) {
    setlocale(LC_ALL, "Portuguese"); // Ajusta a localidade para portugu�s
    // Aloca mem�ria para a lista de tarefas
    lista->tarefas = (Tarefa*)malloc(capacidade * sizeof(Tarefa));
    if (lista->tarefas == NULL) {  // Verifica se deu erro na aloca��o de mem�ria
        printf("Erro ao alocar mem�ria para a lista!\n");
        exit(1);  // Encerra o programa se der erro
    }
    lista->quantidade = 0;  // Inicializa a quantidade de tarefas como 0
    lista->capacidade = capacidade;  // Define a capacidade inicial da lista
}

// Fun��o para liberar a mem�ria alocada para a lista
void liberarLista(ListaTarefas* lista) {
    if (lista->tarefas != NULL) {  // Se a lista n�o estiver vazia
        free(lista->tarefas);  // Libera a mem�ria da lista
        lista->tarefas = NULL;  // Define o ponteiro como NULL para evitar erros
    }
    lista->quantidade = 0;  // Zera a quantidade de tarefas
    lista->capacidade = 0;  // Zera a capacidade da lista
}

// Fun��o para adicionar uma tarefa � lista
void inserirNaLista(ListaTarefas* lista, Tarefa tarefa) {
    if (lista->quantidade >= lista->capacidade) {  // Se a lista estiver cheia
        lista->capacidade *= 2;  // Dobra a capacidade da lista
        // Tenta realocar mem�ria para a nova capacidade
        Tarefa* temp = (Tarefa*)realloc(lista->tarefas, lista->capacidade * sizeof(Tarefa));
        if (temp == NULL) {  // Se a realoca��o falhar
            printf("Erro ao realocar mem�ria para a lista!\n");
            exit(1);  // Encerra o programa
        }
        lista->tarefas = temp;  // Atribui o novo ponteiro � lista
    }
    lista->tarefas[lista->quantidade] = tarefa;  // Adiciona a tarefa na lista
    lista->quantidade++;  // Aumenta a quantidade de tarefas
}

// Fun��o para comparar duas tarefas pelas datas (ano, m�s, dia)
int compararDatas(Tarefa t1, Tarefa t2) {
    if (t1.ano != t2.ano) return t1.ano - t2.ano;  // Se os anos s�o diferentes, compara os anos
    if (t1.mes != t2.mes) return t1.mes - t2.mes;  // Se os meses s�o diferentes, compara os meses
    return t1.dia - t2.dia;  // Se os dias s�o diferentes, compara os dias
}

// Fun��o de ordena��o Bubble Sort
void bubbleSort(ListaTarefas* lista, long* comparacoes, long* trocas) {
    *comparacoes = 0;  // Inicializa o contador de compara��es
    *trocas = 0;  // Inicializa o contador de trocas

    // Percorre todos os elementos da lista
    for (int i = 0; i < lista->quantidade - 1; i++) {
        for (int j = 0; j < lista->quantidade - i - 1; j++) {
            (*comparacoes)++;  // Conta a compara��o
            // Se a tarefa da posi��o j � depois da tarefa de j+1
            if (compararDatas(lista->tarefas[j], lista->tarefas[j + 1]) > 0) {
                Tarefa temp = lista->tarefas[j];  // Troca as duas tarefas de lugar
                lista->tarefas[j] = lista->tarefas[j + 1];
                lista->tarefas[j + 1] = temp;
                (*trocas)++;  // Conta a troca
            }
        }
    }
}

// Fun��o para particionar a lista durante o Quick Sort
int particionar(ListaTarefas* lista, int baixo, int alto, long* comparacoes, long* trocas) {
    Tarefa pivo = lista->tarefas[alto];  // O piv� � a �ltima tarefa da lista
    int i = (baixo - 1);  // Inicializa o �ndice do menor elemento

    // Percorre a lista e faz a troca de elementos que s�o menores que o piv�
    for (int j = baixo; j <= alto - 1; j++) {
        (*comparacoes)++;  // Conta a compara��o
        if (compararDatas(lista->tarefas[j], pivo) <= 0) {  // Se a tarefa for menor ou igual ao piv�
            i++;  // Aumenta o �ndice do menor elemento
            // Troca os elementos
            Tarefa temp = lista->tarefas[i];
            lista->tarefas[i] = lista->tarefas[j];
            lista->tarefas[j] = temp;
            (*trocas)++;  // Conta a troca
        }
    }
    // Troca o piv� com o elemento na posi��o i + 1
    Tarefa temp = lista->tarefas[i + 1];
    lista->tarefas[i + 1] = lista->tarefas[alto];
    lista->tarefas[alto] = temp;
    (*trocas)++;  // Conta a troca

    return (i + 1);  // Retorna a posi��o do piv�
}

// Fun��o recursiva para o Quick Sort
void quickSortRecursivo(ListaTarefas* lista, int baixo, int alto, long* comparacoes, long* trocas) {
    if (baixo < alto) {
        // Divide a lista e ordena as duas partes
        int pi = particionar(lista, baixo, alto, comparacoes, trocas);
        quickSortRecursivo(lista, baixo, pi - 1, comparacoes, trocas);  // Ordena a parte esquerda
        quickSortRecursivo(lista, pi + 1, alto, comparacoes, trocas);  // Ordena a parte direita
    }
}

// Fun��o para ordenar a lista usando o Quick Sort
void quickSort(ListaTarefas* lista, long* comparacoes, long* trocas) {
    *comparacoes = 0;  // Inicializa o contador de compara��es
    *trocas = 0;  // Inicializa o contador de trocas
    quickSortRecursivo(lista, 0, lista->quantidade - 1, comparacoes, trocas);  // Chama a fun��o recursiva
}


// Fun��o para comparar o desempenho dos algoritmos de ordena��o
void compararAlgoritmosOrdenacao(ListaTarefas* lista) {
    ListaTarefas copia1, copia2, copia3;
    inicializarLista(&copia1, lista->capacidade);  // Cria uma c�pia da lista para o Bubble Sort
    inicializarLista(&copia2, lista->capacidade);  // Cria uma c�pia da lista para o Quick Sort
    inicializarLista(&copia3, lista->capacidade);  // Cria uma c�pia da lista para o Insertion Sort

    // Copia todos os elementos da lista original para as c�pias
    for (int i = 0; i < lista->quantidade; i++) {
        inserirNaLista(&copia1, lista->tarefas[i]);
        inserirNaLista(&copia2, lista->tarefas[i]);
        inserirNaLista(&copia3, lista->tarefas[i]);
    }

    clock_t inicio, fim;
    double tempo;
    long comparacoes, trocas;



    // Testa o Bubble Sort
    inicio = clock();  // Marca o in�cio do tempo
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

// Fun��o para ordenar as tarefas pela data, usando Quick Sort
void ordenarPorData(ListaTarefas* lista) {
    long comparacoes, trocas;
    quickSort(lista, &comparacoes, &trocas);  // Chama o Quick Sort
}

// Fun��o para coletar as tarefas da �rvore em ordem e armazen�-las na lista
void coletarTarefasEmOrdem(No* raiz, ListaTarefas* lista) {
    if (raiz == NULL) {
        return;  // Se a �rvore est� vazia ou chegou ao fim, n�o faz nada
    }

    // Percorre a sub�rvore esquerda
    coletarTarefasEmOrdem(raiz->esquerda, lista);

    // Insere a tarefa da raiz na lista
    inserirNaLista(lista, raiz->tarefa);

    // Percorre a sub�rvore direita
    coletarTarefasEmOrdem(raiz->direita, lista);
}
