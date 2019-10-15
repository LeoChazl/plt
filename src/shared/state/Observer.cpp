#include "../state.h"
#include <algorithm>

using namespace state;
using namespace std;

// Constructor

Observer::Observer(){

}

// Functions

/** Record a new action coming from the render in the observer list
 * 
 * param : 
 * obs -> new action to record in the list 
 */
void Observer::registerObserver(IObserver* obs){
    observers.push_back(obs);
}

/** Take out the action when it has been processed
 * 
 * param :
 * obs -> the action that has been processed
 */
void Observer::unregisterObserver(IObserver* obs){
    observers.erase(remove(observers.begin(), observers.end(), obs), observers.end());
}


/** Scroll through the list of observers
 * To complete when render part of the code is done
 */
void const Observer::notifyObservers(const StateEvent& stateEvent, State& state){
	for(auto observer : observers){
		observer->stateChanged(stateEvent, state);
	}
}

// Destructor

Observer::~Observer(){

}