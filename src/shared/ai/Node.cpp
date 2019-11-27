#include "../engine.h"
#include "../state.h"
#include "../ai.h"
#include <iostream>
#include <unistd.h>

using namespace state;
using namespace engine;
using namespace std;
using namespace ai;


// Constructors

Node::Node(){
    position.setX(0);
    position.setY(0);
    previousNode=nullptr;
    distanceFromStart=0;
    distanceFromGoal=0;
}

Node::Node(Node* previousNode) : previousNode(previousNode){
    position.setX(0);
    position.setY(0);
    distanceFromStart=0;
    distanceFromGoal=0;
}

Node::Node(Node* previousNode, state::Position position) : position(position), previousNode(previousNode){
    distanceFromStart=0;
    distanceFromGoal=0;
}

// Functions



// Getters and Setters

state::Position& Node::getPosition(){
    return position;
}

Node* Node::getPreviousNode(){
    return previousNode;
}

int Node::getDistanceFromStart(){
    return distanceFromStart;
}

int Node::getDistanceFromGoal(){
    return distanceFromGoal;
}

void Node::setPosition(state::Position position){
    this->position=position;
}

void Node::setPreviousNode(Node* previousNode){
    this->previousNode=previousNode;
}

void Node::setDistanceFromStart(int distanceFromStart){
    this->distanceFromStart=distanceFromStart;
}

void Node::setDistanceFromGoal(int distanceFromGoal){
    this->distanceFromGoal=distanceFromGoal;
}
