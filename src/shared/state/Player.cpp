#include "../state.h"
#include <iostream>

using namespace state;
using namespace std;

// Constructors

Player::Player(){
    
}

Player::Player(int id){
    this->id = id;
    this->name = "Player " + to_string(id);
}

Player::Player(int id, string name){
    this->id = id;
    this->name = name;
}

// Functions

/** Delete the MobileEntity with the corresponding position
 * 
 * param :
 * mobileEntity -> the unit to delete from the player unit list
 */
void Player::deleteEntity(MobileEntity& mobileEntity){
    for(unsigned int i=0; i<mobileEntityList.size(); i++){
        if(mobileEntityList[i]->getX() == mobileEntity.getX() && mobileEntityList[i]->getY() == mobileEntity.getY()){
            mobileEntityList.erase(mobileEntityList.begin() + i);
        }
    }
}

// Getters

int Player::getId(){
    return id;
}

string Player::getName(){
    return name;
}

vector<shared_ptr<MobileEntity>>& Player::getMobileEntityList(){
    return mobileEntityList;
}

Position Player::getClosestPosition(Position& position){
    Position closestPosition(0,0);
    Position testPosition(0,0);
    int lowestDistance=1000; // Value above any distance possible
    for(size_t i=0; i<mobileEntityList.size(); i++){
        if(mobileEntityList[i]->getStatus()!=DEAD){
            testPosition.setX(mobileEntityList[i]->getX());
            testPosition.setY(mobileEntityList[i]->getY());

            if(lowestDistance > testPosition.distance(position)){
                lowestDistance = testPosition.distance(position);
                closestPosition = testPosition;
            }
        }
    }

    return closestPosition;
}

// Setters 

void Player::setId(int id){
    this->id = id;
}

void Player::setName(string name){
    this->name = name;
}

void Player::setMobileEntityList(vector<shared_ptr<MobileEntity>>& mobileEntityList){
    this->mobileEntityList = mobileEntityList;
}