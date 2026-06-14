#include <iostream>
#include "funcoes.cpp" //Por favor, sugiram um nome melhor para o arquivo com as funções
#include <bits/stdio.h> //Se quiserem tirar esse daqui, à vontade, mas se fizerem isso, vcs vão ter q adicionar as
                        // bibliotecas manualente
using namespace std;

void selecaoFormato(na::funcoes<int> &tipo){
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
    if (argc < 2){
        std::cerr << "Deve-se inserir o executável e o arquivo de entrada da seguinte forma: \"" << argv[0] << "\" \"arquivo\"\n"; 
        return 1;
    }

    std::ifstream file(argv[1]);

    if(file){
        std::cout << "Grafo de roteamento inicializado!\n";
        std::cout << "Vértices únicos (IPs):  | Arestas: \n";
    } else {
        std::cerr << "Não foi possível abrir o arquivo!\n"; //Tratamento de erro
        return 0;
    }

    int opcao;
    na::funcoes<int> m;

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
        selecaoFormato(m);
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
    }
    }
}
