#include "Player.h"

using namespace state;
using namespace std;

Player::Player(){

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

}
