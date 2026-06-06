#include <cstdlib>
#include <bits/stdc++.h>

namespace na{ //Esse é outro nome que será necessário mudar
template <typename T>
class funcoes{
private:
    struct node{
        T value;
        std::unordered_set<node *> links;
    };
    std::unordered_map<T, node> grafo;
    
    node *find(const T &val){
        auto it = grafo.find(val);
        if (it == grafo.end()){
            return nullptr;
        }
        return &it->second;
    }
public:

    void insere_nodo(const T &val){
        if (grafo.count(val) != 0)
            return;
        node aux;
        aux.value = val;
        grafo[val] = aux;
    }

    void load(const std::string &filename){
        std::ifstream arq(filename);
        if(!arq) return;

        arq.close();
    }

    void show()
        {
            std::ofstream dot("/tmp/nahuy.dot");
            dot << "digraph{\n";
            for (const auto &[k, n] : grafo)
            {
                dot << "\t\"" << k << "\" -> {";
                for (const auto &link : n.links)
                {
                    dot << "\"" << link->value << "\" ";
                }
                dot << " };\n";
            }
            dot << "}\n";
            dot.close();
            system("dot -Tx11 /tmp/nahuy.dot");
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