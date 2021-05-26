//
// Created by pedro on 19/05/2021.
//

#ifndef E_ESTAFETAS_GRAPH_H
#define E_ESTAFETAS_GRAPH_H

#include <vector>
#include <iostream>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <stack>
#include <algorithm>
#include <unordered_set>
#include "MutablePriorityQueue.h"

#include "Company.h"
#include "Request.h"

using namespace std;

extern Company<int> company;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/**************************************************** Vertex  *****************************************************************/

template <class T>
class Vertex {
    T info;						// content of the vertex
    double x;
    double y;
    vector<Edge<T> > adj;		// outgoing edges
    double dist = 0;
    Vertex<T> *path = NULL;
    int queueIndex = 0; 		// required by MutablePriorityQueue
    bool processing = false;	// auxiliary field

    int type = 0;   // 0 se não for ponto de interesse, 1 se for uma morada cliente, 2 se for uma store, 3 se estiver ocupado por um estafeta e 4 unicamente para o parque da empresa

    void addEdge(int id, Vertex<T> *dest, double w);

public:
    bool visited = false;		// auxiliary field
    Vertex(T in, double x, double y);
    T getInfo() const;
    double getX() const;
    double getY() const;
    int getNumEdges() const;
    double getDist() const;
    Vertex *getPath() const;
    vector<Edge<T>> getAdj() const;
    int getType() const;
    void setType(int type);
    void setDist(double d);
    void setPath(Vertex<T>* p);

    bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
    friend class Graph<T>;
    friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in, double x, double y): info(in), x(x), y(y) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(int id, Vertex<T> *d, double w) {
    adj.push_back(Edge<T>(id, d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
    return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
    return this->info;
}

template <class T>
double Vertex<T>::getX() const {
    return this->x;
}

template <class T>
double Vertex<T>::getY() const {
    return this->y;
}

template <class T>
int Vertex<T>::getNumEdges() const {
    return adj.size();
}

template <class T>
double Vertex<T>::getDist() const {
    return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
    return this->path;
}

template <class T>
vector<Edge<T>> Vertex<T>::getAdj() const {
    return adj;
}

template <class T>
int Vertex<T>::getType() const {
    return type;
}

template <class T>
void Vertex<T>::setType(int type) {
    this->type = type;
}

template <class T>
void Vertex<T>::setDist(double d){
    this->dist=d;
}

template <class T>
void Vertex<T>::setPath(Vertex<T>* p){
    this->path=p;
}

/************************************************************ Edge  *******************************************************************/

template <class T>
class Edge {
    int edgeID;
    Vertex<T> * dest;      // destination vertex
    double weight;         // edge weight
    double dist;            //edge euclidian distance
public:
    Edge(int id, Vertex<T> *d, double w);
    Vertex<T>* getDest() const;
    double getWeight();
    int getID();
    void setID(int id);
    void setWeight(double d);
    friend class Graph<T>;
    friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(int id, Vertex<T> *d, double w): dest(d), weight(w), edgeID(id) {}

template <class T>
Vertex<T>* Edge<T>::getDest() const {
    return dest;
}

template <class T>
double Edge<T>::getWeight() {
    return this->weight;
}

template <class T>
int Edge<T>::getID() {
    return this->edgeID;
}

template <class T>
void Edge<T>::setID(int id) {
    this->edgeID = id;
}

template <class T>
void Edge<T>::setWeight(double d){this->weight=d;}

/********************************************************* Graph  **********************************************************************/

template <class T>
class Graph {
    vector<Vertex<T> *> vertexSet;

    // Matrix of distances between vertex, used in Floyd-Warshall Algorithm
    vector<vector<double>>  W; //distMin

    // Matrix of paths between vertex, used in Floyd-Warshall Algorithm
    vector<vector<int>> P; //predecedores


public:
    bool conexo;
    Vertex<T> * findVertex(T in) const;
    //bool addVertex(const T &in);
    bool addVertex(Vertex<T>* vertex);
    bool addEdge(int id, T source, T dest);
    int getNumVertex() const;
    int getNumEdges() const;
    void printVertexs();
    void printEdges();
    vector<Vertex<T> *> getVertexSet() const;
    vector<Vertex<T> *> getPath(const T &origin, const T &dest) const;
    int findVertexIdx(const T &in) const;
    double getW(int i, int j) const;
    void setW(int i, int j, double value);
    int getP(int i, int j) const;
    void setP(int i, int j, int index);
    void resetMatrixW(int n);
    void resetMatrixP(int n);
    void reset();

    int nextVertex(int i, int j);
    double edgeWeight(int i, int j);

    // Fp05 - single source
    void unweightedShortestPath(const T &s);
    void dijkstraShortestPath(const T &s);
    // bool dijkstraRelax(Vertex<T> *v, Vertex<T> *w, double weight);
    // std::vector<Vertex<T> *> dijkstraShortestPath2(Graph<T> * graph, const T &origin, const T &dest);
    void bellmanFordShortestPath(const T &s);
    vector<T> getPathTo(const T &dest) const;
    double getDist(const T &src, const T &dest) const;

    // Fp05 - all pairs
    void floydWarshallShortestPath();
    vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;
    vector<Vertex<T> *> NearestNeighborFloyd(const T &origin);
    Graph<T>* invert();

};

template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
int Graph<T>::getNumEdges() const {
    int sum = 0;
    for (Vertex<T>* v : vertexSet) {
        sum += v->getNumEdges();
    }
    return sum;
}

template <class T>
void Graph<T>::printVertexs() {
    for (Vertex<T>* v : vertexSet) {
        cout << "Id: " << v->getInfo() << "   Latitude: " << v->getX() << "   Longitude: " << v->getY() << endl;
    }
}

template <class T>
void Graph<T>::printEdges() {
    for (Vertex<T>* v : vertexSet) {
        for (Edge<T> e : v->getAdj())
            cout << "ID: " << e.getID() << "   Source: " << v->getInfo() << "   Dest: " << e.dest->getInfo() << "   Weight: " << e.weight << endl;
    }
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(T in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(Vertex<T>* vertex) {
    if (findVertex(vertex->getInfo()) != NULL)
        return false;
    vertexSet.push_back(vertex);
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(int id, T source, T dest) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    //cout << "Lat1: " << v1->getLatitude() << "   Lat2: " << v2->getX() << "   Long1 = " << v1->getLongitude() << "   Long2 = " << v2->getY() << endl;
    double weight = sqrt((v1->getX() - v2->getX()) * (v1->getX() - v2->getX()) + (v1->getY() - v2->getY()) * (v1->getY() -
                                                                                                              v2->getY()));
    v1->addEdge(id, v2, weight);
    return true;
}

template<class T>
vector<Vertex<T> *> Graph<T>::getPath(const T &origin, const T &dest) const {
    vector<Vertex<T> *> res;
    auto o = findVertex(origin);
    auto v = findVertex(dest);
    if (v == nullptr || v->dist == INF) {// missing or disconnected
        return res;
    }
    for ( ; v != o && v != nullptr; v = v->path)
        res.push_back(v);
    res.push_back(o);
    reverse(res.begin(), res.end());

    return res;
}

template <class T>
int Graph<T>::findVertexIdx(const T &in) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->info == in)
            return i;
    return -1;
}

template <class T>
double Graph<T>::getW(int i, int j) const{
    return W.at(i).at(j);
}

template <class T>
void Graph<T>::setW(int i, int j, double value){
    W.at(i).at(j) = value;
}

template <class T>
int Graph<T>::getP(int i, int j) const{
    return P.at(i).at(j);
}

template <class T>
void Graph<T>::setP(int i, int j, int index){
    P.at(i).at(j) = index;
}

template <class T>
void Graph<T>::resetMatrixW(int n) {
    W = vector<vector<double>> (n, vector<double> (n));
}

template <class T>
void Graph<T>::resetMatrixP(int n) {
    P = vector<vector<int>> (n, vector<int> (n));
}

template <class T>
void Graph<T>::reset() {
    vertexSet.clear();
}

template <class T>
int Graph<T>::nextVertex(int i, int j){
    for(Edge<T> edge : (vertexSet.at(i)->getAdj())){
        if(edge.dest == vertexSet.at(j))
            return j;
    }

    return -1;
}

template <class T>
double Graph<T>::edgeWeight(int i, int j){
    if(i == j) return 0;

    for(Edge<T> edge : (vertexSet.at(i)->getAdj())){
        if(edge.dest == vertexSet.at(j))
            return edge.getWeight();
    }

    return INF;
}

template <class T>
double Graph<T>::getDist(const T &src, const T &dest) const {
    Vertex<T>* s = findVertex(src);
    Vertex<T>* d = findVertex(dest);
    double i= sqrt(pow((s->getX() - d->getX()), 2) + pow((s->getY() - d->getY()), 2));
    return i;
}

/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
    for (auto vertex : vertexSet) {
        vertex->dist = INF;
        vertex->path = NULL;
    }
    auto origem = findVertex(orig);
    origem->dist = 0;
    queue <Vertex<T>*> fifo;
    fifo.push(origem);
    while (!fifo.empty()) {
        Vertex<T>* vertice = fifo.front();
        fifo.pop();
        for (auto edge : vertice->adj) {
            if (edge.dest->dist == INF) {
                fifo.push(edge.dest);
                edge.dest->dist = vertice->dist + 1;
                edge.dest->path = vertice;
            }
        }
    }
}

template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
    for (auto vertex : vertexSet) {
        vertex->dist = INF;
        vertex->path = NULL;
    }
    Vertex<T>* origem = findVertex(origin);
    origem->dist = 0;
    MutablePriorityQueue<Vertex<T>> fila;
    fila.insert(origem);
    while (!fila.empty()) {
        Vertex<T>* vertice = fila.extractMin();
        for (auto &edge : vertice->adj) {
            if (edge.dest->dist > vertice->dist + edge.weight) {
                edge.dest->dist = vertice->dist + edge.weight;
                edge.dest->path = vertice;
                if (!fila.inQueue(edge.dest))
                    fila.insert(edge.dest);
                else
                    fila.decreaseKey(edge.dest);
            }
        }
    }
}

template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
    for (auto vertex : vertexSet) {
        vertex->dist = INF;
        vertex->path = NULL;
    }
    Vertex<T>* origem = findVertex(orig);
    origem->dist = 0;
    for (unsigned int i = 1 ; i < vertexSet.size() - 1 ; i++) {
        for (auto vertex : vertexSet) {
            for (auto edge : vertex->adj) {
                if ((edge.dest)->dist > vertex->dist + edge.weight) {
                    (edge.dest)->dist = vertex->dist + edge.weight;
                    (edge.dest)->path = vertex;
                }
            }
        }
    }
    for (auto vertex : vertexSet) {
        for (auto edge : vertex->adj) {
            if (vertex->dist + edge.weight < (edge.dest)->dist) {
                cout << "Erro: O grafo tem arestas de peso negativo!\n";
            }
        }
    }
}

template<class T>
vector<T> Graph<T>::getPathTo(const T &dest) const{
    vector<T> res;
    Vertex<T>* destino = findVertex(dest);
    stack<T> pilha;
    pilha.push(dest);
    while (destino->getPath() != NULL) {
        pilha.push(destino->getPath()->getInfo());
        destino = destino->getPath();
    }
    while (!pilha.empty()) {
        res.push_back(pilha.top());
        pilha.pop();
    }
    return res;
}



/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
    bool undirected = true;
    unsigned n = getVertexSet().size();
    resetMatrixW(n);
    resetMatrixP(n);
    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = i; j < n; j++) {
            setW(i, j,edgeWeight(i, j));
            setW(j, i, edgeWeight(j, i));
            setP(i, j, nextVertex(i, j));
            setP(j, i, nextVertex(j, i));
        }
    }
    for(unsigned k = 0; k < n; k++)
        for(unsigned j = 0; j < n; j++)
            for(unsigned i = undirected ? j + 1 : 0; i < n; i++) {
                if(j == k || i == k || i == j ||getW(i, k) == INF ||getW(k, j) == INF)
                    continue; // avoid overflow and unnecessary calculations
                double val =getW(i, k) + getW(k, j);
                if (val < getW(i, j)) {
                    setW(i, j, val);
                    if(undirected) setW(j, i, val);

                    setP(i, j, getP(i, k));
                    if(undirected) setP(j, i, getP(j, k));
                }
            }

    /*distMin.clear();
    predecessores.clear();                  // Aloca memória para as Matrizes
    distMin = vector<vector<double>>(getNumVertex(), vector<double>(getNumVertex(), INF));
    predecessores = vector<vector<Vertex<T>*>>(getNumVertex(), vector<Vertex<T>*>(getNumVertex(), NULL));

    for (int i = 0 ; i < getNumVertex() ; i++) {
        for (int j = 0 ; j < getNumVertex() ; j++) {
            if (i == j) // Elementos da diagonal da Matriz a 0
                distMin[i][j] = 0;
            else {
                for (auto edge : vertexSet[i]->adj) {
                    if (edge.dest->getInfo() == vertexSet[j]->info) {
                        distMin[i][j] = edge.weight;
                        predecessores[i][j] = vertexSet[i];
                    }
                }
            }
        }
    }

    for (int k = 0 ; k < getNumVertex() ; k++) {
        for (int l = 0 ; l < getNumVertex() ; l++) {
            for (int m = 0 ; m < getNumVertex() ; m++) {
                if (distMin[l][m] > distMin[l][k] + distMin[k][m]) {
                    distMin[l][m] = distMin[l][k] + distMin[k][m];
                    predecessores[l][m] = predecessores[k][m];
                }
            }
        }
    }*/
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
    vector<T> res;
    int i = findVertexIdx(orig);
    int j = findVertexIdx(dest);
    cout << "Initial point: " << i << endl;
    cout << "Final point: " << j << endl;
    if (i == -1 || j == -1 || getW(i, j) == INF)  // missing or disconnected
        return res;

    res.push_back(vertexSet[i]->info);

    while(i != j){
        i = getP(i, j);
        if(i < 0)
            break;
        res.push_back(vertexSet[i]->info);
    }

    return res;
    /*vector<T> res;
    int indexOrigem, indexDestino;
    for (int i = 0 ; i < getNumVertex() ; i++) {
        if (vertexSet[i]->info == orig)
            indexOrigem = i;
        else if (vertexSet[i]-> info == dest)
            indexDestino = i;
    }
    while (predecessores[indexOrigem][indexDestino] != vertexSet[indexOrigem]) {
        res.emplace(res.begin(), predecessores[indexOrigem][indexDestino]->info);
        for (int j = 0 ; j < getNumVertex() ; j++) {
            if (vertexSet[j]->info == predecessores[indexOrigem][indexDestino]->info) {
                indexDestino = j;
                break;
            }
        }
    }
    res.push_back(dest);
    res.insert(res.begin(), orig);
    return res;*/
}

template <class T>
std::vector<Vertex<T> *> Graph<T>::NearestNeighborFloyd(const T &origin){
    floydWarshallShortestPath();

    vector<Vertex<T> *> result;
    int inicial = findVertexIdx(origin);
    MutablePriorityQueue<Vertex<T>> Q;

    for(Request<T>* request : company.getRequests()) {
        Vertex<T>* vertexRes = findVertex(request->getStore()->getNodeID);
        Vertex<T>* vertexCli = findVertex(request->getClient()->getNodeID());
        vertexRes->setDist(getW(inicial, findVertexIdx(request->getStore()->getNodeID())));
        vertexCli->setDist(getW(inicial, findVertexIdx(request->getClient()->getNodeID())));
        Q.insert(vertexRes);
        Q.insert(vertexCli);
    }
    result.push_back(findVertex(origin));
    while(!Q.empty()) {
        Vertex<T> *vertex = Q.extractMin();
        int vertexIndex = findVertexIdx((vertex->getInfo()));
        for(Request<T>* request : company.getRequests()){
            if(vertex->getInfo()==request->getStore()->getNodeID()){
                cout<<request->getStore()->getName()<<endl;
            }
            if(vertex->getInfo() == request->getClient()->getNodeID()){
                cout<<request->getClient()->getName();
                if(request->hasCar()){
                    cout << " Requisitado"<<endl;
                }
                else{
                    cout << " NAO requisitado"<<endl;
                }
            }
        }
        vector<T> path = getfloydWarshallPath((result.back()->getInfo()), (vertex->getInfo()));
        for(unsigned i = 1; i < path.size(); i++){
            result.push_back(findVertex(path.at(i)));
        }
        for(Request<T>* request : company.getRequests()){
            int a=getW(vertexIndex, findVertexIdx(request->getClient()->getNodeID()));
            int b=getW(vertexIndex, findVertexIdx(request->getStore()->getNodeID()));
            if(a>b){
                vertex->setDist(getW(vertexIndex, findVertexIdx(request->getClient()->getNodeID())));
            }
            else{
                vertex->setDist(getW(vertexIndex, findVertexIdx(request->getStore()->getNodeID())));
            }
        }
    }

    return result;
}


/**************************************************************************************************************************/

template <class T>
Graph<T>* Graph<T>::invert(){
    Graph<T> *newGraph = new Graph<T>;
    Vertex<T> *vertex;
    for(Vertex<T> * v: this->getVertexSet()) {
        vertex = new Vertex<T>(v->getInfo(), v->getX(), v->getY());
        newGraph->addVertex(vertex);

    }
    int j=0;
    for(auto v: this->getVertexSet())
        for(Edge<T> e: v->getAdj()) {
            newGraph->addEdge(j,e.getDest()->getInfo(), v->getInfo());
            j++;
        }

    return newGraph;
}

#endif //E_ESTAFETAS_GRAPH_H
