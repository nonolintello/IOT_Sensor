//
// Created by Sengel Noé on 20/10/2023.
//

#ifndef UNTITLED_SCHEDULER_H
#define UNTITLED_SCHEDULER_H

#include "Server.h"
#include "Sensor.h"
#include<list>
#include "thread"
#include "chrono"

class Scheduler {
private :
    Server serv;
    vector <Humidity> hSensors;
    vector <Temperature> tSensors;
    vector <Sound> sSensors;
    vector <Light> lSensors;
    int hRefreshTime;
    int tRefreshTime;
    int sRefreshTime;
    int lRefreshTime;
public :
    Scheduler();
    explicit Scheduler(int a);
    ~Scheduler();
    void Schedule();
    template<typename SensorType> void dataProcess(vector <SensorType>& v){
        int i=0;
        string data;
        for (SensorType& elem :v) {
            data=  elem.sendId() + "#";
            elem.aleaGenVal();
            data+= to_string(elem.sendData());
            this->serv.operator<<(data);
            i++;
        }
    };
};

bool isInputValid(int userInput, int minBound, int maxBound);
int getUserInput(int minBound, int maxBound);

#endif

