#include <iostream>
#include "Scheduler.h"


using namespace std;
int main() {
    bool choice;
    cout << endl << "Par défaut :  1 capteur de chaque type avec les délais de mesures suivants (en seconde) | " << "\x1B[33m" << "humidité[3]  " <<"\x1B[32m"<<"température[5]  " <<"\x1B[31m"<<"son[6]  "<<"\x1B[34m"<< "lumière[8] " << "\x1B[0m" << "| Log et Console Activé"<< endl<<endl;
    cout << "Bienvenue dans cet écosystème IOT, voulez vous configurer le nombre de capteur ou garder la configuration par défaut (1 oui - 0 défault )"<<endl ;
    choice= getUserInput(0,1);
    if(choice){
        Scheduler scheduler = Scheduler(1);
        scheduler.Schedule();

    } else{
        Scheduler scheduler = Scheduler();
        scheduler.Schedule();
    }
    return 0;
}

