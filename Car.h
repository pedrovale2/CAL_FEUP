//
// Created by pedro on 18/05/2021.
//

#ifndef E_ESTAFETAS_CAR_H
#define E_ESTAFETAS_CAR_H

#include <string>
#include <vector>

using namespace std;


template <class T>
class Car {
    int battery;
    T position;
    string name;
    bool repeated;

public:

    Car(string name, int battery, T position){
        this->name = name;
        this->battery = battery;
        this->position = position;


    }



    string getName(){
        return name;
    }

    void setName(string &name){
        this->name = name;
    }

    int getBattery() {
        return battery;
    }

    void setBattery(int &battery){
        this->battery = battery;
    }


    T getPosition(){
        return position;
    }

    void setPosition( T &position){
        this->position = position;
    }

    bool getRepeated(){
        return repeated;
    }

    void setRepeated(bool rep){
        this->repeated = rep;
    }

};







#endif //E_ESTAFETAS_CAR_H
