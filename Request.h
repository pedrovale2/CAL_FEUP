//
// Created by pedro on 18/05/2021.
//

#ifndef E_ESTAFETAS_REQUEST_H
#define E_ESTAFETAS_REQUEST_H



template <class T>
class Request {
    Store<T>* store;
    Client<T>* client;
    Car<T>* car;
    long int StoreLocation;
    long int ClientLocation;
    bool associated;

public:
    Request(Client<T>* client, Store<T>* store ) {
        this->client = client;
        this->store = store;

        this->ClientLocation = client->getNodeID();
        this->StoreLocation = store->getNodeID();
    }
    void setAssociated( bool ass){
        this->associated = ass;
    }

    bool getAssociated(){
        return associated;
    }

    Client<T>* getClient() {
        return client;
    }

    Store<T>* getStore() {
        return store;
    }

    bool hasCar() {
        return associated;
    }

    void setcar(Car<T>* car) {
        this->car = car;
    }

    Car<T>* getCar() {
        return car;
    }
};


#endif //E_ESTAFETAS_REQUEST_H
