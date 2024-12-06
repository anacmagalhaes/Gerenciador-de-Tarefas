#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

// Arquivos
#include "tarefa.h"
#include "arvore_avl.h"
#include "pilha.h"
#include "ordenacao.h"

// Definição máximo de tarefas e pilhas
#define MAX_TAREFAS 100
#define MAX_PILHA 100

// Função para ler uma nova tarefa
void lerTarefaDoUsuario(Tarefa* tarefa)
{
    printf("Digite o ID da tarefa: ");
    if (scanf("%d", &tarefa->id) != 1)
    {
        printf("Erro ao ler o ID da tarefa.\n");
        return;
    }

    while (getchar() != '\n'); // Limpar o buffer de entrada

    printf("Digite a descricao da tarefa: ");
    if (fgets(tarefa->descricao, sizeof(tarefa->descricao), stdin) == NULL)
    {
        printf("Erro ao ler a descrição da tarefa.\n");
        return;
    }
    tarefa->descricao[strcspn(tarefa->descricao, "\n")] = '\0'; // Remove o '\n'

    printf("Digite a prioridade (Alta, Media, Baixa): ");
    if (fgets(tarefa->prioridade, sizeof(tarefa->prioridade), stdin) == NULL)
    {
        printf("Erro ao ler a prioridade.\n");
        return;
    }
    tarefa->prioridade[strcspn(tarefa->prioridade, "\n")] = '\0'; // Remove o '\n'

    printf("Digite a data de criacao (dia/mes/ano): ");
    if (scanf("%d/%d/%d", &tarefa->dia, &tarefa->mes, &tarefa->ano) != 3)
    {
        printf("Erro ao ler a data.\n");
        return;
    }
    while (getchar() != '\n'); // Limpar o buffer de entrada
}

int main()
{
    // Inicializa a árvore de tarefas e a pilha para o histórico
    No* raiz = NULL;
    Pilha pilha;
    inicializarPilha(&pilha);

    // Variáveis de controle
    int opcao;
    Tarefa tarefa;
    int id;

    // Loop principal do menu
    while (1)
    {
        // Exibe o menu de opções
        printf("\n Menu de Opcoes: \n");
        printf("1. Inserir tarefa\n");
        printf("2. Buscar tarefa\n");
        printf("3. Pesquisar tarefa por busca binaria\n");
        printf("4. Pesquisar tarefa por busca linear\n");
        printf("5. Imprimir tarefas ordenadas pelo ID\n");
        printf("6. Imprimir tarefas ordenadas por data de criacao\n");
        printf("8. Remover tarefas\n");
        printf("9. Historico de tarefas removidas\n");
        printf("10. Desfazer remocao\n");
        printf("11. Sair\n\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1)
        {
            printf("Entrada invalida! Tente novamente.\n");
            while (getchar() != '\n'); // Limpa o buffer de entrada
            continue;
        }

        while (getchar() != '\n'); // Limpa o buffer após ler a opção

        switch (opcao)
        {
        case 1:
            lerTarefaDoUsuario(&tarefa);
            raiz = inserir(raiz, tarefa);
            break;

        case 2:
            printf("Digite o ID da tarefa que deseja buscar: ");
            if (scanf("%d", &id) != 1)
            {
                printf("Entrada invalida! Tente novamente.\n");
                continue;
            }
            buscarNo(raiz, id);
            break;

        case 3:
        case 4: {
            printf("Digite o ID da tarefa a ser pesquisada: ");
            if (scanf("%d", &id) != 1)
            {
                printf("Entrada inválida para ID.\n");
                while (getchar() != '\n');
                continue;
            }
            while (getchar() != '\n');

            ListaTarefas lista;
            inicializarLista(&lista, 100);
            coletarTarefasEmOrdem(raiz, &lista);

            clock_t inicio, fim;
            double tempo;
            int indice = -1;

            if (opcao == 3)
            {
                inicio = clock();
                indice = buscaBinaria(lista.tarefas, lista.quantidade, id);
                fim = clock();
            }
            else
            {
                inicio = clock();
                indice = buscaLinear(lista.tarefas, lista.quantidade, id);
                fim = clock();
            }

            tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
            printf("Tempo de busca: %.4f segundos\n", tempo);

            if (indice != -1)
            {
                printf("\nDetalhes da tarefa encontrada:\n");
                printf("ID: %d\n", lista.tarefas[indice].id);
                printf("Descrição: %s\n", lista.tarefas[indice].descricao);
                printf("Prioridade: %s\n", lista.tarefas[indice].prioridade);
                printf("Data: %02d/%02d/%04d\n",
                       lista.tarefas[indice].dia,
                       lista.tarefas[indice].mes,
                       lista.tarefas[indice].ano);
            }
            else
            {
                printf("Tarefa não encontrada.\n");
            }

            liberarLista(&lista);
            break;
        }

        case 5:
            printf("Imprimindo todas as tarefas por ordem de ID:\n");
            imprimirEmOrdem(raiz);
            break;

        case 6: {
            ListaTarefas listaParaOrdenacao;
            inicializarLista(&listaParaOrdenacao, 100);
            coletarTarefasEmOrdem(raiz, &listaParaOrdenacao);

            printf("Imprimindo todas as tarefas por ordem de data de criação:\n");
            ordenarPorData(&listaParaOrdenacao);
            for (int i = 0; i < listaParaOrdenacao.quantidade; i++)
            {
                printf("\nTarefa %d:\n", i + 1);
                printf("ID: %d\n", listaParaOrdenacao.tarefas[i].id);
                printf("Descrição: %s\n", listaParaOrdenacao.tarefas[i].descricao);
                printf("Prioridade: %s\n", listaParaOrdenacao.tarefas[i].prioridade);
                printf("Data: %02d/%02d/%04d\n",
                       listaParaOrdenacao.tarefas[i].dia,
                       listaParaOrdenacao.tarefas[i].mes,
                       listaParaOrdenacao.tarefas[i].ano);
                printf("-----------------------\n");
            }
            liberarLista(&listaParaOrdenacao);
            break;
        }

        case 8:
            printf("Digite o ID da tarefa que deseja remover: ");
            if (scanf("%d", &id) != 1)
            {
                printf("Entrada inválida!\n");
                continue;
            }
            raiz = removerNo(raiz, id, &pilha);
            break;

        case 9:
            printf("Histórico de tarefas removidas: \n");
            exibirHistorico(&pilha);
            break;

        case 10:
            desfazerRemocao(&pilha, &raiz);
            break;

        case 11:
            printf("Saindo...\n");
            exit(0);

        default:
            printf("Opção inválida! Tente novamente.\n");
            break;
        }
    }
}
