#include "../engine.h"
#include "../state.h"
#include "../ai.h"
#include <iostream>
#include <unistd.h>

using namespace state;
using namespace engine;
using namespace std;
using namespace ai;


RandomAI::RandomAI(){
    
}


void RandomAI::run (engine::Engine& engine){

    // initialize random seed: 
    srand (time(NULL));
    // generate number between 1 and command list size 
    /*int randomCommand = rand() % aiCommandList.size();

    aiCommandList[randomCommand]->execute(engine.getState());*/
}

