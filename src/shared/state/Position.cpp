#include "../state.h"

using namespace state;
using namespace std;

// Constructors

Position::Position(){
    x=0;
    y=0;
}

Position::Position(int x,int y){
    this->x=x;
    this->y=y;
}

// Function

bool Position::equal(Position& position){
    if(x==position.getX() && y==position.getY()){
        return true;
    }
    return false;
}

// Getters

int Position::getX(){
    return x;
}

int Position::getY(){
    return y;
}

// Setters 

void Position::setX(int x){
    this->x=x;
}

void Position::setY(int y){
    this->y=y;
}