#include "../engine.h"

using namespace engine;
using namespace std;

// Constructor

EngineRenderEvent::EngineRenderEvent(EngineRenderEventID engineRenderEventID){
    this->engineRenderEventID = engineRenderEventID;
}

// Getter

EngineRenderEventID EngineRenderEvent::getEngineRenderEventID(){
    return engineRenderEventID;
}