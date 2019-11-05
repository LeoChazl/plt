#include "../state.h"
#include <algorithm>

using namespace state;
using namespace std;

// Constructor

Observable::Observable(){

}

// Functions

/** Record a new action coming from the render in the observer list
 * 
 * param : 
 * obs -> new action to record in the list 
 */
void Observable::registerObserver(Observer* obs){
    observers.push_back(obs);
}

/** Take out the action when it has been processed
 * 
 * param :
 * obs -> the action that has been processed
 */
void Observable::unregisterObserver(Observer* obs){
    observers.erase(remove(observers.begin(), observers.end(), obs), observers.end());
}


/** Scroll through the list of observers
 * To complete when render part of the code is done
 */
void const Observable::notifyObservers(const StateEvent& stateEvent, State& state){
	for(auto observer : observers){
		observer->stateChanged(stateEvent, state);
	}
}

// Destructor

Observable::~Observable(){

}