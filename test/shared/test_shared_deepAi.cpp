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
    class DeepAiNode;
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

/*--------------------------------------------------------------------------*/

    /***************************************/
    /*"createNodes" function test*/
    /***************************************/
    //Init Parent Node
    ai::DeepAiNode headNode;
    headNode.setScore(30);


    //Init childNode
    DeepAiNode childNode;
    childNode.setPtrParent(&headNode);
    childNode.setExecutedCommand(possibleCommandList[0].get());//with the "get" function I just recover the adress of the pointor without shared pointor specification and proprities
    

    
    //Create a chained list and store it in the parent "childDeepAiNodeList" attribut
    BOOST_CHECK_EQUAL(headNode.getChildDeepAiNodeList().size(),0);
    //deepAi.createChildNodes(copiedEngine,headNode,possibleCommandList);

    //BOOST_CHECK_EQUAL(headNode.getChildDeepAiNodeList().size(),possibleCommandList.size());
    //BOOST_CHECK_EQUAL(headNode.getChildDeepAiNodeList()[0]->getPtrParent(),headNode.getChildDeepAiNodeList()[1]->getPtrParent());

    childNode.getExecutedCommand()->execute(copiedEngine.getState());

    std::vector<ai::DeepAiNode*> childNodesList= headNode.getChildDeepAiNodeList();
    for (uint i = 0; i < possibleCommandList.size(); i++)
    {
        DeepAiNode childNode;
        DeepAiNode* ptrChildNode;
        childNode.setPtrParent(&headNode);
        childNode.setExecutedCommand(possibleCommandList[i].get());
        childNodesList.push_back(&childNode);
    }
    headNode.setChildDeepAiNodeList(childNodesList);

    /***************************************/
    /*"createTheTree" function test*/
    /***************************************/
    for (uint i = 0; i < headNode.getChildDeepAiNodeList().size(); i++)
    {
        deepAi.copyEngine(engine,copiedEngine);
        headNode.getChildDeepAiNodeList()[i]->getExecutedCommand()->execute(copiedEngine.getState());
        //possibleCommandList[i]->execute(copiedEngine.getState());
        
        /***********************************/
        /*"attackableEnemies" function test*/
        /***********************************/
        std::vector<state::Position> attackableEnemiesPositionList;
        attackableEnemiesPositionList=deepAi.attackableEnemies(copiedEngine,0,1);

        /**********************************/
        /*"optimalMoveCoord" function test*/
        /**********************************/
        std::vector<state::Position> optimalMoveCoord;
        optimalMoveCoord=deepAi.optimalMoveCoord(copiedEngine,0,1);

        /*************************************/
        /*"storeAttackCommands" function test*/
        /*************************************/
        std::vector<std::shared_ptr<engine::Command>> possibleCommandList2;
        BOOST_CHECK_EQUAL(possibleCommandList2.size(),0);

        deepAi.storeAttackCommands(copiedEngine,attackableEnemiesPositionList,possibleCommandList2,0);
        BOOST_CHECK_EQUAL(possibleCommandList2.size(),1);

        /***********************************/
        /*"storeMoveCommands" function test*/
        /***********************************/
        deepAi.storeMoveCommands(copiedEngine,attackableEnemiesPositionList,possibleCommandList2,0);
        BOOST_CHECK_EQUAL(possibleCommandList2.size(),2);

        /***************************************/
        /*"storeEndActionCommand" function test*/
        /***************************************/
        deepAi.storeEndActionCommand(copiedEngine,possibleCommandList2,0);
        BOOST_CHECK_EQUAL(possibleCommandList2.size(),3);

        //deepAi.createChildNodes(copiedEngine,*headNode.getChildDeepAiNodeList()[i],possibleCommandList2);
        std::vector<ai::DeepAiNode*> childNodesList2= headNode.getChildDeepAiNodeList();
        DeepAiNode parentNode;
        parentNode.setPtrParent(childNodesList2[i]->getPtrParent());
        parentNode.setChildDeepAiNodeList(childNodesList2[i]->getChildDeepAiNodeList());
        parentNode.setExecutedCommand(childNodesList2[i]->getExecutedCommand());
        parentNode.setScore(childNodesList2[i]->getScore());
        //std::vector<ai::DeepAiNode*> childNodesList= parentNode.getChildDeepAiNodeList();
        for (uint i = 0; i < possibleCommandList2.size(); i++)
        {
            DeepAiNode* ptrChildNode;
            ptrChildNode=new DeepAiNode;

            ptrChildNode->setPtrParent(&parentNode);
            ptrChildNode->setExecutedCommand(possibleCommandList2[i].get());
            childNodesList2.push_back(ptrChildNode);
        }
        
        BOOST_CHECK_EQUAL(parentNode.getChildDeepAiNodeList().size(),headNode.getChildDeepAiNodeList()[i]->getChildDeepAiNodeList().size());
        BOOST_CHECK_EQUAL(headNode.getChildDeepAiNodeList()[i]->getChildDeepAiNodeList().size(),0);

        parentNode.setChildDeepAiNodeList(childNodesList2);
        BOOST_CHECK_EQUAL(parentNode.getChildDeepAiNodeList().size(),headNode.getChildDeepAiNodeList()[i]->getChildDeepAiNodeList().size());
        BOOST_CHECK_EQUAL(headNode.getChildDeepAiNodeList()[i]->getChildDeepAiNodeList().size(),6);


    

    }
    
}