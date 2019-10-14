#include "Player.h"
#include <iostream>

using namespace state;
using namespace std;

Player::Player(int id, string name){
    this->id = id;
    this->name = name;
}

int Player::getId(){
    return id;
}

string Player::getName(){
    return name;
}

vector<shared_ptr<MobileEntity>> Player::getMobileEntityList(){
    return mobileEntityList;
}

void Player::setId(int id){
    this->id = id;
}

void Player::setName(string name){
    this->name = name;
}

void Player::setMobileEntityList(vector<shared_ptr<MobileEntity>> mobileEntityList){
    this->mobileEntityList = mobileEntityList;
}

void Player::deleteEntity(int x, int y){
    for(int i=0; i<mobileEntityList.size(); i++){
        if(mobileEntityList[i]->getX() == x && mobileEntityList[i]->getY() == y){
            //mobileEntityList.erase(i);
        }
    }
}
