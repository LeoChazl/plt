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
    //The current player ID is equal AI ID -> AI turn
    if(engine.getState().getCurrentPlayerID()==artificialIntelligenceID){
        artificialIntelligenceID=artificialIntelligenceID-1;//In order to use the id as an array index
        int action;
        state::Position unitToAttack;

        //for each Unit controlled by artificial Intelligence Player
        for(unsigned int i=0;i<engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList().size();i++){
            
            //The Unit need to end his turn or dead before changing to another unit
            while (engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->getStatus()!=DEAD && engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->getStatus()!=WAITING)
            {
                //Set the status of the current Unit as selected
                engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->setStatus(SELECTED);
                bool ennemyUnitsAllDead=true;

                // Check if there are ennemy units still alive
                for (size_t l = 0; l < engine.getState().getPlayerList().size(); l++){
                    if(engine.getState().getPlayerList()[l]->getId()!=artificialIntelligenceID){
                        for (size_t k = 0; k < engine.getState().getPlayerList()[i]->getMobileEntityList().size(); k++)
                        {
                            if(engine.getState().getPlayerList()[l]->getMobileEntityList()[k]->getStatus()!=DEAD){
                                ennemyUnitsAllDead = false; //there are ennemy units still alive
                                break;
                            }
                        }
                    }
                }

                //No Units alive--> AI 
                if (ennemyUnitsAllDead){
						action = 2;//EndAction=2
				}
				else{
                    //ai::DeepAI deepAi(1);
                    Engine copiedEngine;
                    //copy engine
                    copyEngine(engine,copiedEngine);

                    /***********************************/
                    /*"attackableEnemies" function test*/
                    /***********************************/
                    std::vector<state::Position> attackableEnemiesPositionList;
                    //Store in  "attackableEnemiesPositionList" all attackable ennemeies positions
                    attackableEnemiesPositionList=attackableEnemies(copiedEngine,i,artificialIntelligenceID);

                    /**********************************/
                    /*"optimalMoveCoord" function test*/
                    /**********************************/
                    std::vector<state::Position> optimalMoveCoords;
                    optimalMoveCoords=optimalMoveCoord(copiedEngine,i,artificialIntelligenceID);

                    /*************************************/
                    /*"storeAttackCommands" function test*/
                    /*************************************/
                    std::vector<std::shared_ptr<engine::Command>> possibleCommandList;
                    storeAttackCommands(copiedEngine,attackableEnemiesPositionList,possibleCommandList,i);

                    /***********************************/
                    /*"storeMoveCommands" function test*/
                    /***********************************/
                    storeMoveCommands(copiedEngine,optimalMoveCoords,possibleCommandList,i);

                    /***************************************/
                    /*"storeEndActionCommand" function test*/
                    /***************************************/
                    storeEndActionCommand(copiedEngine,possibleCommandList,i);

                /*--------------------------------------------------------------------------*/

                    /***************************************/
                    /*"createNodes" function test*/
                    /***************************************/
                    //Init Parent Node
                    std::shared_ptr<ai::DeepAiNode> ptrHeadNode(std::make_shared<DeepAiNode>());
                    

                    
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
                        ptrChildNode->setExecutedCommand(possibleCommandList[i]);
                        childNodesList.push_back(ptrChildNode);
                    }
                    ptrHeadNode->setChildDeepAiNodeList(childNodesList);

                    /***************************************/
                    /*"createTheTree" function test*/
                    /***************************************/
                    for (uint i = 0; i < ptrHeadNode->getChildDeepAiNodeList().size(); i++)
                    {
                        copyEngine(engine,copiedEngine);
                        ptrHeadNode->getChildDeepAiNodeList()[i]->getExecutedCommand()->execute(copiedEngine.getState());
                        copiedEngine.update();
                        //possibleCommandList[i]->execute(copiedEngine.getState());
                        
                        /***********************************/
                        /*"attackableEnemies" function test*/
                        /***********************************/
                        std::vector<state::Position> attackableEnemiesPositionList;
                        attackableEnemiesPositionList=attackableEnemies(copiedEngine,0,1);

                        /**********************************/
                        /*"optimalMoveCoord" function test*/
                        /**********************************/
                        std::vector<state::Position> optimalMoveCoords;
                        optimalMoveCoords=optimalMoveCoord(copiedEngine,0,1);

                        /*************************************/
                        /*"storeAttackCommands" function test*/
                        /*************************************/
                        std::vector<std::shared_ptr<engine::Command>> possibleCommandList2;

                        storeAttackCommands(copiedEngine,attackableEnemiesPositionList,possibleCommandList2,0);

                        /***********************************/
                        /*"storeMoveCommands" function test*/
                        /***********************************/
                        storeMoveCommands(copiedEngine,attackableEnemiesPositionList,possibleCommandList2,0);

                        /***************************************/
                        /*"storeEndActionCommand" function test*/
                        /***************************************/
                        storeEndActionCommand(copiedEngine,possibleCommandList2,0);

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

                            //possibleCommandList2[i]->execute(copiedEngine.getState());
                            //ptrChildNode->setScore(deepAi.evalSituation(engine));
                        }
                        

                        //ptrChildParentNode->setChildDeepAiNodeList(childNodesList2);
                        ptrHeadNode->getChildDeepAiNodeList()[i]->setChildDeepAiNodeList(childNodesList2);
                        

                    }


                    /***************************************/
                    /*"evalSituation" function test*/
                    /***************************************/
                    for (uint i = 0; i < ptrHeadNode->getChildDeepAiNodeList().size(); i++)
                    {
                        for (uint j = 0; j < ptrHeadNode->getChildDeepAiNodeList()[i]->getChildDeepAiNodeList().size(); j++)
                        {
                            copyEngine(engine,copiedEngine);
                            ptrHeadNode->getChildDeepAiNodeList()[i]->getChildDeepAiNodeList()[j]->getExecutedCommand()->execute(copiedEngine.getState());
                        
                            ptrHeadNode->getChildDeepAiNodeList()[i]->getChildDeepAiNodeList()[j]->setScore(evalSituation(copiedEngine));

                        }
                        minimixeScore(ptrHeadNode->getChildDeepAiNodeList()[i]);
                    }
                    maximiseScore(ptrHeadNode);

                    int optimalCommandIndex=findOptimalCommandIndex(ptrHeadNode);
                    executeOptimalCommand(engine,optimalCommandIndex,ptrHeadNode);
                    engine.update();
                }
            }
        }
    }
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
    for (uint i = 0; i < allowedAttackPosition.size(); i++)
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
    HeuristicAI heurAi(2);
    state::Position start,goal;
    start.setX(copiedEngine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[aiUnitIndex]->getX());
    start.setY(copiedEngine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[aiUnitIndex]->getY());

    goal=copiedEngine.getState().getClosestEnemyPosition(start);
    optimalMoveCoord=heurAi.algorithmAStar(copiedEngine,start,goal);
    return optimalMoveCoord;
}


/**store all possible attack commands in a list
 * 
 *  No Return
 */
void DeepAI::storeAttackCommands (engine::Engine& engine, std::vector<state::Position>& attackableEnemiesPositionList, std::vector<std::shared_ptr<engine::Command>>& possibleCommandList, int aiUnitIndex){
    int x,y;
    for (uint i = 0; i < attackableEnemiesPositionList.size(); i++)
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
    
    for (uint i = 0; i < optimalMoveCoord.size(); i++)
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

/**create a list of child nodes (one node for each possibleCommands) and sore it in a parent attribut ("childDeepAiNode")
 *  Arguments: -> reference to "copiedEngine" 
 *             -> reference to the parent Node
 *             -> list of possible Commands
 *  No return
 */
void DeepAI::createChildNodes (engine::Engine& copiedEngine, std::shared_ptr<DeepAiNode>& parentNode, std::vector<std::shared_ptr<engine::Command>> possibleCommandList){

    std::vector<std::shared_ptr<ai::DeepAiNode>> childNodesList= parentNode->getChildDeepAiNodeList();
    for (uint i = 0; i < possibleCommandList.size(); i++)
    {
        //DeepAiNode childNode;
        std::shared_ptr<DeepAiNode> ptrChildNode(std::make_shared<DeepAiNode>());
        ptrChildNode->setPtrParent(parentNode);
        ptrChildNode->setExecutedCommand(possibleCommandList[i]);
        childNodesList.push_back(ptrChildNode);
    }
    parentNode->setChildDeepAiNodeList(childNodesList);
    
}

/**Evaluate the actual situation in order to attribut a score
 * 
 *  No retrun
 */ 

int DeepAI::evalSituation(engine::Engine& copiedEngine){
    int score=0;
    int artificialIntelligenceID=1;
    //Situation = game end
    if(copiedEngine.getState().getEndGame()){
        for (size_t i = 0; i < copiedEngine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList().size(); i++)
        {
            if(copiedEngine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->getStatus()!=DEAD){
                score=1000-copiedEngine.getState().getRound();//In a game end situation -> give max score if artificial intelligence have at least one unit alive
            }else{
                score=-1000+copiedEngine.getState().getRound();//In a game end situation --> give min score if artificaial intelligence lose the game
            }
            return score;
        }

    //Situation= game didn't end
    }else{
        int sumCurrentPv=0, sumAdversePv=0, currentPlayerAliveUnits=0, AdverseAliveUnits=0;
        Position deadPosition(-1,-1);
        for(uint i=0; i<copiedEngine.getState().getPlayerList().size(); i++){
            //the player is the artificial intelligence
            if(i==artificialIntelligenceID){
                for (size_t j = 0; j < copiedEngine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList().size(); j++)
                {
                    //sum all the artifical intelligence units pv in the current situation / Count all the artificial intelligence units which are still alive
                    sumCurrentPv+=copiedEngine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[j]->getHealth();
                    currentPlayerAliveUnits++;
                }
            }
            //the player is not the artificial intelligence
            else{
                for (size_t j = 0; j < copiedEngine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList().size(); j++)
                {
                    //sum all adverse units pv in the current situation / Count all adverse units which are still alive
                    sumAdversePv+=copiedEngine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[j]->getHealth();
                    AdverseAliveUnits++;
                }
            }
        }
        score=sumCurrentPv-sumAdversePv+100*currentPlayerAliveUnits-AdverseAliveUnits;
        cout<<"Evaluation function return  :" << score<<endl;
        return score;
    }
    return -1000;
}

/**Give the max score chose between childNode score
 * 
 * No Return
 */
void DeepAI::maximiseScore (std::shared_ptr<DeepAiNode>& ptrEvaluatedNode){
    int actualScore=-1000;
    std::vector<std::shared_ptr<DeepAiNode>> childNodes=ptrEvaluatedNode->getChildDeepAiNodeList();
    int maxScore=childNodes[0]->getScore();
    for (uint i = 0; i < childNodes.size(); i++)
    {
        actualScore=childNodes[i]->getScore();
        if(maxScore<actualScore){
            maxScore=actualScore;
        }
    }
    ptrEvaluatedNode->setScore(maxScore);
}

/**Give the min score chose between childNode score
 * 
 * No Return
 */
void DeepAI::minimixeScore (std::shared_ptr<DeepAiNode>& ptrEvaluatedNode){
    int actualScore;
    std::vector<std::shared_ptr<DeepAiNode>> childNodes=ptrEvaluatedNode->getChildDeepAiNodeList();
    int minScore=childNodes[0]->getScore();
    for (uint i = 0; i < childNodes.size(); i++)
    {
        actualScore=childNodes[i]->getScore();
        if(minScore>actualScore){
            minScore=actualScore;
        }
    }
    ptrEvaluatedNode->setScore(minScore);
}

/**Optimal Command index 
 * 
 * 
 */
int DeepAI::findOptimalCommandIndex (std::shared_ptr<DeepAiNode>& ptrHeadNode){
    int maxScoreIndex=0;
    int maxScore=ptrHeadNode->getChildDeepAiNodeList()[0]->getScore();
    int actualScore=ptrHeadNode->getChildDeepAiNodeList()[0]->getScore();
    for (uint i = 0; i < ptrHeadNode->getChildDeepAiNodeList().size(); i++)
    {
        actualScore=ptrHeadNode->getChildDeepAiNodeList()[i]->getScore();
        if(maxScore<actualScore){
            maxScore=actualScore;
            maxScoreIndex=i;
        }
    }
    return maxScoreIndex;
}


/**Execute Optimal Commmand
 * 
 * 
 */
void DeepAI::executeOptimalCommand (engine::Engine& engine, int optimalCommandIndex, std::shared_ptr<DeepAiNode>& ptrHeadNode){
    ptrHeadNode->getChildDeepAiNodeList()[optimalCommandIndex]->getExecutedCommand()->execute(engine.getState());
}


/**AStartAlgorithm
 * 
 * 
 */
/*std::vector<state::Position> DeepAI::algorithmAStar (engine::Engine& engine, state::Position start, state::Position goal){
    vector<Position> path;

    // Check if the goal is reachable and has a unit on it
    if(engine.getState().isOccupied(goal.getX(), goal.getY())){
        vector<Position> possibleNextPosition=engine.getState().getMobileEntity(goal.getX(), goal.getY())->allowedMove(engine.getState());
        if(possibleNextPosition.size()==0){
            return path;
        }
    }

    // Contains the nodes already processed by A star
    vector<Node> processedNodes;
    // Contains the nodes reached by A star and has to be processed
    vector<Node> nodeStack;

    bool goalNotReached=true;

    // Initializing starting node
    Node startNode(nullptr, start);
    startNode.setDistanceFromStart(0);
    startNode.setDistanceFromGoal(start.distance(goal));

    nodeStack.push_back(startNode);

    // As long as there are nodes to process or that the goal isn't reached
    while(nodeStack.size()!=0 && goalNotReached){
        int minNodeIndex=minIndex(nodeStack);// Index of node with the minimum heuristic distance
        Node currentNode = nodeStack[minNodeIndex];// In the stack list take the node with the minimum heuristic distance

        // Recover all neighbors node from the actual position
        vector<Node> nodeNeighbors = currentNode.getNeighbors(engine.getState());
        if(nodeNeighbors.size()!=0){
            // For each node in the Neighbors Node
            for(size_t i=0; i<nodeNeighbors.size(); i++){
                // If the neighbors node is in the processing node stack
                if(nodeInStack(nodeStack,nodeNeighbors[i])!=-1){
                    // If a node is already in stack but a new shorter path from start is found
                    if(currentNode.getDistanceFromStart()+1 < nodeNeighbors[i].getDistanceFromStart()){//the distance of the current node from the start < the distance of the neighbor node from the start
                        nodeNeighbors[i].setDistanceFromStart(currentNode.getDistanceFromStart()+1);//increase the distance from start to "+1"
                        nodeNeighbors[i].setPreviousNode(&currentNode); // Replace the neighbor node withe the current node in the neighbor stack
                    }
                }
                else{
                    // New node is reached
                    nodeNeighbors[i].setPreviousNode(new Node(currentNode));
                    nodeNeighbors[i].setDistanceFromStart(currentNode.getDistanceFromStart()+1);
                    nodeNeighbors[i].setDistanceFromGoal(nodeNeighbors[i].getPosition().distance(goal));
                    nodeStack.push_back(nodeNeighbors[i]);
                }
                if(nodeNeighbors[i].getPosition().distance(goal)==1){
                    goalNotReached=false;
                    cout << "goal" << endl;

                    // Get the path from goal to start
                    path.push_back(nodeNeighbors[i].getPosition());
                    Node nextNode= *nodeNeighbors[i].getPreviousNode();
                    while(!nextNode.getPosition().equal(startNode.getPosition())){
                        cout << "Next node pos :" << nextNode.getPosition().getX() << ", " << nextNode.getPosition().getY() << endl;
                        path.push_back(nextNode.getPosition());
                        nextNode=*nextNode.getPreviousNode();
                    }
                }
            }
            // Empty the nodeNeighbors list for next iteration
            nodeNeighbors.clear();
        }
        processedNodes.push_back(currentNode);
        nodeStack.erase(nodeStack.begin() + minNodeIndex);
    }
    return path;
}*/