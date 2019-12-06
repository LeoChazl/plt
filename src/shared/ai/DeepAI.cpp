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
DeepAI::DeepAI(int AiID):depth(depth),currentPlayerID(currentPlayerID){
        artificialIntelligenceID=AiID;

}

/**Launch the deeep AI
 * 
 */
void DeepAI::run (engine::Engine& engine){
    
    /*****************************************************
     * TEST
     *****************************************************/ 
    /*vector<int> scores;
    scores = {5,3, 5, 9, 12, 5, 23, 23}; 
    int n = scores.size(); 
    int h = log2(n); 
    int res = algorithmMinMax(0, 0, true, scores, h);
    cout << "NodesValue list size is : " << n << endl; 
    cout << "Depth value is : " << h << endl; 
    cout << "The optimal value is : " << res << endl;*/
    /*************************************************/

    
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


                    //AI Units health are weak --> run (Move)
                    /*std::vector<Position> allowedMovePositionList = engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->allowedMove(engine.getState());
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

                    }*/

                    std::vector<std::unique_ptr<engine::Command>> possibleCommandList=findPossibleActions (engine,artificialIntelligenceID,i);
                    //std::vector<int> scoreList= findCommandWeight (possibleCommandList,engine);
                    std::vector<int> scoreList;
                    scoreList.push_back(10);
                    scoreList.push_back(100);
                    scoreList.push_back(20);
                    scoreList.push_back(40);
                    scoreList.push_back(50);
                    scoreList.push_back(15);
                    scoreList.push_back(20);
                    scoreList.push_back(90);


                    int depth=0;//initial depth
                    int nodeIndex=0;//index of the node
                    bool isMax=true;//first choose the max value
                    int n=scoreList.size();//list of int value representing possible command evaluation
                    int h=log2(n);//real depth
                    while(ceilf(h) != h){
                        n++;
                        h=log2(n);
                        scoreList.push_back(0);
                    }

                    int minMaxAlgoResult= DeepAI::algorithmMinMax (depth,nodeIndex,isMax, scoreList, h);
                    if(minMaxAlgoResult<25){
                        action=2;
                    }else if(minMaxAlgoResult<50 && minMaxAlgoResult>=25){
                        action=1;
                    }else{
                        action=0;
                    }

                    if ( engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->getMovementLeft()== 0){
                        action=2;
                    }
                }

                // 0 : Move
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
                        state::Position position;
                        for (int a = 0; a < 25; a++)
                        {
                            for (int b = 0; b < 50; b++)
                            {
                                if(engine.getState().isOccupied(a,b)){
                                    bool sameTeam=false;
                                    for (int c = 0; c < engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList().size(); c++)
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
                        //std::vector<state::Position> moveList=algorithmAStar(engine,start,goal);

                        /*******************************************************/
                        //cout<<"e3"<<endl;
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


/**Algorithme Min Max
 * 
 */ 
int DeepAI::algorithmMinMax (int depth, int nodeIndex, bool isMax, std::vector<int> nodesValue, int h){
// Terminating condition. i.e 
    // leaf node is reached 
    if (depth == h) 
        return nodesValue[nodeIndex]; 
  
    //  If current move is maximizer, 
    // find the maximum attainable 
    // value 
    if (isMax) 
       return max(algorithmMinMax(depth+1, nodeIndex*2, false, nodesValue, h), 
            algorithmMinMax(depth+1, nodeIndex*2 + 1, false, nodesValue, h));//the bool allow us to altern etween max and min  
  
    // Else (If current move is Minimizer), find the minimum 
    // attainable value 
    else
        return min(algorithmMinMax(depth+1, nodeIndex*2, true, nodesValue, h), 
            algorithmMinMax(depth+1, nodeIndex*2 + 1, true, nodesValue, h));
}


int DeepAI::log2(int n){
    if(n==1){
        return 0;
    }else{
        return 1+log2(n/2);
    }
}

/**Evaluation a value  to score a situation after a simulated action
 * 
 */
int DeepAI::evaluationFunction (engine::Engine& engine){
    int score;
    int artificialIntelligenceID=2;
    //Situation = game end
    if(engine.getState().getEndGame()){
        for (size_t i = 0; i < engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList().size(); i++)
        {
            if(engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i]->getStatus()!=DEAD){
                score=1000-engine.getState().getRound();
            }else{
                score=-1000+engine.getState().getRound();
            }
            return score;
        }
    
    //Situation= game didn't end
    }else{
        int sumCurrentPv=0, sumAdversePv=0, currentPlayerAliveUnits=0, AdverseAliveUnits=0;
		Position deadPosition(-1,-1);
		for(int i=0; i<engine.getState().getPlayerList().size(); i++){
            //the player is the artificial intelligence
            if(i==artificialIntelligenceID){
                for (size_t j = 0; j < engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList().size(); j++)
                {
                    //sum all the artifical intelligence units pv in the current situation / Count all the artificial intelligence units which are still alive
                    sumCurrentPv+=engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[j]->getHealth();
                    currentPlayerAliveUnits++;
                }
            }
            //the player is not the artificial intelligence
            else{
                for (size_t j = 0; j < engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList().size(); j++)
                {
                    //sum all adverse units pv in the current situation / Count all adverse units which are still alive
                    sumAdversePv+=engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[j]->getHealth();
                    AdverseAliveUnits++;
                }
            }
		}
		score=sumCurrentPv-sumAdversePv+100*currentPlayerAliveUnits-100*AdverseAliveUnits;
		cout<<"Evaluation function return  :" << score<<endl;
    }
    return score;
}

/**Ececute all the possible actions and try to have a list of scoring --> with simulated actions 
 * 
 */
std::vector<unique_ptr<engine::Command>> DeepAI::findPossibleActions (engine::Engine& engine, int artificialIntelligenceID, int entityNumber){
    std::vector<unique_ptr<engine::Command>> listCommand;
	std::vector<state::Position> listAttackPosition;
	std::vector<state::Position> listMovePosition;


    if(engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[entityNumber]->getStatus()!= DEAD && engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[entityNumber]->getStatus()!= WAITING){
        //REcover all posibe attack and move positions
        listAttackPosition=engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[entityNumber]->allowedAttack(engine.getState());
        listMovePosition=engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[entityNumber]->allowedMove(engine.getState());

        //Possible ATTACK Command: for each attack possible attack position
        for (size_t i = 0; i < listAttackPosition.size(); i++){
            //Attack poosition : (x,y)
            int x=listAttackPosition[i].getX();
            int y=listAttackPosition[i].getY();

            //Store all the attack command on the adverse units only in the possible attack positions
            if(engine.getState().isOccupied(x,y)){
                if(engine.getState().getMobileEntity(x,y)->getPlayerId()!=artificialIntelligenceID){
                    Attack attack(*engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[entityNumber], *engine.getState().getMobileEntity(x,y));
                    unique_ptr<Command> ptr_attack (new Attack(attack));
                    listCommand.push_back(move(ptr_attack));
                    //engine.addCommand(0, move(ptr_attack));
                    //engine.update();
                }
            }
        }

        //Possible MOVE Command : for each move
        for (size_t i = 0; i < listMovePosition.size(); i++){
            //Attack poosition : (x,y)

            Move movement (*engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[i],listMovePosition[i]);
            unique_ptr<Command> ptr_movement (new Move(movement));
            listCommand.push_back(move(ptr_movement));
            //engine.addCommand(0, move(ptr_attack));
            //engine.update();
        }

        //END ACTION Command
        EndEntityRound endAction(*engine.getState().getPlayerList()[artificialIntelligenceID]->getMobileEntityList()[entityNumber]);
        unique_ptr<Command> ptr_endAction (new EndEntityRound(endAction));
        listCommand.push_back(move(ptr_endAction));
    }

    return listCommand;
}


/**Put a score in each possible commands with "evaluationfunction"
 * 
 */
//std::vector<int> DeepAI::findCommandWeight (std::vector<std::unique_ptr<engine::Command>> listCommand,engine::Engine& engine){
    //std::vector<int> scoreList;

    /*for (size_t i = 0; i < 10; i++)
    {
        //listCommand[i]->execute(engine.getState());
        //scoreList.push_back(evaluationFunction(engine));
        scoreList.push_back(10+i);
    }*/
    //return scoreList;
//}
