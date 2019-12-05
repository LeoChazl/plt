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

std::vector<Node> Node::getNeighbors(state::State& state){

    Node* neighborNode = new Node();
    Position neighborNodePosition(0,0);

    std::vector<Node> neightborNodes;

    for(int i=position.getX()-1; i<=position.getX()+1; i++){
        for(int j=position.getY()-1; j<=position.getY()+1; j++){
            // Test that the node is in range of the current node
            if((abs(i - position.getX()) + abs(j - position.getY()) <= 1)){
                // Test not out of bounds
                if(i>=0 && i < state.getEntityMap().getWidth() && j>=0 && j < state.getEntityMap().getHeight()){
                    // Test the targeted node is not an obstacle and not occupied by a MobileEntity
                    if(state.getEntityMap().getMapArray()[i][j]->isSpace() && !state.isOccupied(i,j)){
                        // Just adding the node with position information for now
                        // Test if the node is already in the stack later
                        neighborNodePosition.setX(i);
                        neighborNodePosition.setY(j);
                        neighborNode->setPosition(neighborNodePosition);
                        neightborNodes.push_back(*neighborNode);
                    }
                }
            }
        }
    }
    return neightborNodes;
}

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

int Node::getHeuristicDistance(){
    return distanceFromStart + distanceFromGoal;
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

Node::~Node(){
    
}
