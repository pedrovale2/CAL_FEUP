//
// Created by pedro on 18/05/2021.
//

#ifndef E_ESTAFETAS_COMPANY_H
#define E_ESTAFETAS_COMPANY_H


#include "Client.h"
#include "Request.h"
#include "Store.h"
#include "Car.h"
#include <vector>


using namespace std;

template <class T>
class Company {
    string name;
    vector<Client<T>*> clients;
    vector<Request<T>*> requests;
    vector<Store<T>*> stores;
    vector<Car<T>*> cars;

    T parque;

public:
    Company(string name) {
        this->name = name;

    }

    void sortCars(){
        sort(cars.begin(), cars.end());
    }

    void setParque(T parque){
        this->parque = parque;
    }

    string getName(){
        return name;
    }

    void setCars(vector<Car<T>*> Cars){
        this->cars = Cars;
    }
    vector<Car<T>*> getCars(){
        return cars;
    }

    vector<Client<T>*> getClients() const {
        return clients;
    }

    vector<Request<T>*> getRequests() const {
        return requests;
    }

    vector<Store<T>*> getStores() const {
        return stores;
    }

    void setClients(vector<Client<T>*> clients) {
        this->clients = clients;
    }

    void setRequests(vector<Request<T>*> requests) {
        this->requests = requests;
    }

    void setStores(vector<Store<T>*> stores) {
        this->stores = stores;
    }

    T getParque() {
        return parque;
    }

    int getNumClients(){
        return clients.size();
    }

    int getNumStores(){
        return stores.size();
    }

    int getNumCars(){
        return cars.size();
    }

    Request<T>* findRequest(T info) {
        for (Request<T>* request : requests) {
            if(request->getClient()->getNodeID() == info)
                return request;
            else if(request->getStore()->getNodeID()==info)
                return request;
        }
        return nullptr;
    }

    Car<T>* findCar(T info) {
        for (Car<T>* car : cars) {
            if(car->getPosition() == info)
                return car;
        }
        return nullptr;
    }

    Store<T>* findStore(T info) {
        for (Store<T>* store : stores) {
            if(store->getNodeID() == info)
                return store;
        }
        return nullptr;
    }

    Client<T>* findClient(T info) {
        for (Client<T>* client : clients) {
            if(client->getNodeID() == info)
                return client;
        }
        return nullptr;
    }

    void eraseRequest(Request<T>* req) {
        /*typename vector<Request<T>*>::iterator it = requests.begin();
        while (it != requests.end()){

            if( ((*it)->getClient()->getNodeID() == c) && ((*it)->getStore()->getNodeID() == s)){
                cout << (*it)->getClient()->getNodeID() << endl;
                requests.erase(it);
                break;
            }
            it++;
        }*/
        requests.erase(find(requests.begin(), requests.end(), req));
    }
};


#endif //E_ESTAFETAS_COMPANY_H
