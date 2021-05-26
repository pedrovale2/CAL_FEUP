//
// Created by pedro on 18/05/2021.
//

#ifndef E_ESTAFETAS_UTILS_H
#define E_ESTAFETAS_UTILS_H

#include "Car.h"
#include "Client.h"
#include "Request.h"
#include "Store.h"
#include "Company.h"
#include "Graph.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <string>
#include <accctrl.h>

extern Graph<int> graph;
extern Company<int> company;
extern bool bidirectional_edges;

void Menu_Principal();
char Sair_Programa();



template <class T>      // Lê os vértices do ficheiro enviado como parâmetro
void readNodes(string file_directory) {
    ifstream ler;
    string number;
    string tuple;
    ler.open(file_directory);
    getline(ler, number);
    int n = stoi(number);
    for (unsigned int i = 0 ; i < n ; i++) {
        getline(ler, tuple);
        tuple = tuple.substr(1, tuple.size() - 2);

        stringstream ss(tuple);
        string id, latitude, longitude;
        getline(ss, id, ',');
        getline(ss, latitude, ',');
        getline(ss, longitude, ',');
        Vertex<T>* vertex = new Vertex<T>(stoi(id), stof(latitude), stof(longitude));
        graph.addVertex(vertex);
    }


    ler.close();
}

template <class T>      // Lê as arestas do ficheiro enviado como parâmetro
void readEdges(string file_directory) {
    ifstream ler;
    string number;
    string tuple;
    ler.open(file_directory);
    getline(ler, number);
    int n = stoi(number);
    if (bidirectional_edges) {
        for (unsigned int i = 0 ; i < 2*n ; i += 2) {
            getline(ler, tuple);
            tuple = tuple.substr(1, tuple.size() - 2);

            stringstream ss(tuple);
            string id1, id2;
            getline(ss, id1, ',');
            getline(ss, id2, ',');
            graph.addEdge(i + 1, stoi(id1), stoi(id2));
            graph.addEdge(i + 2, stoi(id2), stoi(id1));
        }
    }
    else {
        for (unsigned int i = 0; i < n; i++) {
            getline(ler, tuple);
            tuple = tuple.substr(1, tuple.size() - 2);

            stringstream ss(tuple);
            string id1, id2;
            getline(ss, id1, ',');
            getline(ss, id2, ',');
            graph.addEdge(i + 1, stoi(id1), stoi(id2));
        }
    }



    ler.close();
}

template <class T>       // Constrói os paths dos ficheiros e lê os vértices e as arestas destes
void readMap(string directory) {
    string nodes_path = directory + "/nodes.txt";
    string edges_path = directory + "/edges.txt";
    graph.reset();
    readNodes<int>(nodes_path);
    readEdges<int>(edges_path);

    for(Vertex<T>* v: graph.getVertexSet()){
        for(Edge<T> e: v->getAdj()){
            double i=graph.getDist(v->getInfo(),e.getDest()->getInfo());
            e.setWeight(i);
        }
    }
}


// Apresenta o grafo completo, mostrando todos os clients, stores, e carros que estão presentes na empresa
void Visualizar_Mapa() {
    GraphViewer gv;
    gv.createWindow(800, 800);
    gv.setCenter(sf::Vector2f(300, 300));
    for (Vertex<int> *vertex : graph.getVertexSet()) {
        Client<int> *clientaux = company.findClient(vertex->getInfo());
        Store<int>* storeaux = company.findStore(vertex->getInfo());
        Car<int>* caraux = company.findCar(vertex->getInfo());
        GraphViewer::Node &node0 = gv.addNode(vertex->getInfo(), sf::Vector2f(vertex->getX(), vertex->getY()));
        gv.lock();
        switch (vertex->getType()) {
            case 0:     // Não é ponto de interesse
                node0.setColor(GraphViewer::BLUE);
                break;
            case 1:     // Morada de Cliente
                node0.setColor(GraphViewer::GREEN);
                node0.setSize(30);
                node0.setLabel("Cliente " + clientaux->getName());
                break;
            case 2:     // Store
                node0.setColor(GraphViewer::RED);
                node0.setLabel("Store " + storeaux->getName());
                node0.setSize(30);
                break;
            case 3:     // Posição de Car
                node0.setColor(GraphViewer::YELLOW);
                node0.setLabel("Car " + caraux->getName());
                node0.setSize(30);
                break;

            case 4:     // Parque
                node0.setColor(GraphViewer::ORANGE);
                node0.setSize(30);
                node0.setLabel("Parque");
                break;

        }
        gv.unlock();
    }


    for (Vertex<int>* vertex : graph.getVertexSet()) {
        for (Edge<int> edge : vertex->getAdj()) {
            GraphViewer::Node &node1 = gv.getNode(vertex->getInfo());
            GraphViewer::Node &node2 = gv.getNode(edge.getDest()->getInfo());
            gv.addEdge(edge.getID(), node1, node2);
        }
    }


    gv.join();
}

template<class T>       // Trata da informação do Parque da Empresa
void parque_info() {
    company.setParque(graph.getVertexSet()[0]->getInfo());
    Vertex<T>* vertex = graph.findVertex(company.getParque());
    vertex->setType(4);
}

template<class T>       // Lê as informações relativas aos clients do ficheiro
void clients_info() {

    vector<Client<T>*> v;
    ifstream ler;
    ler.open("../files/clients.txt");
    while(!ler.eof()){
        string nome, morada, separacao;
        getline(ler, nome);
        getline(ler, morada);
        getline(ler, separacao);


        Client<int>* client = new Client<int>(nome, stoi(morada));
        Vertex<T>* vertex = graph.findVertex(client->getNodeID());
        if(vertex==nullptr){continue;}
        else{v.push_back(client);};
    }


    company.setClients(v);
    ler.close();

    for (Client<T>* client : company.getClients()) {
        Vertex<T>* vertex = graph.findVertex(client->getNodeID());
        if (vertex->getType() == 0) {
            vertex->setType(1);
        }
    }
}



template <class T>      // Lê as informações relativas aos stores do ficheiro
void stores_info() {
    vector<Store<T>*> v;
    ifstream ler;
    ler.open("../files/stores.txt");
    while(!ler.eof()){
        string nome, morada, desc, separacao;
        getline(ler, nome);
        getline(ler, morada);
        getline(ler, separacao);

        Store<T>* store = new Store<T>(nome, stoi(morada));
        Vertex<T>* vertex = graph.findVertex(store->getNodeID());
        if(vertex==nullptr){continue;}
        else{
            v.push_back(store);
        }
    }
    company.setStores(v);
    ler.close();

    for (Store<T>* store : company.getStores()) {
        Vertex<T>* vertex = graph.findVertex(store->getNodeID());
        if (vertex->getType() == 0) {
            vertex->setType(2);
        }
    }
}


template <class T>      // Lê as informações relativas aos carros do ficheiro
void cars_info() {
    vector<Car<T>*> v;
    ifstream ler;
    ler.open("../files/cars.txt");
    while(!ler.eof()){
        string nome, pos, battery, separacao;
        getline(ler, nome);
        getline(ler, battery);
        getline(ler, separacao);
        Car<T>* car = new Car<T>(nome, stoi(battery), company.getParque());

        Vertex<T>* vertex = graph.findVertex(car->getPosition());
        if(vertex==nullptr){continue;}
        else{
            v.push_back(car);
        }
    }


    company.setCars(v);

    ler.close();

    for (Car<T>* car : company.getCars()) {
        Vertex<T>* vertex = graph.findVertex(car->getPosition());
        if (vertex->getType() == 0) {
            vertex->setType(3);
        }
    }
}

void all_info(){
    parque_info<int>();
    clients_info<int>();
    stores_info<int>();
    cars_info<int>();

}


template <class T>      // Verifica se um dado vertex é um dos vertices envolvidos nos pedidos
int is_InRequests(Vertex<T>* vertex) {
    int numero_pedido = 0;
    for (Request<T>* request : company.getRequests()) {
        numero_pedido++;
        Vertex<T>* rest = graph.findVertex(request->getStore()->getNodeID());
        Vertex<T>* cl = graph.findVertex(request->getClient()->getNodeID());
        Vertex<T>* est = graph.findVertex(request->getCar()->getPosition());
        if (rest->getInfo() == vertex->getInfo() || cl->getInfo() == vertex->getInfo() || est->getInfo() == vertex->getInfo())
            return numero_pedido;
    }
    return 0;
}

// Verifica se um dado vertex pertence a um vetor de vértices
template <class T>
bool isIn( Vertex<T>* vertex,vector<Vertex<T>*> v) {
    for (Vertex<T>* vert : v) {
        if (vert->getInfo() == vertex->getInfo())
            return true;
    }
    return false;
}

template <class T>
bool is_in ( T m, vector<T> v ){
    for (T i : v){
        if (m == i)
            return true;
    }

    return false;
}


template <class T>
double get_path_distance( vector<Vertex<T> *> result){
    vector<Vertex<T> *> percurso;

    T init = result[0]->getInfo();
    T final;
    graph.dijkstraShortestPath(company.getParque());
    vector<Vertex<T> *> vetor = graph.getPath(company.getParque(), init);
    percurso.insert(percurso.end(), vetor.begin(), vetor.end() - 1);
    bool inicio = true;
    for (Vertex<T>* vertex : result) {
        if (inicio) {
            inicio = false;
            continue;
        }

        final = vertex->getInfo();
        graph.dijkstraShortestPath(init);
        vetor = graph.getPath(init, final);
        percurso.insert(percurso.end(), vetor.begin(), vetor.end() - 1);

        init = final;

        if(result.back()->getInfo() == vertex->getInfo()){
            graph.dijkstraShortestPath(init);
            final = company.getParque();
            vetor = graph.getPath(init, final);
            percurso.insert(percurso.end(), vetor.begin(), vetor.end() );
        }

    }

    percurso.push_back(graph.findVertex(final));

    double distancia_total_pedido = 0;

    for (unsigned int i = 0; i < percurso.size() - 1; i++) {
        for (Edge<int> edge : percurso[i]->getAdj()) {
            if (edge.getDest() == percurso[i + 1]) {
                distancia_total_pedido += edge.getWeight();
                break;
            }
        }
    }

    return distancia_total_pedido;

}

template <class T>
double get_distance( vector<Vertex<T> *> result){

    double distancia_total_pedido = 0;

    for (unsigned int i = 0; i < result.size() - 1; i++) {
        for (Edge<int> edge : result[i]->getAdj()) {
            if (edge.getDest() == result[i + 1]) {
                distancia_total_pedido += edge.getWeight();
                break;
            }
        }
    }

    return distancia_total_pedido;

}



template <class T>
double calculate_special_distance(T begin, T end){
     double total = graph.getDist(begin, end) + graph.getDist(end, company.getParque());
     return total;
}


template <class T>       // Apresenta o grafo e os vários percursos dos vários carros
void showMultiplePathsGV(vector<vector<Vertex<T>*>> percursos) {
    GraphViewer gv;
    gv.createWindow(800, 800);
    gv.setCenter(sf::Vector2f(300, 300));

    int n_request;
    for (Vertex<int> *vertex : graph.getVertexSet()) {
        Client<int> *clientaux = company.findClient(vertex->getInfo());
        Store<int>* storeaux = company.findStore(vertex->getInfo());
        Car<int>* caraux = company.findCar(vertex->getInfo());
        GraphViewer::Node &node0 = gv.addNode(vertex->getInfo(), sf::Vector2f(vertex->getX(), vertex->getY()));
        gv.lock();
        switch (vertex->getType()) {
            case 0:     // Não é ponto de interesse
                node0.setColor(GraphViewer::BLUE);
                break;
            case 1:     // Morada de Cliente
                node0.setColor(GraphViewer::GREEN);
                node0.setSize(40);
                node0.setLabel("Cliente " + clientaux->getName());
                break;
            case 2:     // Store
                node0.setColor(GraphViewer::RED);
                node0.setLabel("Store " + storeaux->getName());
                node0.setSize(40);
                break;
            case 3:     // Posição de Car
                node0.setColor(GraphViewer::YELLOW);
                node0.setLabel("Car " + caraux->getName());
                node0.setSize(40);
                break;

            case 4:     // Parque da Empresa
                node0.setColor(GraphViewer::ORANGE);
                node0.setSize(40);
                node0.setLabel("Parque");
                break;

        }
        gv.unlock();
    }


    for (Vertex<int> *vertex : graph.getVertexSet()) {
        for (Edge<int> edge : vertex->getAdj()) {
            GraphViewer::Node &node1 = gv.getNode(vertex->getInfo());
            GraphViewer::Node &node2 = gv.getNode(edge.getDest()->getInfo());
            gv.addEdge(edge.getID(), node1, node2, GraphViewer::Edge::EdgeType::DIRECTED);

        }
    }

    if(percursos.size()==0) return;

    // Mostra na consola a conexão entre os dados apresentados no ecrã e os dados dos clients, stores e carros da empresa
    cout << "\n Dados: " << endl << endl;

    n_request = 0;
    for (Request<T>* request : company.getRequests()) {
        n_request++;
        cout << "Pedido " + to_string(n_request) + ": Cliente - " << request->getClient()->getName() << "   Loja - " << request->getStore()->getName() << endl;
    }





    // Limpeza dos boleanos que permitiram a organização do output da consola
    for (Request<T>* request : company.getRequests()) {
        request->getClient()->setRepeated(false);
        request->getStore()->setRepeated(false);
        request->getCar()->setRepeated(false);
    }

    Sleep(2000);    // Concede tempo para o GraphViewer abrir


    int num_percurso=1;
    GraphViewer::Color color;
    // Desenha os percursos dos vários carros

    if(percursos.empty())
        cout << "NAO CONSEGUI REALIZAR PERCURSOS" << endl;
    for(vector<Vertex<T>*> v: percursos) {
        if(!v.empty()) {
            for (unsigned int i = 0; i < v.size() - 1; i++) {
                if (num_percurso % 4 == 1) { color = sf::Color::Red; }
                if (num_percurso % 4 == 2) { color = sf::Color::Green; }
                if (num_percurso % 4 == 3) { color = sf::Color::Yellow; }
                if (num_percurso % 4 == 0) { color = sf::Color::Blue; }
                Sleep(30);     // Mostra o percurso construtivamente
                if (!is_InRequests(v[i + 1])) {
                    GraphViewer::Node &node = gv.getNode(v[i + 1]->getInfo());
                    gv.lock();
                    node.setColor(GraphViewer::PINK);
                    gv.unlock();
                }
                for (Edge<int> edge : v[i]->getAdj()) {
                    if (edge.getDest() == v[i + 1]) {
                        GraphViewer::Edge &edge1 = gv.getEdge(edge.getID());

                        gv.lock();
                        edge1.setColor(color);
                        gv.unlock();

                        break;
                    }
                }

            }

            num_percurso++;
        }
    }

    gv.join();

    char sair = Sair_Programa();
    if (sair == 'N' || sair == 'n')
        Menu_Principal();
}


template <class T>       // Devolve o id do vertex onde se encontra a loja mais próximo do estafeta
T get_NearestStore(T pos, vector<T> vetor) {
    int i = 0;
    T proximo;
    for (T rest : vetor) {
        if (i == 0)
            proximo = vetor[0];
        else {
            if (graph.getDist(pos, rest) < graph.getDist(pos, proximo))
                proximo = rest;
        }
        i++;
    }
    return proximo;
}

template <class T>
Request<T>* findRequest(T info, vector<Request<T>*> requests ){
    for (Request<T>* request : requests) {
        if(request->getClient()->getNodeID() == info)
            return request;
        else if(request->getStore()->getNodeID()==info)
            return request;
    }
    return nullptr ;
}

template <class T>      // Apaga o id de um dado vertex de um vetor de ids de vertices
void erase(T inf, vector<T> &vetor) {
    for (typename vector<T>::iterator it = vetor.begin() ; it != vetor.end() ; it++) {
        if ((*it) == inf) {
            vetor.erase(it);
            break;
        }
    }
}

template <class T>      //Apaga pedido de um vetor de pedidos
void erase_request(Request<T>* pedido, vector<Request<T>*> &pedidos){
    for (typename vector<Request<T>*>::iterator it = pedidos.begin() ; it != pedidos.end() ; it++) {
        if  ( *it == pedido) {
            pedidos.erase(it);
            break;
        }
    }
}







#endif //E_ESTAFETAS_UTILS_H
