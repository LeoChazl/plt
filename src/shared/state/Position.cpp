#include "Position.h"

using namespace state;
using namespace std;

//Constructor
Position::Position(){

}

Position::Position(int x,int y){
    this->x=x;
    this->y=y;
}

//Getters and Setters
int Position::getX(){
    return x;
}

int Position::getY(){
    return y;
}

void Position::setX(int x){
    this->x=x;
}

void Position::setY(int y){
    this->y=y;
}