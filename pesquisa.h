#ifndef PESQUISA_H
#define PESQUISA_H

#include "tarefa.h"      // Inclus�o do arquivo que define a estrutura Tarefa
#include "ordenacao.h"   // Inclus�o do arquivo que define a estrutura ListaTarefas

// Fun��es para pesquisa de tarefas
int estaOrdenadaPorId(Tarefa* lista, int tamanho);                  // Verifica se a lista est� ordenada por ID
int buscaBinaria(Tarefa* lista, int tamanho, int idBuscado);       // Realiza busca bin�ria por ID
int buscaLinear(Tarefa* lista, int tamanho, int idBuscado);        // Realiza busca linear por ID
Tarefa* buscarTarefa(ListaTarefas* lista, int idBuscado);          // Busca uma tarefa por ID

#endif
