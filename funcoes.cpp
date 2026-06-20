#include <cstdlib>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

namespace na{ //Esse é outro nome que será necessário mudar
template <typename T>
class funcoes{
private:
    struct node
    {
        T value;
        std::unordered_set<node*> links;
    };

    std::unordered_map<T, node> grafo;
    
    node *find(const T& val)
    {
        auto it = grafo.find(val);
        if (it == grafo.end()){
            return nullptr;
        }
        return &it->second;
    }

public:
    void insere_nodo(const T& val)
    {
        if(grafo.count(val) != 0)
            return;
        node aux;
        aux.value = val;
        grafo[val] = aux;
    }

    void insert_link(const T& from, const T& to)
    {
        auto pfrom = find(from);
        if (!pfrom)
            return;
        auto pto = find(to);
        if (!pto)
            return;

        pfrom->links.insert(pto);
    }

    void leitura(const std::string& filename)
    {
        using aresta = std::pair<std::string, std::string>; // chama uma aresta que recebe um par de strings

        std::ifstream arq(filename); //abre o arquivo passado
        std::unordered_set<std::string> total_vertices; //cria um set 
        std::set<aresta> arestas;

        std::string linha;
        std::getline(arq, linha); 

        while(std::getline(arq, linha)){
            if(linha.empty()) continue; 

            int contador_virgulas = 0;
            std::string endereco_hop_from = "";
            std::string endereco_hop_to = "";

            for(char c : linha){
                if(c == ','){
                    contador_virgulas++;
                    continue;
                }
                if (contador_virgulas == 4) {
                    endereco_hop_from += c;
                }
                else if (contador_virgulas == 5) {
                    endereco_hop_to += c; 
                }
                else if (contador_virgulas > 5) {
                    break; 
                }
            }

            if(!endereco_hop_from.empty() && !endereco_hop_to.empty()) {
                if(endereco_hop_to != "*") {
                    total_vertices.insert(endereco_hop_from);
                    total_vertices.insert(endereco_hop_to);

                    arestas.insert({endereco_hop_from, endereco_hop_to});
                }
            }
        }
        std::cout << "Vértices únicos (IPs): " << total_vertices.size() << " | Arestas: " << arestas.size() << "\n";

        std::ofstream txt("rede.txt");
        txt << total_vertices.size() << "\n";
        for(std::string s : total_vertices){
            txt << s << "\n";
        }
        for(const auto& a : arestas){
            txt << a.first << "\n" << a.second << "\n";
        }

        arq.close();
        txt.close();
    }

    void load(const std::string& filename)
    {
        std::ifstream in(filename);
        if(!in){
            return;
        }
        int n;
        in >> n;
        in.ignore();
        std::string line, line2;
        while (n--) {
            getline(in, line);
            insere_nodo(line);
        }
        while (getline(in, line) && getline(in, line2)) {
            insert_link(line, line2);
        }

        in.close();
    }

    bool verticeexiste(const T& ip){
        if(!find(ip)){
            return false;
        }
        return true;
    }

    std::vector<T> shortest_path(const T& inicio, const T& fim){
            std::vector<T> caminho;//vetor do caminho
            auto c = find(inicio);
            if (!c) return caminho;

            auto f = find(fim);
            if (!f) return caminho;

            std::queue<node *> q;//cria uma fila de ponteiro
            std::unordered_set<node *> enfileirados;//cria um unordere_set para os nodos já visitados
            std::unordered_map<node *, node *> origem;//unordered_map que registra de onde veio o nodo
            q.push(c);//adiciona o nodo na fila
            enfileirados.insert(c);//insere o nodo do unordered_set
            origem[c] = nullptr;//no unordered map define a origem como c e o antes dele null, já que ele é o ponto de partida
            bool found = false;//variavel booleana inicia com false
            while (!q.empty()){//enquanto a fila não estiver vazia
                auto atual = q.front();//variavel atual recebe o primeiro nodo inserido na fila
                q.pop();//exclui ele da fila
                if (atual == f){//compara se o atual é f que é a variavel que recebe o nodo final, se achou
                    found = true;//variavel booleana fica true
                    break;//sai do laço
                }
                for(auto adj : atual->links){//aqui percorremos as arestas da variavel atual, que enquanto a fila nao for vazia, vai se modificando
                    if (enfileirados.count(adj) == 0){//adiciona os vizinhos no unordered_set que verifica se o nodo já foi visitado
                        q.push(adj);
                        enfileirados.insert(adj);
                        origem[adj] = atual;//registra de onde esse nodo veio
                    }
                }
            }
            if (found){//se encontrou
                    auto p = f;
                    while (p){//volta do inicio ate o fim
                        caminho.push_back(p->value); //adiciona no vetor
                        p = origem[p];
                    }
                }
            std::reverse(caminho.begin(), caminho.end());//inverte o caminho
            return caminho;
        }

    void gerarDot(const std::vector<T>& caminho = {}) { //gera o .dot completo e o com caminho destacado
        bool temCaminho = !caminho.empty();//.empty retorna um booleano que inicia nesse caso com false

        std::ofstream dot("input.dot");//gera o .dot padronizado para o nome input.dot para ambos
        dot << "digraph{\n";

        std::set<std::pair<T,T>> arestas_caminho;//aqui vai criar um set que armazena os pares que tem arestas no caminho

        if (temCaminho) { //se tem caminho cria as ligações dos nos, as arestas
            for (size_t i = 0; i < caminho.size() - 1; i++) {
                arestas_caminho.insert({caminho[i], caminho[i+1]});
            }
        }

        for (const auto &[k, n] : grafo) {//percorre o grafo
            for (const auto &link : n.links) {//percorre as arestas

                if (temCaminho && arestas_caminho.count({k, link->value})) {//se existe caminho verifica se a aresta faz parte do caminho, se faz destaca
                    dot << "\"" << k << "\" -> \"" << link->value
                        << "\" [color=red, penwidth=3.0];\n";//aresta destacada de vermelho
                } else {
                    dot << "\"" << k << "\" -> \"" << link->value << "\";\n";//assim desenha normal sem destacar
                }
            }
        }

        if (temCaminho) {//se tem caminho
            for (const auto &ip : caminho) {//percorre os nos do grafo
                dot << "\"" << ip << "\" [color=black, penwidth=3.0, style=filled, fillcolor=palegreen];\n";//destaca eles
                if(ip == caminho[0]){
                    dot << "\"" << ip << "\" [color=black, penwidth=3.0, style=filled, fillcolor=palegreen3];\n";//destaca eles
                }
                if(ip == caminho.back()){
                    dot << "\"" << ip << "\" [color=black, penwidth=3.0, style=filled, fillcolor=tomato3];\n";//destaca eles
                }
            }
        }

        dot << "}\n";
        dot.close();//fecha grafo
    }

     int calculaDiametro(){
        int diametroMaximo = 0;//cria variavel global
        for(const auto& [ip, nodo] : grafo){//percorre os nodos do grafo
            int maiorDiametro = 0;//variavel para comparacao interna
            std::queue<std::pair <node *, int>> q;//lista de pares com nodo e distancia do nodo
            std::unordered_map<node*, bool> visitados;//unordered_map com visitados
            node* verifica = find(ip);//variavel que pega o find ip para uma variavel de nodo
            q.push({verifica, 0});//insere na lista o verifica, que é o nodo, e a distancia do nodo de origem
            visitados.insert({verifica, true});
            while (!q.empty()){//enquanto não estiver vazio
                auto atual = q.front().first;
                auto distanciaAtual = q.front().second;
                if(distanciaAtual > maiorDiametro){//comparacao
                    maiorDiametro = distanciaAtual;//atualiza variavel
                }
                q.pop();
                for(auto adj : atual->links){
                    if (visitados.count(adj) == 0){//mesma coisa de shortest path
                        q.push({adj, distanciaAtual + 1});//adicona distancia
                        visitados.insert({adj, true});
                    }
                }
            }
            if(maiorDiametro > diametroMaximo){//comparacao com variavel interna e externa
                diametroMaximo = maiorDiametro;
            }
        }
        return diametroMaximo;
    }

};
}