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
DeepAI::DeepAI():depth(depth),currentPlayerID(currentPlayerID){

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