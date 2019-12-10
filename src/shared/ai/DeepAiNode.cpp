#include "../engine.h"
#include "../state.h"
#include "../ai.h"
#include <iostream>
#include <unistd.h>

using namespace state;
using namespace engine;
using namespace std;
using namespace ai;

//Constructor

DeepAiNode::DeepAiNode(){
    this->ptrParent=0;
    this->score=-1000;
    this->executedCommand=0;
    this->childDeepAiNodeList=childDeepAiNodeList;
}

DeepAiNode::DeepAiNode (DeepAiNode* ptrParent, engine::Command* executedCommand):ptrParent(ptrParent),score(-1000),executedCommand(executedCommand),childDeepAiNodeList(childDeepAiNodeList){

}


//Getters and Setters

DeepAiNode* DeepAiNode::getPtrParent (){
    return ptrParent; 
}

std::vector<DeepAiNode*> DeepAiNode::getChildDeepAiNodeList (){
    return childDeepAiNodeList;
}

int DeepAiNode::getScore (){
    return score;
}

engine::Command* DeepAiNode::getExecutedCommand (){
    return executedCommand;
}

void DeepAiNode::setPtrParent (DeepAiNode* ptrParent){
    this->ptrParent=ptrParent;
}

void DeepAiNode::setChildDeepAiNodeList (std::vector<DeepAiNode*> childDeepAiNodeList){
    this->childDeepAiNodeList=childDeepAiNodeList;
}

void DeepAiNode::setScore (int score){
    this->score=score;
}

void DeepAiNode::setExecutedCommand (engine::Command* executedCommand){
    this->executedCommand=executedCommand;
}


