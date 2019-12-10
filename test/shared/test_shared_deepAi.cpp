#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"
#include "../../src/shared/engine.h"
#include "../../src/shared/ai.h"
#include "../../src/client/render.h"


#include <vector>
#include <unistd.h>


#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
using namespace state;
using namespace render;
using namespace engine;
using namespace ai;

namespace ai{
    class DeepAI;
}

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
    //Engine Side
    Engine engine;
    engine.getState().initPlayers();
  
    /**************************/
    /*"copyEngine" function test*/
    /**************************/

    engine.setChangeRound(true);
    engine.setStop(true);

    ai::DeepAI deepAi(1);
    Engine copiedEngine;
    //copy engine
    deepAi.copyEngine(engine,copiedEngine);
    
    state::State state;
    state.setEndGame(true);
    copiedEngine.setCurrentState(state);
    //Test if "engine" and copiedEngine" don't have any link
    BOOST_CHECK_EQUAL(engine.getState().getEndGame(),false);
    BOOST_CHECK_EQUAL(copiedEngine.getState().getEndGame(),true);

    /***********************************/
    /*"attackableEnemies" function test*/
    /***********************************/
    std::vector<state::Position> attackableEnemiesPositionList;
    //Store in  "attackableEnemiesPositionList" all attackable ennemeies positions
    attackableEnemiesPositionList=deepAi.attackableEnemies(copiedEngine,1,1);
    if(attackableEnemiesPositionList.size()!=0){
        BOOST_CHECK_EQUAL(attackableEnemiesPositionList[0].getX(),0);
        BOOST_CHECK_EQUAL(attackableEnemiesPositionList[0].getY(),0);
    }

    /**********************************/
    /*"optimalMoveCoord" function test*/
    /**********************************/
    std::vector<state::Position> optimalMoveCoord;
    optimalMoveCoord=deepAi.optimalMoveCoord(copiedEngine,1,1);

    /*************************************/
    /*"storeAttackCommands" function test*/
    /*************************************/
    std::vector<std::shared_ptr<engine::Command>> possibleCommandList;
    BOOST_CHECK_EQUAL(possibleCommandList.size(),0);

    deepAi.storeAttackCommands(copiedEngine,attackableEnemiesPositionList,possibleCommandList,0);
    BOOST_CHECK_EQUAL(possibleCommandList.size(),0);

    /***********************************/
    /*"storeMoveCommands" function test*/
    /***********************************/
    deepAi.storeMoveCommands(copiedEngine,attackableEnemiesPositionList,possibleCommandList,0);
    BOOST_CHECK_EQUAL(possibleCommandList.size(),0);

    /***********************************/
    /*"storeEndActionCommand" function test*/
    /***********************************/
    deepAi.storeEndActionCommand(copiedEngine,possibleCommandList,0);
    BOOST_CHECK_EQUAL(possibleCommandList.size(),1);




}