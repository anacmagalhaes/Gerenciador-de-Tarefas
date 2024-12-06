#include "tarefa.h"
#include <string.h>

// Fun��o para inicializar uma tarefa
void inicializarTarefa(Tarefa* tarefa, int id, const char* descricao, const char* prioridade, int dia, int mes, int ano) {
    // Atribui o ID da tarefa
    tarefa->id = id;

    // Copia a descri��o da tarefa, garantindo que n�o ultrapasse o tamanho do buffer
    strncpy(tarefa->descricao, descricao, sizeof(tarefa->descricao) - 1);
    tarefa->descricao[sizeof(tarefa->descricao) - 1] = '\0';  // Garante que a string seja nula-terminada

    // Copia a prioridade da tarefa, garantindo que n�o ultrapasse o tamanho do buffer
    strncpy(tarefa->prioridade, prioridade, sizeof(tarefa->prioridade) - 1);
    tarefa->prioridade[sizeof(tarefa->prioridade) - 1] = '\0';  // Garante que a string seja nula-terminada

    // Atribui a data de cria��o da tarefa
    tarefa->dia = dia;
    tarefa->mes = mes;
    tarefa->ano = ano;
}
