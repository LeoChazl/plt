#include "../state.h"

using namespace state;
using namespace std;

StateEvent::StateEvent(StateEventID stateEventID){
    this->stateEventID = stateEventID;
}

StateEventID StateEvent::getStateEventID(){
    return stateEventID;
}

StateEvent::~StateEvent(){

}