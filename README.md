# TAD Grafo (Graph Abstract Data Type)

Neste trabalho, construímos em Linguagem C um Tipo Abstrato de Dados (TAD) que representa um **Grafo Não-Direcionado**. A implementação utiliza uma **matriz de adjacência** para o armazenamento das relações entre os vértices, suportando arestas com peso.

## 🛠️ Estrutura do Projeto

O projeto está dividido nos seguintes arquivos principais:

* **`graph.h`**: Interface do TAD. Contém a definição das assinaturas das funções e abstrações do grafo.
* **`graph.c`**: Implementação das funções do TAD. O grafo é alocado dinamicamente com índices baseados em `1` até `N`. A ausência de arestas é representada pelo valor `-1`.
* **`main.c`**: Programa principal que atua como interface de linha de comando para testar as operações do grafo através de um menu de opções numéricas.
* **`main_runcodes.c`**: Versão unificada do código (cabeçalhos, implementação e `main` no mesmo arquivo), ideal para submissão em plataformas de correção automática (como o RunCodes).
* **`Makefile`**: Script de automação para compilação e execução do projeto[cite: 4].

## ⚙️ Funcionalidades Implementadas

A API do Grafo (`graph.h`) disponibiliza as seguintes operações principais:

* **`MyGraph(N)`**: Inicializa um grafo com `N` vértices e 0 arestas.
* **`add_edge(G, u, v, w)`**: Adiciona (ou atualiza) uma aresta entre os vértices `u` e `v` com o peso `w`.
* **`exist_edge(G, u, v)`**: Verifica a existência de uma aresta entre `u` e `v`.
* **`neighbors(G, u)`**: Retorna um vetor alocado dinamicamente com os vértices vizinhos de `u`, terminado com um sentinela `-1`.
* **`remove_edge(G, u, v)`**: Remove a aresta entre os vértices `u` e `v` (atribuindo o valor `-1` na matriz).
* **`print_info(G)`**: Imprime todos os vértices e as arestas presentes no grafo de forma formatada.
* **`remove_graph(&G)`**: Desaloca completamente a memória da matriz de adjacência e da estrutura do grafo.
* **`max_neighbors(G)`**: Retorna o vértice que possui o maior grau (maior número de vizinhos).
* **`adjacency_matrix(G)`**: Retorna um ponteiro para a matriz de adjacência interna do grafo.

## 🚀 Como Compilar e Executar

O projeto inclui um `Makefile` configurado para facilitar a compilação utilizando o padrão `c99` com os avisos (`-Wall`) ativados.

**Para compilar o projeto padrão:**
```bash
make all
```

**Para compilar com o Address Sanitizer (útil para detectar vazamentos de memória e erros de segmentação):**
```bash
make verifica
```

**Para executar o programa compilado:**
```bash
make run
```

**Para limpar os arquivos objetos e o executável:**
```bash
make clean
```

## 🎮 Como Usar (Interface de Linha de Comando)

A execução do programa (`main.c`) espera a leitura de inteiros representando a **opção** do menu, seguida pelos argumentos da respectiva operação. O laço de repetição é encerrado ao receber a opção `-1`.

| Opção | Ação | Entrada Esperada | Exemplo de Uso |
| :--- | :--- | :--- | :--- |
| **0** | Criar Grafo | `0 N` (Onde N é o número de vértices) | `0 5` |
| **1** | Adicionar Aresta | `1 u v w` (vértices u, v e peso w) | `1 2 3 10` |
| **2** | Verificar Aresta | `2 u v` (vértices u e v) | `2 2 3` |
| **3** | Imprimir Vizinhos | `3 u` (vértice u) | `3 2` |
| **4** | Remover Aresta | `4 u v` (vértices u e v) | `4 2 3` |
| **5** | Imprimir Matriz | `5` (Imprime a matriz de adjacência) | `5` |
| **6** | Vértice de Maior Grau | `6` (Retorna o vértice com mais conexões) | `6` |
| **-1** | Sair | `-1` | `-1` |

*Nota: Ao finalizar com `-1`, dependendo das opções chamadas anteriormente, o programa pode imprimir um resumo do grafo final (`print_info`) ou o último resultado armazenado de uma consulta simples.*

## 👥 Desenvolvedores

* 15512767 - José Fausto Vital Barbosa
* 16876293 - João Pedro Boaretto
* 16897421 - Philippe Sardenberg Castro Couto
* 16854281 - André Luiz Sousa Paião

## 📄 Licença

Este projeto está sob a Licença MIT.
O software é fornecido "no estado em que se encontra" (AS IS), sem garantia de qualquer tipo, expressa ou implícita. Em nenhuma circunstância os autores ou detentores de direitos autorais serão responsáveis por qualquer reclamação, danos ou outras responsabilidades.