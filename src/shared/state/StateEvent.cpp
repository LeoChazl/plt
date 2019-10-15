#include "../state.h"

using namespace state;
using namespace std;

// Constructor

StateEvent::StateEvent(StateEventID stateEventID){
    this->stateEventID = stateEventID;
}


// Getter

StateEventID StateEvent::getStateEventID(){
    return stateEventID;
}