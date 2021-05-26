#include <iostream>
#include <graphviewer.h>
#include "Car.h"
#include "Client.h"
#include "Store.h"
#include "Request.h"
#include "Company.h"
#include "Graph.h"
#include "Time.h"


#include "utils.h"
#include "Algorithms.h"

bool bidirectional_edges;
Graph<int> graph;
Company<int> company("E-stafetas");




// Função que permite perguntar ao utilizador se deseja terminar o programa e obtém a sua resposta
char Sair_Programa()
{
    char sair;
    cout << "\nSair do Programa? (S/N)\n\n";
    do{
        cout << "R: ";
        cin >> sair;
    } while(sair != 'N' && sair != 'n' && sair != 'S' && sair != 's');
    return sair;
}

// Menu que trata da análise da conetividade do grafo
template <class T>
void Menu_Conetividade() {

    cout << "\n\n\t\t     Menu da Conetividade do Grafo \n\n";
    cout<<"\nTesting Connectivity..."<<endl;
    Vertex<T>* begin = graph.findVertex(company.getParque());
    vector<Vertex<T>*> vec = Avaliar_Conetividade<T>(begin);    // Devolve parte fortemente conexa do grafo a partir da parque

    if(vec.size()==graph.getVertexSet().size()){
        cout<<"Grafo fortemente conexo!"<<endl;
    }
    else{
        cout<<"Grafo nao e fortemente conexo!"<<endl;
    }
    vector<T> vec_aux;
    for(Vertex<T>* v: vec){
        vec_aux.push_back(v->getInfo());
    }
    showConnection<T>(vec_aux);

    char sair = Sair_Programa();
    if (sair == 'N' || sair == 'n')
        Menu_Principal();
}

// Menu que trata da visualização do grafo que contém todos os dados da empresa (clientes, lojas e carros)
void Menu_Visualizacao() {

    cout << "\n\n\t\t     Menu de Visualizacao do Mapa \n\n";
    cout << "Abrindo Mapa..." << endl;
    cout << "\n Cores: " << endl << endl;
    cout << "Laranja - Parque" << endl;
    cout << "Amarelo - Carros" << endl;
    cout << "Verde - Clientes" << endl;
    cout << "Vermelho - Lojas" << endl;
    Visualizar_Mapa();
    char sair = Sair_Programa();
    if (sair == 'N' || sair == 'n')
        Menu_Principal();
}

// Menu que trata da visualização dos clientes da empresa
template <class T>
void Visualizar_Clientes() {


    cout << "\n\n\t\t     Menu de Visualizacao de Clientes \n\n";
    int i = 0;
    for (Client<T>* cliente : company.getClients()) {
        cout << "Nome: " << cliente->getName() << endl;
        cout << "Morada: " << cliente->getNodeID() << endl;
        if (i != company.getNumClients() - 1)
            cout << "----------" << endl;
        i++;
    }
    char sair = Sair_Programa();
    if (sair == 'N' || sair == 'n')
        Menu_Principal();
}

// Menu que trata da visualização dos restaurantes da empresa
template <class T>
void Visualizar_Lojas() {

    cout << "\n\n\t\t     Menu de Visualizacao de Lojas \n\n";
    int i = 0;
    for (Store<T>* loja : company.getStores()) {
        cout << "Nome: " << loja->getName() << endl;
        cout << "Morada: " << loja->getNodeID() << endl;
        if (i != company.getNumStores() - 1)
            cout << "----------" << endl;
        i++;
    }
    char sair = Sair_Programa();
    if (sair == 'N' || sair == 'n')
        Menu_Principal();
}

// Menu que trata da visualização dos  da empresa
template <class T>
void Visualizar_Carros() {

    cout << "\n\n\t\t     Menu de Visualizacao de Carros \n\n";
    int i = 0;
    for (Car<T>* car : company.getCars()) {
        cout << "Nome: " << car->getName() << endl;
        cout << "Morada: " << car->getPosition() << endl;
        cout << "Bateria: " << car->getBattery() << endl;
        if (i != company.getNumCars() - 1)
            cout << "----------" << endl;
        i++;
    }
    char sair = Sair_Programa();
    if (sair == 'N' || sair == 'n')
        Menu_Principal();
}


// Menu que trata da visualização dos dados da empresa (clientes, lojas e carros)
void Menu_Visualizar_Dados() {

    cout << "\n\n\t\t     Menu de Visualizacao de Dados \n\n";
    cout << "[1] Visualizar Clientes\n";
    cout << "[2] Visualizar Lojas\n";
    cout << "[3] Visualizar Carros\n";
    cout << "[4] Voltar ao Menu Principal \n";
    cout << "\nOpcao: ";

    string name;
    cin >> name;
    char opcao;
    if(name.size() == 1) opcao = name[0];
    else opcao = '9';

    switch(opcao)
    {
        case '1':
            Visualizar_Clientes<int>(); break;
        case '2':
            Visualizar_Lojas<int>(); break;
        case '3':
            Visualizar_Carros<int>(); break;
        case '4':
            Menu_Principal(); break;
        default:
            Menu_Visualizar_Dados(); break;
    }
    char sair = Sair_Programa();
    if (sair == 'N' || sair == 'n')
        Menu_Principal();
}


// Função que trata da visualização do Menu Principal
void Menu_Principal()
{

    cout << "\n\n\t\t     Menu Principal \n\n";
    cout << "[1] Avaliar Conetividade do grafo \n";
    cout << "\n\t Visualizacao: \n\n";
    cout << "[2] Visualizar o mapa recorrendo ao GraphViewer \n";
    cout << "[3] Visualizar Dados \n";
    cout << "\n\t Pedidos: \n\n";
    cout << "[4] Atendimento de Pedidos \n";
    cout << "[0] Sair do Programa \n";
    cout << "\nOpcao: ";

    string name;
    cin >> name;
    char opcao;
    if(name.size() == 1) opcao = name[0];
    else opcao = '9';

    switch(opcao)
    {
        case '1':
            Menu_Conetividade<int>(); break;
        case '2':
            Menu_Visualizacao(); break;
        case '3':
            Menu_Visualizar_Dados(); break;
        case '4':
            Varios_Carros_Com_Autonomia<int>();
        case '0':
            break;
        default:
            Menu_Principal(); break;
    }
}

// Função que trata da visualização do Menu Mapas, onde são dados a escolher ao utilizador vários mapas
template <class T>
int Menu_Mapas() {

    cout << "\n\n\t\t     Menu de Escolha do Mapa \n\n";
    cout << "\t GraphGrid \n";
    cout << "[1] 4x4 \n";
    cout << "[2] 8x8 \n";
    cout << "[3] 16x16 \n";
    cout << "[4] Personalizado \n";
    cout << "\n\t Mapas de Portugal \n";
    cout << "\n Mapas Fortemente Conexos \n\n";
    cout << "[5] Penafiel \n";
    cout << "[6] Espinho \n";
    cout << "[7] Porto \n";
    cout << "\n Mapas Nao Conexos \n\n";
    cout << "[8] Penafiel \n";
    cout << "[9] Espinho \n";
    cout << "[10] Porto \n\n";
    cout << "[11] Analisar Tempo \n";



    cout << "\n[0] Sair do Programa \n";
    cout << "\nOpcao: ";

    string name;
    cin >> name;
    char opcao;
    if(name.size() == 1) opcao = name[0];
    else {
        if (name == "10") opcao = 'p';
        else if (name == "11") opcao = 'a';
        else opcao = 'r';
    }

    switch(opcao)
    {
        case '1':
            bidirectional_edges = true;
            readMap<T>("../maps/GridGraphs/4x4");
            break;
        case '2':
            bidirectional_edges = true;
            readMap<T>("../maps/GridGraphs/8x8");
            break;
        case '3':
            bidirectional_edges = true;
            readMap<T>("../maps/GridGraphs/16x16");
            break;
        case '4':
            bidirectional_edges = false;
            readMap<T>("../maps/Personalizado");
            break;
        case '5':
            bidirectional_edges = false;
            readMap<T>("../maps/MapasConexos/Penafiel");
            break;
        case '6':
            bidirectional_edges = false;
            readMap<T>("../maps/MapasConexos/Espinho");
            break;
        case '7':
            bidirectional_edges = false;
            readMap<T>("../maps/MapasConexos/Porto");
            break;
        case '8':
            bidirectional_edges = false;
            readMap<T>("../maps/MapasNaoConexos/Penafiel");
            break;
        case '9':
            bidirectional_edges = false;
            readMap<T>("../maps/MapasNaoConexos/Espinho");
            break;
        case 'a':
            Analise_Temporal();
        case 'p':
            bidirectional_edges = false;
            readMap<T>("../maps/MapasNaoConexos/Porto");
            break;
        case '0':
            return 1;
        default:
            Menu_Mapas<int>(); break;
    }
    return 0;
}


int main() {
    if (Menu_Mapas<int>() == 1)
        return 0;
    all_info();
    Menu_Principal();
    system("pause");
    return 0;
}
