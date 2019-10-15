#include "../state.h"
#include <algorithm>

using namespace state;
using namespace std;

Observer::Observer(){

}

void Observer::registerObserver(IObserver* obs){
    observers.push_back(obs);
}

void Observer::unregisterObserver(IObserver* obs){
    observers.erase(remove(observers.begin(), observers.end(), obs), observers.end());
}

void const Observer::notifyObservers(const StateEvent& e, State& state){

}

Observer::~Observer(){

}