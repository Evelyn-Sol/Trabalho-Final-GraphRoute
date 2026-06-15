#include <iostream>
#include "funcoes.cpp" //Por favor, sugiram um nome melhor para o arquivo com as funções

using namespace std;

void selecaoFormato(const std::string &tipo){
    int formato;
    cout << "Selecione o formato de saida do Graphviz:\n";
    cout << "1. Tela\n";
    cout << "2. Imagem (PNG)\n";
    cout << "3. Documento (PDF)\n";
    cout << "Opção: "; cin >> formato;
    
    switch (formato){
    case 1:
        system(("dot -Tpng " + tipo + " -o grafo.png").c_str()); // comandos do windows
        system("start grafo.png");
        break;
    case 2:
        system(("dot -Tpng " + tipo + " -o saida.png").c_str());
        system("start saida.png");
        break;
    case 3:
        system(("dot -Tpdf " + tipo + " -o saida.pdf").c_str());
        system("start saida.pdf");
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

    string nome_arquivo;
    ifstream arq(nome_arquivo = argv[1]);
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
            selecaoFormato("input.dot");
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
            auto resultado = rede.shortest_path(origem, destino);//armazena na variavel resultado o shortest_path
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
                selecaoFormato("input.dot");//chama a função selecao formato para escolher o formato de saida do arquivo
                break;
            }
        }
        case 3:
            /*A implementar*/
            break;
        case 4:
            /*A implementar*/
            break;
        
        default:
            cout << "Opção Invalida! Tente Novamente.\n";
            break;
        }
    }
}
