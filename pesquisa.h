#ifndef PESQUISA_H
#define PESQUISA_H

#include "tarefa.h"      // Inclusão do arquivo que define a estrutura Tarefa
#include "ordenacao.h"   // Inclusão do arquivo que define a estrutura ListaTarefas

// Funções para pesquisa de tarefas
int estaOrdenadaPorId(Tarefa* lista, int tamanho);                  // Verifica se a lista está ordenada por ID
int buscaBinaria(Tarefa* lista, int tamanho, int idBuscado);       // Realiza busca binária por ID
int buscaLinear(Tarefa* lista, int tamanho, int idBuscado);        // Realiza busca linear por ID
Tarefa* buscarTarefa(ListaTarefas* lista, int idBuscado);          // Busca uma tarefa por ID

#endif
