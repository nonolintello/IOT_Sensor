//
// Created by Sengel Noé on 22/09/2023.
//
#include "Server.h"
#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <cmath>
#include "ctime"

using namespace std;


Server::Server (){
    this->nbrOfSensors=0;
    this->consolActivation= true;
    this->logActivation= true;
}
Server::Server (const Server& serv){
    this->nbrOfSensors=serv.nbrOfSensors;
    this->consolActivation=serv.consolActivation;
    this->logActivation=serv.logActivation;
}
Server::Server (int sensors, bool console, bool log){
    this->nbrOfSensors=sensors;
    this->consolActivation= console;
    this->logActivation= log;
}
Server::~Server(){
    //cout << "Objet Serveur detruit" <<endl;
}
Server& Server:: operator=(const Server& serv){
    if(this != &serv){ //on évite l'autoaffectation
        this->nbrOfSensors=serv.nbrOfSensors;
        this->consolActivation=serv.consolActivation;
        this->logActivation=serv.logActivation;
    }
    return *this;
}
mutex consoleMutex;
 void Server::consoleWrite(string dataSens) {
    lock_guard<mutex> lock(consoleMutex);
    char firstChar= dataSens[0];
    string color, resetColor="\x1B[0m";
    switch (firstChar) {
        case 'S':
            color= "\x1B[31m";
            break;
        case 'T':
            color="\x1B[32m";
            break;
        case 'H' :
            color =  "\x1B[33m";
            break;
        case 'L':
            color ="\x1B[34m";
            break;
        default :
            color = "\x1B[0m";
            break;
    }
    string sensorId;
    string sensordata;
    convData(dataSens,sensorId,sensordata);
    cout << color << sensorId << " : " << sensordata << resetColor << endl;
}

void Server::operator<<(const string& dataSens){
    if(this->logActivation){
        this->fileWrite(dataSens);
    } else{
        cout << "Log isn't activated" << endl;
    }
    if (this->consolActivation){
        this->consoleWrite(dataSens);
    } else {
        cout << "Consol isn't activated" << endl;
    }
}


void convData(const string& data,string& sensorId,string& sensorData) {
    // Chercher la position du symbole #
    size_t pos = data.find('#');
    // Vérifier si le symbole # a été trouvé
    if (pos != string::npos) {
        // Extraire la sous-chaîne avant le #
        sensorId = data.substr(0, pos);
        // Extraire la sous-chaîne après le #
        sensorData = data.substr(pos + 1);
    } else {
        // Gérer le cas où le symbole # n'est pas présent
        sensorId = "";
        sensorData = data;
    }
}
void Server::fileWrite(const string& dataSens) {
    string sensorId;
    string sensordata;
    convData(dataSens,sensorId,sensordata);
    string file = "SensorData/"+sensorId.substr(0, sensorId.size() - 1)+"/";
    string const fileName = file + sensorId + ".log";
    ofstream monFlux(fileName.c_str(),std::ios_base::app);
    if(monFlux){
        time_t t = time(nullptr);
        tm localTime = *std::localtime(&t);
        monFlux << (localTime.tm_mon + 1) << "-" << localTime.tm_mday << " at " << localTime.tm_hour << "h" << localTime.tm_min << "m" << localTime.tm_sec << "s : "<< sensordata << endl;

    } else {
        cout<< "Erreur fichier"<<endl;
    }
}

std::ostream& operator<<(std::ostream& os, const Server& server){
    string cons="off",log="off";
    if(server.consolActivation){
        cons="on";
    }
    if(server.logActivation){
        log="on";
    }
    os << "Nombre de sensors : " << server.nbrOfSensors << "  |  Console " << cons<< "  |  Log "  << log << endl;
    return os;
}



