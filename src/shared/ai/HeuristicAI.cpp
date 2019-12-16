#include "../engine.h"
#include "../state.h"
#include "../ai.h"
#include <iostream>
#include <unistd.h>
#include <bits/stdc++.h> 


using namespace state;
using namespace engine;
using namespace std;
using namespace ai;

// Constructor

HeuristicAI::HeuristicAI(int AiID){
        artificialIntelligenceID=AiID;
}

// Functions 

void HeuristicAI::run (engine::Engine& engine){
    // The current player ID is equal AI ID -> AI turn
    if(engine.getState().getCurrentPlayerID()==artificialIntelligenceID){
        artificialIntelligenceID=artificialIntelligenceID-1;//In order to use the id as an array index
        int action;
        state::Position unitToAttack;

        // For each Unit controlled by artificial Intelligence Player
        for(unsigned int i=0;i<engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList().size();i++){

            // The Unit need to end his turn or dead before changing to another unit
            while (engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->getStatus()!=DEAD && engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->getStatus()!=WAITING)
            {
                // Set the status of the current Unit as selected
                engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->setStatus(SELECTED);
                bool ennemyUnitsAllDead=true;

                // Check if there are enemy units still alive
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

                // No Units alive--> AI 
                if (ennemyUnitsAllDead){
						action = 2; // EndAction=2
				}
				else{
                    // AI Units health are weak --> run (Move)
                    std::vector<Position> allowedMovePositionList = engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->allowedMove(engine.getState());
                    if(engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->getHealth()<=10){
                        if(engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->getMovementLeft()==0 || allowedMovePositionList.size()==0){
                            action=2; // EndAction=2
                        }else{
                            action=0; // Move=0
                        }
                        
                    }else{
                        // Check and recover in a list all units position inside the attack Zone
                        std::vector<Position> allowedAttackPositionList = engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->allowedAttack(engine.getState());

                        // If there are units to attack
                        if(allowedAttackPositionList.size()!=0){
                                unitToAttack=attackSuccessScoring(allowedAttackPositionList,*engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i],engine.getState());
                                action=1; // Attack=1
                        }else if(engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->getMovementLeft()==0 || allowedMovePositionList.size()==0){
                            action=2; // EndAction=2
                        }else{
                            action=0; // Move=0
                        }
                    }
                }

                // 0 : Move
                int waitingTime=1;
                if (action == 0 && engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->getMovementLeft()!= 0){
                    // Initialize a list of allowed Move
                    std::vector<Position> allowedMoveList =engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->allowedMove(engine.getState());
                    if (allowedMoveList.size() != 0){
                        state::Position start,goal;
                        start.setX(engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->getX());
                        start.setY(engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->getY());

                        goal=engine.getState().getClosestEnemyPosition(start);
                        cout << "Goal position : " << goal.getX() << ", " << goal.getY() << endl;

                        std::vector<state::Position> moveList=algorithmAStar(engine,start,goal);

                        // Move Command
                        Move movement (*engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i],moveList[moveList.size()-1]);
                        unique_ptr<Command> ptr_movement (new Move(movement));
                        engine.addCommand(0, move(ptr_movement));
                        engine.update();//update engine will use state to notify render about changes

                        sleep(waitingTime);
                        moveList.pop_back();

                        moveList.clear();
                    }
                }

                // 1 : Attack
                else if (action == 1){
                    Attack attack(*engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i], *engine.getState().getMobileEntity(unitToAttack.getX(),unitToAttack.getY()));
                    unique_ptr<Command> ptr_attack (new Attack(attack));
                    engine.addCommand(0, move(ptr_attack));
                    engine.update();
                    sleep(waitingTime);		
                }

                // 2 : EndEntityRound
                else if (action == 2){
                    EndEntityRound endAction(*engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]);
                    unique_ptr<Command> ptr_endAction (new EndEntityRound(endAction));
                    engine.addCommand(0, move(ptr_endAction));
                    engine.update();
                    sleep(waitingTime);
                }
            }
        }
    }
}

state::Position HeuristicAI::attackSuccessScoring (std::vector<state::Position>& occupiedPositionInAttackZone,state::MobileEntity& currentUnit,state::State& state){
    
    // Initialize all AI current unit statistics
    float currentUnitHealth=currentUnit.getHealth();
    float currentUnitDamage=currentUnit.getDamage();
    int currentUnitMovementRange= currentUnit.getMovementRange();
    int currentUnitAttackRange=currentUnit.getAttackRange();

    // Declaration of all enemy Unit statistics variable
    float enemyUnitHealth;
    float enemyUnitArmor;
    float enemyUnitDamage;
    int enemyUnitMovementRange;
    int enemyUnitAttackRange;

    // Array to store all score value for different units in attackable zone
    std::vector<int> scoreList;
    int score=0;
    int maxScore=0;
    int maxScoreIndex=0;

    for (size_t i = 0; i < occupiedPositionInAttackZone.size(); i++)
    {
        // Initialization of all enemy Unit statistics
        enemyUnitHealth=state.getMobileEntity(occupiedPositionInAttackZone[i].getX(),occupiedPositionInAttackZone[i].getY())->getHealth();
        enemyUnitArmor=state.getMobileEntity(occupiedPositionInAttackZone[i].getX(),occupiedPositionInAttackZone[i].getY())->getArmor();
        enemyUnitDamage=state.getMobileEntity(occupiedPositionInAttackZone[i].getX(),occupiedPositionInAttackZone[i].getY())->getDamage();
        enemyUnitMovementRange=state.getMobileEntity(occupiedPositionInAttackZone[i].getX(),occupiedPositionInAttackZone[i].getY())->getMovementRange();
        enemyUnitAttackRange=state.getMobileEntity(occupiedPositionInAttackZone[i].getX(),occupiedPositionInAttackZone[i].getY())->getAttackRange();
        
        // Enemy Health is lower than AI health
        if(enemyUnitHealth<=currentUnitHealth){
            score+=6;
        }

        // Enemy armor is lower than AI damage
        if(enemyUnitArmor<currentUnitDamage){
            score++;
        }
        // Enemy armor is twice time lower than AI damage
        if(enemyUnitArmor<currentUnitDamage/2){
            score+=2;
        }
        // Enemy armor is third time lower than AI damage
        if(enemyUnitArmor<currentUnitDamage/3){
            score+=3;
        }

        if(enemyUnitDamage<currentUnitDamage){
            score++;
        }

        if(enemyUnitMovementRange<currentUnitMovementRange){
            score++;
        }

        if(enemyUnitAttackRange<currentUnitAttackRange){
            score++;
        }

        // Even after enemy attck in the AI the AI health is upper than the enemy health
        if(currentUnitHealth-enemyUnitDamage>enemyUnitHealth){
            score+=10;
        }

        // Store the score in the scoreList
        scoreList.push_back(score);
    }
    
    // Find the max score in the scoreList
    for (size_t k = 0; k < scoreList.size(); k++)
    {
        if(maxScore<scoreList[k]){
            maxScore=scoreList[k];
            maxScoreIndex=k;
        }
    }
    // Return the position of the enemy unit which will offer a good chance to wi the game if AI ATTACK it
    return occupiedPositionInAttackZone[maxScoreIndex];

}


std::vector<state::Position> HeuristicAI::algorithmAStar (engine::Engine& engine, state::Position start, state::Position goal){
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

                    // Get the path from goal to start
                    path.push_back(nodeNeighbors[i].getPosition());
                    Node nextNode= *nodeNeighbors[i].getPreviousNode();
                    while(!nextNode.getPosition().equal(startNode.getPosition())){
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
}

/**Recover the index of a node in a stack with the smallest heuristic distance to the goal
 * 
 */

int HeuristicAI::minIndex(std::vector<Node> nodeStack){
    int minIndex=-1;

    if(nodeStack.size()!=0){
        minIndex=0;
        Node minNode=nodeStack[0];
        //for each node in a node stack
        for(size_t i=1; i<nodeStack.size(); i++){
            //compare the heuristic distance of two Nodes to the goal in order to fin the Node which is near to the goal
            if(nodeStack[i].getHeuristicDistance()<minNode.getHeuristicDistance()){
                minNode=nodeStack[i];
                minIndex=i;
            }
        }
    }
    return minIndex;
}

/** Recover the index of a noeud give as argument if it is in a Node Stack
 * 
 */
int HeuristicAI::nodeInStack(std::vector<Node> nodeStack, Node& node){
    int indexInStack=-1;
    
    for(size_t i=0; i<nodeStack.size(); i++){
        if(nodeStack[i].getPosition().equal(node.getPosition())){
            indexInStack=i;
            break;
        }
    }

    return indexInStack;
}

