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
    //Engine Init
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

    //Test if the "initplayer" function on the engine init is the same as copiedEngine
        //x position
    BOOST_CHECK_EQUAL(engine.getState().getPlayerList()[0]->getMobileEntityList()[0]->getX(),copiedEngine.getState().getPlayerList()[0]->getMobileEntityList()[0]->getX());
    BOOST_CHECK_EQUAL(engine.getState().getPlayerList()[1]->getMobileEntityList()[0]->getX(),copiedEngine.getState().getPlayerList()[1]->getMobileEntityList()[0]->getX());
        //Health
    BOOST_CHECK_EQUAL(engine.getState().getPlayerList()[1]->getMobileEntityList()[0]->getHealth(),copiedEngine.getState().getPlayerList()[1]->getMobileEntityList()[0]->getHealth());
    BOOST_CHECK_EQUAL(engine.getState().getPlayerList()[1]->getMobileEntityList()[0]->getHealth(),copiedEngine.getState().getPlayerList()[1]->getMobileEntityList()[0]->getHealth());
        //Damage
    BOOST_CHECK_EQUAL(engine.getState().getPlayerList()[1]->getMobileEntityList()[0]->getDamage(),copiedEngine.getState().getPlayerList()[1]->getMobileEntityList()[0]->getDamage());
    BOOST_CHECK_EQUAL(engine.getState().getPlayerList()[1]->getMobileEntityList()[0]->getDamage(),copiedEngine.getState().getPlayerList()[1]->getMobileEntityList()[0]->getDamage());


    copiedEngine.getState().getPlayerList()[0]->getMobileEntityList()[0]->setX(0);
    copiedEngine.getState().getPlayerList()[0]->getMobileEntityList()[0]->setY(0);

    copiedEngine.getState().getPlayerList()[1]->getMobileEntityList()[0]->setX(0);
    copiedEngine.getState().getPlayerList()[1]->getMobileEntityList()[0]->setY(1);

    /***********************************/
    /*"attackableEnemies" function test*/
    /***********************************/
    std::vector<state::Position> attackableEnemiesPositionList;
    //Store in  "attackableEnemiesPositionList" all attackable ennemeies positions
    attackableEnemiesPositionList=deepAi.attackableEnemies(copiedEngine,0,1);

    cout<<"attackable Enemies Position List size = "<<attackableEnemiesPositionList.size()<<endl;
    if(attackableEnemiesPositionList.size()!=0){
        BOOST_CHECK_EQUAL(attackableEnemiesPositionList[0].getX(),0);
        BOOST_CHECK_EQUAL(attackableEnemiesPositionList[0].getY(),0);
    }

    /**********************************/
    /*"optimalMoveCoord" function test*/
    /**********************************/
    std::vector<state::Position> optimalMoveCoord;
    optimalMoveCoord=deepAi.optimalMoveCoord(copiedEngine,0,1);

    /*************************************/
    /*"storeAttackCommands" function test*/
    /*************************************/
    std::vector<std::shared_ptr<engine::Command>> possibleCommandList;
    BOOST_CHECK_EQUAL(possibleCommandList.size(),0);

    deepAi.storeAttackCommands(copiedEngine,attackableEnemiesPositionList,possibleCommandList,0);
    BOOST_CHECK_EQUAL(possibleCommandList.size(),1);

    /***********************************/
    /*"storeMoveCommands" function test*/
    /***********************************/
    deepAi.storeMoveCommands(copiedEngine,attackableEnemiesPositionList,possibleCommandList,0);
    BOOST_CHECK_EQUAL(possibleCommandList.size(),2);

    /***************************************/
    /*"storeEndActionCommand" function test*/
    /***************************************/
    deepAi.storeEndActionCommand(copiedEngine,possibleCommandList,0);
    BOOST_CHECK_EQUAL(possibleCommandList.size(),3);




}