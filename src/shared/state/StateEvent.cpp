#include "../state.h"

using namespace state;
using namespace std;

// Constructor

StateEvent::StateEvent(StateEventID stateEventID){
    this->stateEventID = stateEventID;
}


// Getter and setters

StateEventID StateEvent::getStateEventID(){
    return stateEventID;
}

string StateEvent::getActionText(){
    return actionText;
}

void StateEvent::setActionText(string actionText){
    this->actionText = actionText;
}