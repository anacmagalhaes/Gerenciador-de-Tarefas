
# 📋 Gerenciador de Tarefas – Estruturas de Dados em C

Este projeto é um gerenciador de tarefas desenvolvido em linguagem C, como parte de um trabalho acadêmico voltado ao uso de **estruturas de dados**. Ele implementa funcionalidades de organização, pesquisa e manipulação de tarefas utilizando **pilhas**, **filas com prioridade**, **árvores AVL** e **algoritmos de ordenação**.

🧩 **Status**: Trabalho concluído ✅

## 🚀 Tecnologias e recursos utilizados

- Linguagem C (padrão ANSI C)
- Compilador Code::Blocks (.cbp incluso)
- Estruturas de dados:
  - Árvore AVL
  - Fila com prioridade
  - Pilha
  - Algoritmos de ordenação
  - Pesquisa sequencial e binária

## 🛠️ Funcionalidades

- Inserção, exclusão e listagem de tarefas
- Ordenação de tarefas por prioridade, data, ou outros critérios
- Armazenamento em árvore AVL para balanceamento de dados
- Fila com prioridade para execução ordenada
- Pilha para desfazer operações
- Pesquisas com algoritmos eficientes

## 📂 Estrutura do projeto

```
📁 /vscode                 # Configurações do editor (opcional)
📁 /bin/Debug              # Saída do build
📁 /obj/Debug              # Objetos compilados

📄 arvore_avl.c / .h       # Implementação da árvore AVL
📄 fila_com_prioridade.c/h # Fila com prioridade
📄 pilha.c / .h            # Pilha de tarefas
📄 ordenacao.c / .h        # Funções de ordenação
📄 pesquisa.c / .h         # Algoritmos de busca
📄 tarefa.c / .h           # Definição e operações sobre tarefas
📄 main.c                  # Função principal (menu/interação)
📄 gerenciador_de_tarefas.cbp # Projeto Code::Blocks
```

## ✅ Como executar

### Requisitos

- Um compilador C (GCC, TDM-GCC, etc)
- [Code::Blocks](http://www.codeblocks.org/) (opcional, para abrir o projeto `.cbp`)
- Terminal (Linux/Windows)

### Compilação via terminal (Linux)

```bash
gcc main.c arvore_avl.c fila_com_prioridade.c pilha.c ordenacao.c pesquisa.c tarefa.c -o gerenciador
./gerenciador
```

Ou abra o arquivo `gerenciador_de_tarefas.cbp` diretamente no Code::Blocks e compile.

## 👨‍🏫 Projeto acadêmico

Este projeto foi desenvolvido com fins educacionais, aplicando conceitos fundamentais de estrutura de dados em C.

---

📁 Desenvolvido por: Ana Carolina Soares Magalhães
