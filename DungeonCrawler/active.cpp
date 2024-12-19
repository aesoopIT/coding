#include "active.h"
#include <algorithm>
#include <iostream>
#include <ostream>

Active::Active()
{

}


void Active::attach(Passive* observer)
{
    //std::cout << "Observers.clear Aufgerufen" << std::endl;
    observers.clear();

    if (observer && std::find(observers.begin(), observers.end(), observer) == observers.end()) {
        observers.push_back(observer);
        std::cout << "Attached observer: " << observer << std::endl; // Debug-Ausgabe
    } else {
        std::cerr << "Error: Observer already in Vector" << std::endl;
    }

    // Alle observer Ausgeben, Debug-Hilfe
    int counter = 1;
    for (auto observer : observers) {
        std::cout << "Observer " << counter << ": " << observer << std::endl;
        counter++;
    }
}

void Active::detach(Passive* observer)
{
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    std::cout << "Detached observer\n"; // Debug-Ausgabe
}

void Active::activate()
{
    for (Passive* observer : observers) {
        if (observer) {
            std::cout << "Notifying observer (" << observer << "): ";     // Debuggin Hilfe
            observer->notify();
        } else {
            std::cerr << "Error: Null observer" << std::endl;   // Debuggin Hilfe
        }
    }
}

bool Active::isObserverAttached(Passive *observer) const
{
    return std::find(observers.begin(), observers.end(), observer) != observers.end();
}

/*
void Active::attach(Passive* observer)
{
    for(auto observers:observers){
        if(observers==observer)
            return;
    }
    observers.push_back(observer);
}

void Active::detach(Passive* pass)
{
    for( auto it=observers.begin();it!=observers.end();it++){
        if(*it==pass){
            observers.erase(it);
            return;
        }
    }
}

void Active::activate()
{
    for(auto passObj:observers){
        if(passObj)
            passObj->notify();
    }
}
*/
