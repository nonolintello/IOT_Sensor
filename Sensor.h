//
// Created by Sengel Noé on 06/10/2023.
//
#ifndef UNTITLED_SENSOR_H
#define UNTITLED_SENSOR_H

#include <iostream>
#include <string>
#include <random>
using namespace std;

template<class T> class Sensor{
    protected:
        string id;
        T valSense;
        T min;
        T max;
    public:
        T sendData(){
            return valSense;
        }
        virtual T aleaGenVal()=0;
        void addId(int ident){
            id = id + to_string(ident);
        };
        string sendId(){return id;};
        friend std::ostream& operator<<(std::ostream& os, const Sensor<T>& sensor){
            os <<"id : " << sensor.id << "  | val : "<< sensor.valSense << endl;
            return os;
        };
};

class IntSensor : public Sensor<int> {
    public :
        virtual void no_instance()=0;
        int aleaGenVal() {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<int> dis(this->min, this->max);
            valSense= dis(gen);
            return dis(gen);
    };
};
class FloatSensor : public Sensor<float> {
    public :
        virtual void no_instance()=0;
        float aleaGenVal() {
            random_device rd;
            mt19937 gen(rd());
            uniform_real_distribution<float> dis(this->min, this->max);
            valSense= dis(gen);
            return dis(gen);
    };
};

class Light : public IntSensor {
public :
     void no_instance() {
        cout << "";
    }

    Light() {
        id = "Light";
        min = 0;
        max = 1;
        valSense = 0;
    }
};
class Sound : public IntSensor {
public :
     void no_instance()  {
        cout << "";
    }
    Sound() {
        id = "Sound";
        min = 0;
        max = 100;
        valSense = 0;
    }
};
class Humidity : public FloatSensor{
public :
     void no_instance() {
        cout << "";
    }
    Humidity(){
        id = "Humidity";
        min = 0.0;
        max = 100.0;
        valSense = 0.0;
}
};
class Temperature : public FloatSensor {
public :
     void no_instance()  {
        cout << "";
    }

    Temperature() {
        id = "Temperature";
        min = -20.0;
        max = 40.0;
        valSense = 0.0;
    }
};

#endif


