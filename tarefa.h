#ifndef TAREFA_H
#define TAREFA_H

// Estrutura que representa uma tarefa
typedef struct Tarefa {
    int id;                 // Identificador �nico da tarefa
    char descricao[100];    // Descri��o da tarefa
    char prioridade[10];    // Prioridade da tarefa: Alta, M�dia, Baixa
    int dia, mes, ano;      // Data de cria��o da tarefa (dia, m�s, ano)
} Tarefa;

// Fun��o para inicializar uma tarefa
void inicializarTarefa(Tarefa* tarefa, int id, const char* descricao, const char* prioridade, int dia, int mes, int ano);

#endif // TAREFA_H
