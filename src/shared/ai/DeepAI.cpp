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
    // The number of elements in scores must be 
    // a power of 2. 
    vector<int> scores;
    scores = {5,3, 5, 9, 12, 5, 23, 23}; 
    int n = scores.size(); 
    int h = log2(n); 
    int res = algorithmMinMax(0, 0, true, scores, h);
    cout << "NodesValue list size is : " << n << endl; 
    cout << "Depth value is : " << h << endl; 
    cout << "The optimal value is : " << res << endl;

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
int evaluationFunction (engine::Engine& engine){
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
    
    //Situation=game didn't end
    }else{
        int sumCurrentPv=0, sumAdversePv=0, currentPlayerAliveUnits=0, AdverseAliveUnits=0;
		Position deadPosition(-1,-1);
		for(size_t i=0; i<engine.getState().getPlayerList().size(); i++){
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
