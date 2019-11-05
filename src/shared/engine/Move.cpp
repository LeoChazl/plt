#include "../engine.h"
#include "../state.h"

using namespace engine;

// Constructor

Move::Move(state::MobileEntity& selectedUnit, state::Position& destination): selectedUnit(selectedUnit), destination(destination){
}

// Function

void Move::execute(state::State& state){

}