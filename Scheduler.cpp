//
// Created by Sengel Noé on 20/10/2023.
//

#include "Scheduler.h"
#include "Sensor.h"





Scheduler::~Scheduler() {
    //appel auto du destructeur de Server et de vector
}

Scheduler::Scheduler(){
    serv= Server();
    Humidity h;
    h.addId(0);
    Sound s;
    s.addId(0);
    Light l;
    l.addId(0);
    Temperature t;
    t.addId(0);
    hSensors.push_back(h);
    sSensors.push_back(s);
    lSensors.push_back(l);
    tSensors.push_back(t);
    hRefreshTime= 3;
    tRefreshTime=5;
    sRefreshTime =6;
    lRefreshTime=8;
}
Scheduler::Scheduler(int a) {
    int minSens=1,maxSens=10;
    int hNb,lNb,sNb,tNb,consA,fileA;
    cout << "Nombre de capteur d'humidité , ";
    hNb= getUserInput(minSens,maxSens);
    cout << "Temps entre les mesures d'humidité (s) , ";
    hRefreshTime = getUserInput(1,60);
    cout << "Nombre de capteur de luminosité, ";
    lNb= getUserInput(minSens,maxSens);
    cout << "Temps entre les mesures de luminosité (s) , ";
    lRefreshTime = getUserInput(1,60);
    cout << "Nombre de capteur de son, ";
    sNb= getUserInput(minSens,maxSens);
    cout << "Temps entre les mesures sonores (s) , ";
    sRefreshTime = getUserInput(1,60);
    cout << "Nombre de capteur de température, ";
    tNb= getUserInput(minSens,maxSens);
    cout << "Temps entre les mesures de température (s) , ";
    tRefreshTime = getUserInput(1,60);
    cout << "Voulez-vous activez la console ?(1 oui- 0 non)  ";
    consA=getUserInput(0,1);
    cout << "Voulez-vous activez l'écriture fichier log ?(1 oui- 0 non)  ";
    fileA= getUserInput(0,1);
    this->serv= Server(hNb+lNb+sNb+tNb,consA,fileA);;
    for (int i = 0; i < hNb; ++i) {
        Humidity h;
        h.addId(i);
        this->hSensors.push_back(h);
    }
    for (int i = 0; i < lNb; ++i) {
        Light l;
        l.addId(i);
        this->lSensors.push_back(l);
    }
    for (int i = 0; i < tNb; ++i) {
        Temperature t;
        t.addId(i);
        this->tSensors.push_back(t);
    }
    for (int i = 0; i < sNb; ++i) {
        Sound s;
        s.addId(i);
        this->sSensors.push_back(s);
    }
}

void Scheduler:: Schedule(){
    vector <Humidity> h = hSensors;
    vector <Temperature> t= tSensors;
    vector <Sound> s= sSensors;
    vector <Light> l= lSensors;
    cout << endl << "Start data collecting..." << endl;
    thread hSched([this, &h]() {
        while(true){
            this_thread::sleep_for(chrono::seconds(hRefreshTime));
            this->dataProcess(h);
            }
    });
    thread tSched([this, &t]() {
        while(true){
            this_thread::sleep_for(chrono::seconds(tRefreshTime));
            this->dataProcess(t);
            }
    });
    thread sSched([this, &s]() {
        while(true){
            this_thread::sleep_for(chrono::seconds(sRefreshTime));
            this->dataProcess(s);
           }
    });
    thread lSched([this, &l]() {
        while(true){
            this_thread::sleep_for(chrono::seconds(lRefreshTime));
            this->dataProcess(l);
            }
    });
    hSched.join();
    lSched.join();
    sSched.join();
    tSched.join();
}

bool isInputValid(int userInput, int minBound, int maxBound) {
    return (userInput >= minBound && userInput <= maxBound);
}
int getUserInput(int minBound, int maxBound) {
    int userInput;

    do {
        cout << "Veuillez saisir un entier entre " << minBound << " et " << maxBound << " : ";
        if (!(cin >> userInput)) {
            cout << "Erreur : Saisie invalide. Veuillez saisir un entier valide." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (!isInputValid(userInput, minBound, maxBound)) {
            cout << "Erreur : Entier en dehors de la plage autorisée (" << minBound << "-" << maxBound << ")." << endl;
        }
    } while (!isInputValid(userInput, minBound, maxBound));

    return userInput;
}
