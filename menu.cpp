#include <iostream>
#include <fstream>
#include "funcoes.cpp"

using namespace std;

void selecaoFormato(const std::string &tipo, const std::string &nomearquivo){
    int formato;
    cout << "Selecione o formato de saida do Graphviz:\n";
    cout << "1. Tela\n";
    cout << "2. Imagem (PNG)\n";
    cout << "3. Documento (PDF)\n";
    cout << "Opcao: "; cin >> formato;

    std::string nomedoarquivo = nomearquivo;
    
    switch (formato){
    case 1:
        system(("dot -Tx11 " + tipo).c_str());
        break;
    case 2:
        system(("dot -Tpng " + tipo + " -o " + nomearquivo + ".png").c_str());
        cout << "Arquivo " << nomearquivo << ".png gerado com sucesso!\n";
        break;
    case 3:
        system(("dot -Tpdf " + tipo + " -o " + nomearquivo + ".pdf").c_str());
        cout << "Arquivo " << nomearquivo << ".pdf gerado com sucesso!\n";
        break;
    default:
        cout << "Opcao Invalida!\n";
        break;
    }
}

int main(int argc, char* argv[]){
    if(argc < 2) {
        cout << "Erro: nome do arquivo não recebido\n";
        return 1; 
    }

    string nome_arquivo = argv[1];
    ifstream arq(nome_arquivo.c_str());
    if(!arq){
        cout << "Erro: nao foi possivel abrir o arquivo\n"; 
        return 1;
    }

    cout << "Grafo de roteamento inicializado!\n";
    
    na::funcoes<string> rede;
    rede.leitura(nome_arquivo);
    rede.load("rede.txt");

    int opcao;

    while(true){
        cout << "======================================================\n";
        cout << "1. Exibir Grafo Completo\n";
        cout << "2. Encontrar Menor Caminho\n";
        cout << "3. Calcular o Diametro do Grafo\n";
        cout << "4. Indentificar Roteadores Críticos\n";
        cout << "0. Sair\n";
        cout << "======================================================\n";
        cout << "Escolha uma opcao: "; cin >> opcao;
    switch (opcao){
        case 0:
            return 0;
            break;
        case 1:
            rede.gerarDot();
            selecaoFormato("input.dot", nome_arquivo);
            break;
        case 2:{
            string origem;//cria string que vai receber o ip de origem
            string destino;//ip de destino
            cout << "Digite o IP de origem\n";
            cin >> origem;
            if(!rede.verticeexiste(origem)){//verifica se o ip de origem existe
                cout << "IP de origem nao encontrado\n";
                break;
            }
            cout << "Digite o IP de destino\n";
            cin >> destino;
            if(!rede.verticeexiste(destino)){//verifica se o ip de destino existe
                cout << "IP de destino nao encontrado\n";
                break;
            }
            vector<string> resultado = rede.shortest_path(origem, destino);//armazena na variavel resultado o shortest_path
            if(resultado.empty()){
                cout << "Nao existe caminho entre os nós\n";
                break;
            }
            else{
                cout << "Caminho encontrado (Saltos: " << resultado.size() - 1 << ")\n";//conta quantos saltos deu de um ip ate o destino
                for(size_t i = 0; i < resultado.size(); i++){//imprime o resultado
                    cout << resultado[i];
                    if(i != resultado.size()-1){
                        cout << " -> ";
                    }
                    if(i == resultado.size()-1){
                        cout << "\n";
                    }
                }
                rede.gerarDot(resultado);//chama a funcao gerar dot que cria o .dot do caminho
                selecaoFormato("input.dot", nome_arquivo);//chama a função selecao formato para escolher o formato de saida do arquivo
                break;
            }
        }
        case 3:
            cout << "O diametro do grafo e: " << rede.calculaDiametro() << " saltos.\n";
            break;
        case 4:
            cout << "TOP 5 Roteadores Criticos\n";
            rede.identificadorRoteadoresCriticos();
            break;
        
        default:
            cout << "Opção Invalida! Tente Novamente.\n";
            break;
        }
    }
}
