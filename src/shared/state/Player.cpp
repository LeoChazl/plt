#include "../state.h"

using namespace state;
using namespace std;

// Constructors

Player::Player(){
    
}

Player::Player(int id){
    this->id = id;
    if(id==1){
        shared_ptr<MobileEntity> ptrMage(new Mage);
        shared_ptr<MobileEntity> ptrKnight(new Knight);
        mobileEntityList.push_back(ptrMage);
        mobileEntityList.push_back(ptrKnight);
    }
    else if(id==2){
        shared_ptr<MobileEntity> ptrTroll(new Troll);
        mobileEntityList.push_back(ptrTroll);
    }
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