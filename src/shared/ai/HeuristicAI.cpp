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

//Constructor
HeuristicAI::HeuristicAI(int AiID){
        artificialIntelligenceID=AiID;
}

// Functions 

void HeuristicAI::run (engine::Engine& engine){
    /*Position start,goal;
    start.setX(1);
    start.setY(1);
    goal.setX(3);
    goal.setY(3);
    std::vector<state::Position> moveList=algorithmAStar(engine,start,goal);*/
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

                /*** Check if there are ennemy units still alive***/
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
                    //AI Units health are weak --> run (Move)
                    std::vector<Position> allowedMovePositionList = engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->allowedMove(engine.getState());
                    if(engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->getHealth()<=10){
                        if(engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->getMovementLeft()==0 || allowedMovePositionList.size()==0){
                            action=2;//EndAction=2
                        }else{
                            action=0; //Move=0
                        }
                        
                    }else{
                        //Recover in a list all attackable positions
                        std::vector<Position> allowedAttackPositionList = engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->allowedAttack(engine.getState());
                        std::vector<Position> occupiedPositionInAttackZone;
                        int x_unit,y_unit;
                        if(allowedAttackPositionList.size()!=0){
                            //Check and recover in a list all units position inside the attack Zone
                            for (size_t m = 0; m < allowedAttackPositionList.size(); m++)
                            {
                                x_unit=allowedAttackPositionList[m].getX();
                                y_unit=allowedAttackPositionList[m].getY();
                                if(engine.getState().isOccupied(x_unit,y_unit)){
                                    occupiedPositionInAttackZone.push_back(allowedAttackPositionList[i]);
                                }
                            }

                            //There are units in attackable zone
                            
                            if(occupiedPositionInAttackZone.size()!=0){
                                unitToAttack=attackSuccessScoring(occupiedPositionInAttackZone,*engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i],engine.getState());
                                action=1;//Attack=1
                            }else{//No units in attackable zone
                                action=0;//Move=0
                            }
                        }else{
                            action=0;//Move=0
                        }

                        if(engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->getMovementLeft()==0 || allowedMovePositionList.size()==0){
                            action=2;//EndAction=2
                        }

                    }
                }

                // 0 : Move
                int randomPosition;
                int waitingTime=3;
                if (action == 0 && engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->getMovementLeft()!= 0){
                    //Initialize a liste of allowed Move
                    //cout<<"e1"<<endl;
                    std::vector<Position> allowedMoveList =engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->allowedMove(engine.getState());
                    if (allowedMoveList.size() != 0){
                        //srand(time(NULL));
                        //randomPosition = rand()%allowedMoveList.size();
                        state::Position start,goal;
                        start.setX(engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->getX());
                        start.setY(engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->getY());

                        /***************************************/
                        std::vector<Position> occupiedPosition;
                        state:Position position;
                        for (size_t a = 0; a < 25; a++)
                        {
                            for (size_t b = 0; b < 50; b++)
                            {
                                if(engine.getState().isOccupied(a,b)){
                                    bool sameTeam=false;
                                    for (size_t c = 0; c < engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList().size(); c++)
                                    {
                                        if(a==engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[c]->getX() && b==engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[c]->getY()){
                                            sameTeam=true;
                                        }
                                    }
                                    if(!sameTeam){
                                        position.setX(a);
                                        position.setY(b);
                                        occupiedPosition.push_back(position);
                                    }
                                    
                                }
                            }
                        }
                        
                        std::vector<float> distanceList;
                        float distance;
                        for (size_t d = 0; d < occupiedPosition.size(); d++)
                        {
                            distance=abs(occupiedPosition[d].getX()-start.getX()) + abs(occupiedPosition[d].getY()-start.getY());
                            distanceList.push_back(distance);
                        }
                        
                        int minIndex=0;
                        float minDistance=distanceList[0];
                        for (size_t e = 0; e < distanceList.size(); e++)
                        {
                            if(distanceList[e]<minDistance){
                                minDistance=distanceList[e];
                                minIndex=e;
                            }
                        }
                        

                        goal.setX(occupiedPosition[minIndex].getX());
                        goal.setY(occupiedPosition[minIndex].getY());


                        cout<<"e2"<<endl;
                        std::vector<state::Position> moveList=algorithmAStar(engine,start,goal);

                        /*******************************************************/
                        cout<<"e3"<<endl;
                        //cout<<moveList[0].getX()<<endl;
                        //cout<<moveList[0].getY()<<endl;
                        //cout<<moveList.size()<<endl;

                        // Move Command
                        Move movement (*engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i],allowedMoveList[0]);
                        unique_ptr<Command> ptr_movement (new Move(movement));
                        engine.addCommand(0, move(ptr_movement));
                        engine.update();//update engine will use state to notify render about changes
                        //cout<<"e4"<<endl;
                        //notAllowedAttack = false;
                        sleep(waitingTime);
                    }
                    //else{notAllowedMove = true;}
                }

                // 1 : Attack
                else if (action == 1){
    

                    //if (allowedAttackPositionList.size() !=0){
                        //srand(time(NULL));
                        //randomAttackPosition = rand()%allowedAttackPositionList.size();
                                            
                        // Check if there are units on the random Attack Position
                        //int target=engine.getState().isOccupied(allowedAttackPositionList[randomAttackPosition].getX(),allowedAttackPositionList[randomAttackPosition].getY());
                        //if (target ==true){
                            // Commande d'attaque
                            Attack attack(*engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i], *engine.getState().getMobileEntity(unitToAttack.getX(),unitToAttack.getY()));
                            unique_ptr<Command> ptr_attack (new Attack(attack));
                            engine.addCommand(0, move(ptr_attack));
                            engine.update();
                            //notAllowedMove = false;
                            sleep(waitingTime);
                        //}
                    //}
                    //else{notAllowedAttack = true;}				
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

state::Position HeuristicAI::attackSuccessScoring (std::vector<state::Position> occupiedPositionInAttackZone,state::MobileEntity& currentUnit,state::State& state){
    
    //Initialize all AI current unit statistics
    float currentUnitHealth=currentUnit.getHealth();
    float currentUnitArmor=currentUnit.getArmor();
    float currentUnitDamage=currentUnit.getDamage();
    int currentUnitMovementRange= currentUnit.getMovementRange();
    int currentUnitAttackRange=currentUnit.getAttackRange();

    //Declaration of all enemy Unit statistics variable
    float enemyUnitHealth;
    float enemyUnitArmor;
    float enemyUnitDamage;
    int enemyUnitMovementRange;
    int enemyUnitAttackRange;

    //Array to store all score value for different units in attackable zone
    std::vector<int> scoreList;
    int score=0;
    int maxScore=0;
    int maxScoreIndex=0;

    for (size_t i = 0; i < occupiedPositionInAttackZone.size(); i++)
    {
        //Initialization of all enemy Unit statistics
        enemyUnitHealth=state.getMobileEntity(occupiedPositionInAttackZone[i].getX(),occupiedPositionInAttackZone[i].getY())->getHealth();
        enemyUnitArmor=state.getMobileEntity(occupiedPositionInAttackZone[i].getX(),occupiedPositionInAttackZone[i].getY())->getArmor();
        enemyUnitDamage=state.getMobileEntity(occupiedPositionInAttackZone[i].getX(),occupiedPositionInAttackZone[i].getY())->getDamage();
        enemyUnitMovementRange=state.getMobileEntity(occupiedPositionInAttackZone[i].getX(),occupiedPositionInAttackZone[i].getY())->getMovementRange();
        enemyUnitAttackRange=state.getMobileEntity(occupiedPositionInAttackZone[i].getX(),occupiedPositionInAttackZone[i].getY())->getAttackRange();
        
        //the enemey Health is weak than AI health
        if(enemyUnitHealth<=currentUnitHealth){
            score+=6;
        }

        //the enemy armor is weak than AI damage
        if(enemyUnitArmor<currentUnitDamage){
            score++;
        }
        //the enemy armor is twice time weak than AI damage
        if(enemyUnitArmor<currentUnitDamage/2){
            score+=2;
        }
        //the enemy armor is third time weak than AI damage
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

        //Even after enemy attck in the AI the AI health is upper than the enemy health
        if(currentUnitHealth-enemyUnitDamage>enemyUnitHealth){
            score+=10;
        }

        //Store the score in the scoreList
        scoreList.push_back(score);
    }
    
    //Find the max score in the scoreList
    for (size_t k = 0; k < scoreList.size(); k++)
    {
        if(maxScore<scoreList[k]){
            maxScore=scoreList[k];
            maxScoreIndex=k;
        }
    }
    //Return the position of the enemy unit which will offer a good chance to wi the game if AI ATTACK it
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
        int minNodeIndex=minIndex(nodeStack);// index of node with the minimum heuristic distance
        Node currentNode = nodeStack[minNodeIndex];//in the stack list take the node with the minimum heuristic distance

        if(currentNode.getPosition().equal(goal)){
            goalNotReached=true;

            // Get the path from goal to start
            path.push_back(currentNode.getPosition());
            Node* nextNode=currentNode.getPreviousNode();
            while(!nextNode->getPosition().equal(startNode.getPosition())){
                path.push_back(nextNode->getPosition());
                nextNode=nextNode->getPreviousNode();
            }
        }
        else{
            cout << "Current Node :" << currentNode.getPosition().getX() << ", " << currentNode.getPosition().getY() << "\n" << endl;
            //Recover all neighbors node from the actual position
            vector<Node> nodeNeighbors = currentNode.getNeighbors(engine.getState());
            if(nodeNeighbors.size()!=0){
                //for each node in the Neighbors Node
                for(size_t i=0; i<nodeNeighbors.size(); i++){
                    //if the neighbors node is in the processing node stack
                    if(nodeInStack(nodeStack,nodeNeighbors[i])!=-1){
                        // If a node is already in stack but a new shorter path from start is found
                        if(currentNode.getDistanceFromStart()+1 < nodeNeighbors[i].getDistanceFromStart()){//the distance of the current node from the start < the distance of the neighbor node from the start
                            nodeNeighbors[i].setDistanceFromStart(currentNode.getDistanceFromStart()+1);//increase the distance from start to "+1"
                            nodeNeighbors[i].setPreviousNode(&currentNode);//replace the neighbor node withe the current node in the neighbor stack
                        }
                    }
                    else{
                        // New node is reached
                        nodeNeighbors[i].setPreviousNode(&currentNode);
                        nodeNeighbors[i].setDistanceFromStart(currentNode.getDistanceFromStart()+1);
                        nodeNeighbors[i].setDistanceFromGoal(nodeNeighbors[i].getPosition().distance(goal));
                        nodeStack.push_back(nodeNeighbors[i]);
                    }
                }
                // Empty the nodeNeighbors list for next iteration
                while(nodeNeighbors.size()!=0){
                    nodeNeighbors.pop_back();
                }
            }
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

