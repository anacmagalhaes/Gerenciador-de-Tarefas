#ifndef TAREFA_H
#define TAREFA_H

// Estrutura que representa uma tarefa
typedef struct Tarefa {
    int id;                 // Identificador único da tarefa
    char descricao[100];    // Descrição da tarefa
    char prioridade[10];    // Prioridade da tarefa: Alta, Média, Baixa
    int dia, mes, ano;      // Data de criação da tarefa (dia, mês, ano)
} Tarefa;

// Função para inicializar uma tarefa
void inicializarTarefa(Tarefa* tarefa, int id, const char* descricao, const char* prioridade, int dia, int mes, int ano);

#endif // TAREFA_H
