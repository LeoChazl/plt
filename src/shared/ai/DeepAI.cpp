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


/**sore all attackable positions where ennemies are standed
 *  Arguments: -> reference "copied Engine"
 *             -> the unit index in the mobile entity list associated to a player
 *             -> the artificial intelligence ID - 1
 *  Return: list of the attackable positions where ennemies are standed
 */ 
std::vector<state::Position> DeepAI::attackableEnemies (engine::Engine& copiedEngine, int aiUnitIndex, int artificalIntelligenceID){
    std::vector<state::Position> attackableEnemiesPositionList;
    std::vector<state::Position> allowedAttackPosition=copiedEngine.getState().getPlayerList()[artificalIntelligenceID]->getMobileEntityList()[aiUnitIndex]->allowedAttack(copiedEngine.getState());
    int x,y;
    for (int i = 0; i < allowedAttackPosition.size(); i++)
    {
        x=allowedAttackPosition[i].getX();
        y=allowedAttackPosition[i].getY();
        if(copiedEngine.getState().isOccupied(x,y)){
            attackableEnemiesPositionList.push_back(allowedAttackPosition[i]);
        }
    }
    return attackableEnemiesPositionList;
    
}


/**recover all optimal move position after using AStar algorithm
 *  Arguments: -> reference "copied Engine"
 *             -> the unit index in the mobile entity list associated to a player
 *             -> the artificial intelligence ID - 1
 *  Return: list of optimal coord where the unit can move in order to reach the nearest enemy
 */ 
std::vector<state::Position> DeepAI::optimalMoveCoord (engine::Engine& copiedEngine, int aiUnitIndex, int artificialIntelligenceID){
    //change with the ASTAR Algorithm results
    std::vector<state::Position> optimalMoveCoord=copiedEngine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[aiUnitIndex]->allowedMove(copiedEngine.getState());
    return optimalMoveCoord;
}


/**store all possible attack commands in a list
 * 
 *  No Return
 */
void DeepAI::storeAttackCommands (engine::Engine& engine, std::vector<state::Position>& attackableEnemiesPositionList, std::vector<std::shared_ptr<engine::Command>>& possibleCommandList, int aiUnitIndex){
    int x,y;
    for (int i = 0; i < attackableEnemiesPositionList.size(); i++)
    {
        x=attackableEnemiesPositionList[i].getX();
        y=attackableEnemiesPositionList[i].getY();
        Attack attack(*engine.getState().ptrReferenceToPlayingEntity(aiUnitIndex), *engine.getState().getMobileEntity(x,y)); //Initialize the Attack constrctor with attacker and target
		shared_ptr<Command> ptr_attack(new Attack(attack));
        possibleCommandList.push_back(ptr_attack);
    }
}

/**store all possible move commands in the possible command list
 * 
 *  No return
 */
void DeepAI::storeMoveCommands (engine::Engine& copiedEngine, std::vector<state::Position>& optimalMoveCoord, std::vector<std::shared_ptr<engine::Command>>& possibleCommandList, int aiUnitIndex){
    
    for (int i = 0; i < optimalMoveCoord.size(); i++)
    {
        Move movement(*copiedEngine.getState().ptrReferenceToPlayingEntity(aiUnitIndex), optimalMoveCoord[i]);//Initialize the movement pointor with the unit to move and the position to reach
		shared_ptr<Command> ptr_move(new Move(movement));
        possibleCommandList.push_back(ptr_move);
    }
}

/**store End Action command in the possible command list
 * 
 *  No Return
 */
void DeepAI::storeEndActionCommand(engine::Engine& copiedEngine, std::vector<std::shared_ptr<engine::Command>>& possibleCommandList, int aiUnitIndex){
    EndEntityRound endEntityRound(*copiedEngine.getState().ptrReferenceToPlayingEntity(aiUnitIndex));
	shared_ptr<Command> ptr_endEntityRound(new EndEntityRound(endEntityRound));
    possibleCommandList.push_back(ptr_endEntityRound);
}





