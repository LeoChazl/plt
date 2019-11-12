#include "../render.h"
#include <algorithm>

using namespace render;
using namespace state;
using namespace engine;
using namespace std;

// Constructor

RenderObservable::RenderObservable(){

}

// Functions

/** Record a new action coming from the render in the observer list
 * 
 * param : 
 * obs -> new action to record in the list 
 */
void RenderObservable::registerRenderObserver(EngineForRenderObserver* obs){
    observers.push_back(obs);
}

/** Scroll through the list of observers
 * To complete when render part of the code is done
 */
void const RenderObservable::notifyRenderObservers(engine::EngineRenderEvent& engineRenderEvent, state::State& state, state::Position& position, shared_ptr<state::MobileEntity>& selectedMobileEntity, shared_ptr<state::MobileEntity>& targetMobileEntity){
	for(auto observer : observers){
		observer->engineRenderChanged(engineRenderEvent, state, position, selectedMobileEntity, targetMobileEntity);
	}
}

// Destructor

RenderObservable::~RenderObservable(){

}