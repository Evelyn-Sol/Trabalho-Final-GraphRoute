#include <cstdlib>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <vector>

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
        struct aresta{
            std::string origem;
            std::string destino;
        };

        std::ifstream arq(filename);
        std::unordered_set<std::string> total_vertices;
        std::vector<aresta> arestas;
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
                    arestas.push_back({endereco_hop_from, endereco_hop_to});
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
            txt << a.origem << "\n" << a.destino << "\n";
        }

        arq.close();
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

    void show()
    {
        std::ofstream dot("nahuy.dot");
        dot << "digraph{\n";
        for (const auto &[k, n] : grafo){
            dot << "\t\"" << k << "\" -> {";
            for (const auto &link : n.links){
                dot << "\"" << link->value << "\" ";
            }
            dot << " };\n";
        }
        dot << "}\n";
        dot.close();

        system("dot -Tpng nahuy.dot -o grafo.png"); // comandos do windows
        system("start grafo.png");

        //system("dot -Tx11 nahuy.dot"); // comando linux
    }

    /*std::vector<node *> shortest_path(const T& inicio, const T& fim){
            std::vector<node *> caminho;
            auto c = find(inicio);
            if (!c) return caminho;

            auto f = find(fim);
            if (!f) return caminho;

            std::queue<node *> q;
            std::unordered_set<node *> enfileirados;
            std::unordered_map<node *, node *> origem;
            q.push(c);
            enfileirados.insert(c);
            origem[c] = nullptr;
            bool found = false;
            while (!q.empty()){
                auto atual = q.front();
                q.pop();
                if (atual == f){
                    found = true;
                    break;
                }
                for(auto adj : atual->links){
                    if (enfileirados.count(adj) == 0)
                        q.push(adj);
                        enfileirados.insert(adj);
                        origem[adj] = atual;
                }
                if (found){
                    auto p = f;
                    while (p){
                        caminho.push_back(p);
                        std::cout << p->value << " ";
                        p = origem[p];
                    }
                std::cout << "\n";
                }
            }
            std::reverse(caminho.begin(), caminho.end());
            return caminho;
        }*/
    };
}