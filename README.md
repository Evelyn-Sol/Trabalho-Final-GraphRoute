# Analisador de Rotas de Rede com Grafos

### Integrantes:
Évelyn Marques Soletti (206891@upf.br)  
João Paulo da Silva Franceschi (188358@upf.br)  
Matheus Dos Santos Savegnago (198879@upf.br)  

## Sobre a aplicação:
Foi desenvolvido uma aplicação que lê um arquivo de redes .log de rotas em formato de grafo direcionado de IPs, armazena os nodos e arestas em uma lista de adjacência e transforma-os em uma estrutura de grafo na memória, utilizando de hashmap. Cada um dos vértices são armazenados em um unordered_map, e as ligações de cada nó ficam guardadas em um unordered_set de ponteiros. Isso acelera o processo de busca de nós e evita a duplicidade de arestas. O programa possui os seguintes comandos:

### 1. Exibir Grafo Completo: Contém um algoritmo para exibir o grafo em uma tela local, usando o aplicativo graphviz, em formato PNG e PDF.

### 2. Encontrar Menor Caminho: Possui também um algoritmo que encontra o menor caminho entre dois nodos determinados, usando de uma BFS(breadth-first search) que realiza uma busca de camada por camada no grafo, ideal para grafos lineares não ponderados, implementada com uma fila para receber os nodos que serão percorridos, um unordered_set para os nodos já visitados e um unordered_map que registra a origem do nodo.
Tem a mesma opção de exibição do primeiro comando, permitindo escolher entre tela, PNG e PDF.

### 3. Calcular o Diâmetro do Grafo: Também realizará uma busca em largura(BFS) a partir de cada um dos vértices, irá medir a maior distância encontrada em cada varredura e retornará o maior valor global.

### 4. Identificar Roteadores Críticos: Com um unordered_map para determinar o valor das entradas de cada nodo e um vetor de pares para determinar a sua posição no ranking, esse comando irá mostrar os nodos que mais aparecem como destino de uma aresta e exibirá os 5 maiores em ordem decrescente.

## Instruções de compilação e execução:

Para a compilação e execução do programa, antes, será necessário o G++ com suporte a C++17, para sua instalação, execute no terminal:

`sudo apt update && sudo apt install g++`

### Detalhe importante sobre o arquivo .log:
Sobre esse arquivo que será lido na execução do programa, é OBRIGATÓRIO que esteja escrito no cabeçalho do arquivo a seguinte estrutura:
prb_id,probe_src,dst_addr,hop,hop_from,hop_to,rtt

Isso será necessário para a leitura e interpretação correta dos dados recebidos do arquivo

E para a visualização em tela do grafo, será necessário o aplicativo graphviz, que possui compatibilidade com arquivos do tipo .dot, para instalar, execute no terminal:

## Partições derivadas do Debian ou Ubuntu:
sudo apt install graphviz

Fedora, Rocky Linux, RedHat ou CentOS
sudo dnf install graphviz

Com as ferramentas instaladas, partimos para a etapa da compilação do programa, para isso, com um terminal aberto, acesse a pasta onde o programa está e compile com:

g++ menu.cpp -o menu -Wall

Agora para a execução, com o .log localizado e o arquivo “funcoes.cpp” na mesma pasta, digite no terminal:

./menu "nome do arquivo .log"

## Exemplo de Execução:
``` txt
$ ./menu input_1.log  
Grafo de roteamento inicializado!  
Vértices únicos (IPs): 342 | Arestas: 812  
======================================================  
1. Exibir Grafo Completo  
2. Encontrar Menor Caminho  
3. Calcular o Diâmetro do Grafo  
4. Identificar Roteadores Críticos  
0. Sair  
======================================================  
Escolha uma opção: 2  
Digite o IP de Origem: 82.66.191.65  
Digite o IP de Destino: 194.149.162.250  
Caminho encontrado (3 saltos):  
82.66.191.65 -> 192.168.3.1 -> 194.149.162.248 -> 194.149.162.250  
Selecione o formato de saída do Graphviz:  
1. Tela  
2. Imagem (PNG)  
3. Documento (PDF)  
Opção: 2  
Arquivo input_1.log.png gerado com sucesso  
```
