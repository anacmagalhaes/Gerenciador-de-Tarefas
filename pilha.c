#include "pilha.h"
#include <stdio.h>
#include "tarefa.h"

// Função para inicializar a pilha
void inicializarPilha(Pilha* pilha) {
    pilha->topo = -1;  // A pilha começa vazia, então o topo é -1
}

// Função para verificar se a pilha está vazia
int pilhaVazia(Pilha* pilha) {
    return pilha->topo == -1;  // Retorna 1 (verdadeiro) se o topo for -1, ou seja, pilha vazia
}

// Função para verificar se a pilha está cheia
int pilhaCheia(Pilha* pilha) {
    return pilha->topo == MAX_PILHA - 1;  // Retorna 1 (verdadeiro) se o topo atingir o limite máximo
}

// Função para empilhar uma tarefa (adicionar no topo da pilha)
void empilhar(Pilha* pilha, Tarefa tarefa) {
    if (!pilhaCheia(pilha)) {  // Se a pilha não estiver cheia
        pilha->topo++;  // Aumenta o topo
        pilha->itens[pilha->topo] = tarefa;  // Adiciona a tarefa no topo da pilha
    } else {
        printf("Pilha cheia! Nao e possivel armazenar mais historico.\n");  // Exibe erro se a pilha estiver cheia
    }
}

// Função para desempilhar uma tarefa (remover do topo da pilha)
Tarefa desempilhar(Pilha* pilha) {
    Tarefa tarefaVazia = {0, "", "", 0, 0, 0};  // Cria uma tarefa vazia para retornar em caso de erro

    if (!pilhaVazia(pilha)) {  // Se a pilha não estiver vazia
        Tarefa tarefa = pilha->itens[pilha->topo];  // Pega a tarefa no topo
        pilha->topo--;  // Diminui o topo, removendo a tarefa
        return tarefa;  // Retorna a tarefa removida
    }

    printf("Pilha vazia! Nao ha tarefas para desempilhar.\n");  // Exibe erro se a pilha estiver vazia
    return tarefaVazia;  // Retorna uma tarefa vazia
}

// Função para exibir o histórico de tarefas removidas da pilha
void exibirHistorico(Pilha* pilha) {
    if (pilhaVazia(pilha)) {  // Se a pilha estiver vazia
        printf("Historico vazio!\n");  // Exibe que o histórico está vazio
        return;
    }

    // Exibe o histórico de tarefas removidas (do mais recente para o mais antigo)
    printf("\nHistorico de tarefas removidas (do mais recente ao mais antigo):\n");
    for (int i = pilha->topo; i >= 0; i--) {  // Percorre a pilha do topo para baixo
        printf("\nTarefa %d:\n", pilha->topo - i + 1);  // Exibe o número da tarefa
        printf("ID: %d\n", pilha->itens[i].id);  // Exibe o ID da tarefa
        printf("Descricao: %s\n", pilha->itens[i].descricao);  // Exibe a descrição da tarefa
        printf("Prioridade: %s\n", pilha->itens[i].prioridade);  // Exibe a prioridade da tarefa
        printf("Data: %02d/%02d/%04d\n",
               pilha->itens[i].dia,
               pilha->itens[i].mes,
               pilha->itens[i].ano);  // Exibe a data da tarefa
        printf("-----------------------\n");
    }
}


