//
// Created by pedro on 19/05/2021.
//

#ifndef E_ESTAFETAS_CONNECTIVITY_H
#define E_ESTAFETAS_CONNECTIVITY_H


#include "Graph.h"
extern Graph<int> graph;


// Algoritmo de visita em profundidade
template <class T>
void dfsVisit(Vertex<T> *v, vector<Vertex<T> *> & res) {

    v->visited=true;

    res.push_back(v);
    for(unsigned int i = 0; i < v->getAdj().size(); i++) {
        if (!v->getAdj().at(i).getDest()->visited) {
            dfsVisit(v->getAdj().at(i).getDest(), res);
        }
    }

}

// Função que chama o algoritmo de visita em profundidade, tratando das suas preparações
template <class T>
std::vector<Vertex<T> *> dfs(Graph<T> *graph1, Vertex<T> *initial) {
    vector<Vertex<T> *> res;
    for(Vertex<T> * vertex: graph1->getVertexSet()){
        vertex->visited = false;
    }
    dfsVisit(initial, res);

    return res;
}

// Função que verifica se um vetor de vértices contém um dado vértice
template <class T>
bool containsVertex(std::vector<Vertex<T> *> vectorVert, Vertex<T> * vert){
    for(auto v : vectorVert)
        if( (vert->getInfo()) == (v->getInfo()))
            return true;
    return false;
}

// Função que mostra no GraphViewer a conetividade de um grafo
template <class T>
void showConnection(vector<T> vec) {        // Apresenta no ecrã a conetividade do grafo
    GraphViewer gv;
    gv.createWindow(800, 800);
    gv.setCenter(sf::Vector2f(300, 300));

    vector<Vertex<T>*> vector_vertexs;
    for (Vertex<T>* vertex : graph.getVertexSet()) {
        GraphViewer::Node &node0 = gv.addNode(vertex->getInfo(), sf::Vector2f(vertex->getX(), vertex->getY()));
    }
    for (Vertex<T>* vertex : graph.getVertexSet()) {
        for (Edge<T> edge : vertex->getAdj()) {
            GraphViewer::Node &node1 = gv.getNode(vertex->getInfo());
            GraphViewer::Node &node2 = gv.getNode(edge.getDest()->getInfo());
            gv.addEdge(edge.getID(), node1, node2, GraphViewer::Edge::EdgeType::DIRECTED);
        }
    }
    for (unsigned int i = 0 ; i < vec.size() ; i++) {
        Vertex<T>* vertex = graph.findVertex(vec[i]);
        GraphViewer::Node &node0 = gv.getNode(vertex->getInfo());
        gv.lock();
        node0.setColor(gv.GREEN);
        gv.unlock();
        for (Edge<T> edge : vertex->getAdj()) {
            GraphViewer::Edge &edge1 = gv.getEdge(edge.getID());
            gv.lock();
            edge1.setColor(gv.GREEN);
            gv.unlock();

        }
    }
    gv.join();


}

// Função que avalia a conetividade de um grafo
template <class T>
vector<Vertex<T>*> Avaliar_Conetividade(Vertex<T> *v) {               // Avalia a Conetividade do Grafo a partir de V

    vector<Vertex<T>*> res_normal= dfs(&graph,v); // Pesquisa em profundidade no grafo normal

    T info = v->getInfo();
    Graph<T> *invertedGraph = graph.invert();   //Inverter Grafo
    Vertex<T> *invInitial = invertedGraph->findVertex(info);

    vector<Vertex<T> *> res_invert = dfs(invertedGraph, invInitial); // Pesquisa em profundidade no grafo invertido

    vector<Vertex<T> *> res;
    for(auto v: res_normal){
        if(containsVertex(res_invert, v))
            res.push_back(v);
    }

    return res;

}




#endif //E_ESTAFETAS_CONNECTIVITY_H
