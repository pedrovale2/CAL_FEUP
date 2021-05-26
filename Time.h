//
// Created by pedro on 24/05/2021.
//

#ifndef E_ESTAFETAS_TIME_H
#define E_ESTAFETAS_TIME_H


#include <ctime>

#include "Graph.h"
#include "Algorithms.h"
#include "utils.h"
#include "Connectivity.h"

extern Car<int>* active_car;


template <class T>
void Tempo_Alg_4() {
    srand(time(NULL));



    struct timespec start, finish;
    double elapsed;

    //-------------------------------         Para Grid 4x4         ------------------------------------------

    // Iniciar Grafo e Dados da company
    vector<Request<T>*> pedidos;
    bidirectional_edges = true;
    readMap<T>("../maps/GridGraphs/4x4");
    all_info();

    // Criação de Pedidos Random
    for (unsigned int i = 0 ; i < 10 ; i++) {
        int client_id = rand() % company.getNumClients();
        int store_id = rand() % company.getNumStores();
        Client<int> *cliente = company.getClients().at(client_id);
        Store<int> *restaurante = company.getStores().at(store_id);
        Request<T> *pedido = new Request<int>( cliente, restaurante);
        pedidos.push_back(pedido);
    }
    company.setRequests(pedidos);

    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (Car<T> *car: company.getCars()) {
        alg(car, pedidos);
    }

    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    cout << "\nGrid4x4\n";
    cout << "Time: " << elapsed*1000 << endl;
    //-------------------------------         Para Grid 8x8         ------------------------------------------

    // Iniciar Grafo e Dados da company
    pedidos.clear();
    bidirectional_edges = true;
    readMap<T>("../maps/GridGraphs/8x8");
    all_info();

    // Criação de Pedidos Random
    for (unsigned int i = 0 ; i < 10 ; i++) {
        int client_id = rand() % company.getNumClients();
        int store_id = rand() % company.getNumStores();
        Client<T> *cliente = company.getClients().at(client_id);
        Store<T> *restaurante = company.getStores().at(store_id);
        Request<T> *pedido = new Request<int>( cliente, restaurante);
        pedidos.push_back(pedido);
    }
    company.setRequests(pedidos);

    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (Car<T> *car: company.getCars()) {
        alg(car, pedidos);
    }
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    cout << "\nGrid8x8\n";
    cout << "Time: " << elapsed*1000 << endl;

    //-------------------------------         Para Grid 16x16         ------------------------------------------
    // Iniciar Grafo e Dados da company
    pedidos.clear();
    bidirectional_edges = true;
    readMap<T>("../maps/GridGraphs/16x16");
    all_info();

    // Criação de Pedidos Random
    for (unsigned int i = 0 ; i < 10 ; i++) {
        int client_id = rand() % company.getNumClients();
        int store_id = rand() % company.getNumStores();
        Client<T> *cliente = company.getClients().at(client_id);
        Store<T> *restaurante = company.getStores().at(store_id);
        Request<T> *pedido = new Request<int>(cliente, restaurante);
        pedidos.push_back(pedido);
    }
    company.setRequests(pedidos);


    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (Car<T> *car: company.getCars()) {
        alg(car, pedidos);
    }
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;


    cout << "\nGrid16x16\n";
    cout << "Time: " << elapsed*1000 << endl;

    //-------------------------------         Para Mapa Penafiel         ------------------------------------------
    // Iniciar Grafo e Dados da company
    pedidos.clear();
    bidirectional_edges = true;
    readMap<T>("../maps/MapasConexos/Penafiel");
    all_info();

    // Criação de Pedidos Random
    for (unsigned int i = 0 ; i < 10 ; i++) {
        int client_id = rand() % company.getNumClients();
        int store_id = rand() % company.getNumStores();
        Client<T> *cliente = company.getClients().at(client_id);
        Store<T> *restaurante = company.getStores().at(store_id);
        Request<T> *pedido = new Request<int>(cliente, restaurante);
        pedidos.push_back(pedido);
    }
    company.setRequests(pedidos);


    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (Car<T> *car: company.getCars()) {
        alg(car, pedidos);
    }
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    cout << "\nPenafiel\n";
    cout << "Time: " << elapsed*1000 << endl;

    //-------------------------------         Para Mapa Espinho         ------------------------------------------
    // Iniciar Grafo e Dados da company
    pedidos.clear();
    bidirectional_edges = true;
    readMap<T>("../maps/MapasConexos/Espinho");
    all_info();

    // Criação de Pedidos Random
    for (unsigned int i = 0 ; i < 10 ; i++) {
        int client_id = rand() % company.getNumClients();
        int store_id = rand() % company.getNumStores();
        Client<T> *cliente = company.getClients().at(client_id);
        Store<T> *restaurante = company.getStores().at(store_id);
        Request<T> *pedido = new Request<int>(cliente, restaurante);
        pedidos.push_back(pedido);
    }
    company.setRequests(pedidos);


    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (Car<T> *car: company.getCars()) {
        alg(car, pedidos);
    }
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    cout << "\nEspinho\n";
    cout << "Time" << ": " << elapsed*1000 << endl;


}

template <class T>
void Tempo_DFS() {
    srand(time(NULL));


    struct timespec start, finish;
    double elapsed;

    //-------------------------------         Para Grid 4x4         ------------------------------------------
    // Iniciar Grafo e Dados da EatExpress
    bidirectional_edges = true;
    readMap<T>("../maps/GridGraphs/4x4");
    all_info();

    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    vector<Vertex<T>*> vetor = dfs(&graph, graph.getVertexSet()[0]);
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    cout << "\nGrid4x4\n";
    cout << "Time" << ": " << elapsed*1000 << endl;

    //-------------------------------         Para Grid 8x8         ------------------------------------------
    // Iniciar Grafo e Dados da EatExpress
    bidirectional_edges = true;
    readMap<T>("../maps/GridGraphs/8x8");
    all_info();

    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    vetor = dfs(&graph, graph.getVertexSet()[0]);
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    cout << "\nGrid8x8\n";
    cout << "Time" << ": " << elapsed*1000 << endl;

    //-------------------------------         Para Grid 16x16         ------------------------------------------
    // Iniciar Grafo e Dados da EatExpress
    bidirectional_edges = true;
    readMap<T>("../maps/GridGraphs/16x16");
    all_info();

    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    vetor = dfs(&graph, graph.getVertexSet()[0]);
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    cout << "\nGrid16x16\n";
    cout << "Time" << ": " << elapsed*1000 << endl;

    //-------------------------------         Para Mapa Penafiel         ------------------------------------------
    // Iniciar Grafo e Dados da EatExpress
    bidirectional_edges = true;
    readMap<T>("../maps/MapasConexos/Penafiel");
    all_info();

    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    vetor = dfs(&graph, graph.getVertexSet()[0]);
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    cout << "\nPenafiel\n";
    cout << "Time" << ": " << elapsed*1000 << endl;

    //-------------------------------         Para Mapa Espinho         ------------------------------------------
    // Iniciar Grafo e Dados da EatExpress
    bidirectional_edges = true;
    readMap<T>("../maps/MapasConexos/Espinho");
    all_info();

    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    vetor = dfs(&graph, graph.getVertexSet()[0]);
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    cout << "\nEspinho\n";
    cout << "Time" << ": " << elapsed*1000 << endl;
}

template <class T>
void Tempo_Avaliar_Conetividade() {
    srand(time(NULL));


    struct timespec start, finish;
    double elapsed;

    //-------------------------------         Para Grid 4x4         ------------------------------------------
    // Iniciar Grafo e Dados da EatExpress
    bidirectional_edges = true;
    readMap<T>("../maps/GridGraphs/4x4");
    all_info();

    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    vector<Vertex<T>*> vetor = Avaliar_Conetividade(graph.getVertexSet()[0]);
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    cout << "\nGrid4x4\n";
    cout << "Time" << ": " << elapsed*1000 << endl;

    //-------------------------------         Para Grid 8x8         ------------------------------------------
    // Iniciar Grafo e Dados da EatExpress
    bidirectional_edges = true;
    readMap<T>("../maps/GridGraphs/8x8");
    all_info();

    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    vector<Vertex<T>*> vetor1 = Avaliar_Conetividade(graph.getVertexSet()[0]);
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    cout << "\nGrid8x8\n";
    cout << "Time" << ": " << elapsed*1000 << endl;

    //-------------------------------         Para Grid 16x16         ------------------------------------------
    // Iniciar Grafo e Dados da EatExpress
    bidirectional_edges = true;
    readMap<T>("../maps/GridGraphs/16x16");
    all_info();

    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    vector<Vertex<T>*> vetor2 = Avaliar_Conetividade(graph.getVertexSet()[0]);
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    cout << "\nGrid16x16\n";
    cout << "Time" << ": " << elapsed*1000 << endl;

    //-------------------------------         Para Mapa Penafiel         ------------------------------------------
    // Iniciar Grafo e Dados da EatExpress
    bidirectional_edges = false;
    readMap<T>("../maps/MapasConexos/Penafiel");
    all_info();

    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    vector<Vertex<T>*> vetor3 = Avaliar_Conetividade(graph.getVertexSet()[0]);
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    cout << "\nPenafiel\n";
    cout << "Time" << ": " << elapsed*1000 << endl;
}

template <class T>
void Tempo_Dijkstra() {
    srand(time(NULL));


    bidirectional_edges = true;
    readMap<T>("../maps/GridGraphs/4x4");

    struct timespec start, finish;
    double elapsed;

    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (unsigned int i = 1 ; i <= 50 ; i++) {
        Vertex<T> *src = graph.findVertex(rand() % graph.getNumVertex());
        graph.dijkstraShortestPath(src->getInfo());
    }

    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    cout << "\nGrid4x4\n";
    cout << "Time" << ": " << elapsed*1000 << endl;

    bidirectional_edges = true;
    readMap<T>("../maps/GridGraphs/8x8");

    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (unsigned int i = 1 ; i <= 50 ; i++) {
        Vertex<T> *src = graph.findVertex(rand() % graph.getNumVertex());
        graph.dijkstraShortestPath(src->getInfo());
    }
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    cout << "\nGrid8x8\n";
    cout << "Time" << ": " << elapsed*1000 << endl;

    bidirectional_edges = true;
    readMap<T>("../maps/GridGraphs/16x16");

    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (unsigned int i = 1 ; i <= 50 ; i++) {
        Vertex<T> *src = graph.findVertex(rand() % graph.getNumVertex());
        graph.dijkstraShortestPath(src->getInfo());
    }

    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    cout << "\nGrid16x16\n";
    cout << "Time" << ": " << elapsed*1000 << endl;


    bidirectional_edges = false;
    readMap<T>("../maps/MapasNaoConexos/Penafiel");

    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (unsigned int i = 1 ; i <= 50 ; i++) {
        Vertex<T> *src = graph.findVertex(rand() % graph.getNumVertex());
        graph.dijkstraShortestPath(src->getInfo());
    }

    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    cout << "\nPenafiel Nao Conexo\n";
    cout << "Time" << ": " << elapsed*1000 << endl;


    bidirectional_edges = false;
    readMap<T>("../maps/MapasNaoConexos/Espinho");

    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (unsigned int i = 1 ; i <= 50 ; i++) {
        Vertex<T> *src = graph.findVertex(rand() % graph.getNumVertex());
        graph.dijkstraShortestPath(src->getInfo());
    }

    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    cout << "\nEspinho Nao Conexo\n";
    cout << "Time" << ": " << elapsed*1000 << endl;


}


void Analise_Temporal() {
    Tempo_DFS<int>();
    //Tempo_Avaliar_Conetividade<int>();
    //Tempo_Dijkstra<int>();
    //Tempo_Alg_4<int>();
    exit(0);
}
#endif //E_ESTAFETAS_TIME_H
