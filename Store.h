//
// Created by pedro on 18/05/2021.
//

#ifndef E_ESTAFETAS_STORE_H
#define E_ESTAFETAS_STORE_H


#include <string>

using namespace std;

template <class T>
class Store {
    string name;
    T nodeID;  //Location
    bool repeated;
public:
    Store(string name, T nodeID) {
        this->name = name;
        this->nodeID = nodeID;

    }

    T getNodeID() {
        return nodeID;
    }

    void setNodeID(T &nodeID) {
        this->nodeID = nodeID;
    }

    string getName() {
        return name;
    }

    bool getRepeated(){
        return repeated;
    }

    void setRepeated(bool rep){
        this->repeated = rep;
    }
};




#endif //E_ESTAFETAS_STORE_H
