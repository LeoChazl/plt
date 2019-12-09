#include "../engine.h"
#include "../state.h"
#include "../ai.h"
#include <iostream>
#include <unistd.h>

using namespace state;
using namespace engine;
using namespace std;
using namespace ai;


// Constructor
DeepAI::DeepAI(int AiID):depth(depth){
    artificialIntelligenceID=AiID;
}

//Functions

void DeepAI::run (engine::Engine& engine){
}

/**copy Engine object in another engine Object
 *  Arguments: -> reference "engine" to copy
 *             -> reference "copiedEngine"(the copied object)
 *  No Return
 */
void DeepAI::copyEngine (engine::Engine& engine,engine::Engine& copiedEngine){
    copiedEngine.setCurrentState(engine.getState());
    copiedEngine.setCurrentCommands(move(engine.getCurrentCommands()));
    copiedEngine.setChangeRound(engine.getChangeRound());
    copiedEngine.setStop(engine.getStop());
}

