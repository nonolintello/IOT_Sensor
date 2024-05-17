//
// Created by Sengel Noé on 22/09/2023.
//

#ifndef UNTITLED_SERVER_H
#define UNTITLED_SERVER_H

#include <iostream>
#include <string>

using namespace std;

class Server {
    private :
    int nbrOfSensors;
    bool consolActivation,logActivation;
    static void fileWrite(const string& dataSens);
    static void consoleWrite(string dataSens);
    public :
    Server ();
    Server ( const Server& serv);
    Server (int sensors, bool console, bool log);
    ~Server();
    Server& operator=(const Server& serv);
    void operator<<(const string& dataSens);

    friend std::ostream& operator<<(std::ostream& os, const Server& server);
};

void convData(const string& data,string& sensorId,string& sensorData);

#endif //UNTITLED_SERVER_H
