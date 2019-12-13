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
    std::shared_ptr<ai::DeepAiNode> ptrHeadNode(std::make_shared<DeepAiNode>());
    ptrHeadNode->setScore(30);


    //Init childNode
    std::shared_ptr<DeepAiNode> ptrChildNode(std::make_shared<DeepAiNode>());
    ptrChildNode->setPtrParent(ptrHeadNode);
    ptrChildNode->setExecutedCommand(possibleCommandList[0]);//with the "get" function I just recover the adress of the pointor without shared pointor specification and proprities
    

    
    //Create a chained list and store it in the parent "childDeepAiNodeList" attribut
    //BOOST_CHECK_EQUAL(ptrHeadNode->getChildDeepAiNodeList().size(),0);
    ////deepAi.createChildNodes(copiedEngine,headNode,possibleCommandList);

    //BOOST_CHECK_EQUAL(headNode.getChildDeepAiNodeList().size(),possibleCommandList.size());
    //BOOST_CHECK_EQUAL(headNode.getChildDeepAiNodeList()[0]->getPtrParent(),headNode.getChildDeepAiNodeList()[1]->getPtrParent());

    //childNode.getExecutedCommand()->execute(copiedEngine.getState());

    std::vector<std::shared_ptr<ai::DeepAiNode>> childNodesList= ptrHeadNode->getChildDeepAiNodeList();
    for (uint i = 0; i < possibleCommandList.size(); i++)
    {
        std::shared_ptr<DeepAiNode> ptrChildNode(std::make_shared<DeepAiNode>());
        ptrChildNode->setPtrParent(ptrHeadNode);
        ptrChildNode->setExecutedCommand(possibleCommandList[0]);
        childNodesList.push_back(ptrChildNode);
    }
    ptrHeadNode->setChildDeepAiNodeList(childNodesList);

    /***************************************/
    /*"createTheTree" function test*/
    /***************************************/
    for (uint i = 0; i < ptrHeadNode->getChildDeepAiNodeList().size(); i++)
    {
        deepAi.copyEngine(engine,copiedEngine);
        ptrHeadNode->getChildDeepAiNodeList()[i]->getExecutedCommand()->execute(copiedEngine.getState());
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
        std::vector<std::shared_ptr<DeepAiNode>> childNodesList2= ptrHeadNode->getChildDeepAiNodeList();
        auto ptrChildParentNode(std::make_shared<DeepAiNode>());
        ptrChildParentNode->setPtrParent(childNodesList2[i]->getPtrParent());
        ptrChildParentNode->setChildDeepAiNodeList(childNodesList2[i]->getChildDeepAiNodeList());
        ptrChildParentNode->setExecutedCommand(childNodesList2[i]->getExecutedCommand());
        ptrChildParentNode->setScore(childNodesList2[i]->getScore());
        //std::vector<ai::DeepAiNode*> childNodesList= parentNode.getChildDeepAiNodeList();
        for (uint i = 0; i < possibleCommandList2.size(); i++)
        {
            std::shared_ptr<DeepAiNode> ptrChildNode2(std::make_shared<DeepAiNode>());
            ptrChildNode2->setPtrParent(ptrHeadNode);
            ptrChildNode2->setExecutedCommand(possibleCommandList[0]);
            childNodesList2.push_back(ptrChildNode2);

            possibleCommandList2[i]->execute(copiedEngine.getState());
            ptrChildNode->setScore(deepAi.evalSituation(engine));
        }
        
        BOOST_CHECK_EQUAL(ptrChildParentNode->getChildDeepAiNodeList().size(),ptrHeadNode->getChildDeepAiNodeList()[i]->getChildDeepAiNodeList().size());
        BOOST_CHECK_EQUAL(ptrHeadNode->getChildDeepAiNodeList()[i]->getChildDeepAiNodeList().size(),0);

        //ptrChildParentNode->setChildDeepAiNodeList(childNodesList2);
        ptrHeadNode->getChildDeepAiNodeList()[i]->setChildDeepAiNodeList(childNodesList2);
        //BOOST_CHECK_EQUAL(ptrChildParentNode->getChildDeepAiNodeList().size(),ptrHeadNode->getChildDeepAiNodeList()[i]->getChildDeepAiNodeList().size());
        //BOOST_CHECK_EQUAL(headNode.getChildDeepAiNodeList()[i]->getChildDeepAiNodeList().size(),6);

    }


    /***************************************/
    /*"evalSituation" function test*/
    /***************************************/
    for (uint i = 0; i < ptrHeadNode->getChildDeepAiNodeList().size(); i++)
    {
        for (uint j = 0; j < ptrHeadNode->getChildDeepAiNodeList()[i]->getChildDeepAiNodeList().size(); j++)
        {
            deepAi.copyEngine(engine,copiedEngine);
            ptrHeadNode->getChildDeepAiNodeList()[i]->getChildDeepAiNodeList()[j]->getExecutedCommand()->execute(copiedEngine.getState());
            //deepAi.evalSituation(copiedEngine,*ptrHeadNode->getChildDeepAiNodeList()[i]->getChildDeepAiNodeList()[j]);
            deepAi.evalSituation(copiedEngine);
           

        }
        deepAi.minimixeScore(ptrHeadNode->getChildDeepAiNodeList()[i]);
        //cout<<headNode.getChildDeepAiNodeList()[i]->getScore();
         //BOOST_CHECK_EQUAL(ptrHeadNode->getChildDeepAiNodeList()[i]->getChildDeepAiNodeList().size(),10);

    }
    deepAi.maximiseScore(ptrHeadNode);

    int optimalCommandIndex=deepAi.findOptimalCommandIndex(ptrHeadNode);
    deepAi.executeOptimalCommand(engine,optimalCommandIndex,ptrHeadNode);
    

    
}