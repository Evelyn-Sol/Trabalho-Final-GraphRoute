#include <iostream>
#include "funcoes.cpp" //Por favor, sugiram um nome melhor para o arquivo com as funções

using namespace std;

void selecaoFormato(na::funcoes<string> &tipo){
    int formato;
    cout << "Selecione o formato de saída do Graphviz:\n";
    cout << "1. Tela\n";
    cout << "2. Imagem (PNG)\n";
    cout << "3. Documento (PDF)\n";
    cout << "Opção: "; cin >> formato;
    
    switch (formato){
    case 1:
        tipo.show(); 
        break;
    case 2:
        /*Falta implementar o formato PNG*/
        break;
    case 3:
        /*E o PDF também*/
        break;
    default:
        cout << "Opção Inválida!\n";
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
        cout << "3. Calcular o Diâmetro do Grafo\n";
        cout << "4. Indentificar Roteadores Críticos\n";
        cout << "0. Sair\n";
        cout << "======================================================\n";
        cout << "Escolha uma opção: "; cin >> opcao;
    switch (opcao){
        case 0:
            return 0;
            break;
        case 1:
            selecaoFormato(rede);
            break;
        case 2:
            /*A implementar*/
            break;
        case 3:
            /*A implementar*/
            break;
        case 4:
            /*A implementar*/
            break;
        
        default:
            cout << "Opção Inválida! Tente Novamente.\n";
            break;
        }
    }
}
