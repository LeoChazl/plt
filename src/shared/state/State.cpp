#include "../state.h"
#include <iostream>

using namespace state;
using namespace std;

// Constructor

State::State(){
    // We are initializing a state for the first level for now
    round=1;
    level=1;
    EntityMap entityMap(1);
    map=entityMap;
    Cursor cursor;
    endGame=false;
}

// Functions

/** Delete the player with the corresponding id
 * 
 * param :
 * player -> the player to delete from the player list
 */
void State::deletePlayer(Player& player){
    for(unsigned int i=0; i<playerList.size(); i++){
        if(playerList[i]->getId() == player.getId()){
            playerList.erase(playerList.begin() + i);
        }
    }
}

/** Initialize the players for level 1
 */
bool State::initPlayers(){
    // To randomize units starting position
    srand(time(0));
    int x = 0;
    int y = 0;

    // Initialization of the first player
    shared_ptr<MobileEntity> ptrMage(new Mage);
    // Unit starting position is randomized in a certain area
    do{
        x = rand() % 13;
        y = rand() % 11;
    }while(!getEntityMap().getMapArray()[ptrMage->getY() + y][ptrMage->getX() + x]->isSpace());
    ptrMage->setX(ptrMage->getX() + x);
    ptrMage->setY(ptrMage->getY() + y);

    shared_ptr<MobileEntity> ptrKnight(new Knight);
    do{
        x = rand() % 7;
        y = rand() % 8;
    }while(!getEntityMap().getMapArray()[ptrKnight->getY() + y][ptrKnight->getX() + x]->isSpace());
    ptrKnight->setX(ptrKnight->getX() + x);
    ptrKnight->setY(ptrKnight->getY() + y);

    shared_ptr<Player> ptrPlayer1(new Player(1));
    ptrPlayer1->getMobileEntityList().push_back(ptrMage);
    ptrPlayer1->getMobileEntityList().push_back(ptrKnight);
    playerList.push_back(ptrPlayer1);

    // Initialization of the second player
    shared_ptr<MobileEntity> ptrTroll(new Troll);
    do{
        x = rand() % 5;
        y = rand() % 10;
    }while(!getEntityMap().getMapArray()[ptrTroll->getY() + y][ptrTroll->getX() + x]->isSpace());
    ptrTroll->setX(ptrTroll->getX() + x);
    ptrTroll->setY(ptrTroll->getY() + y);

    shared_ptr<Player> ptrPlayer2(new Player(2));
    ptrPlayer2->getMobileEntityList().push_back(ptrTroll);
    playerList.push_back(ptrPlayer2);

    return true;
}

// Getters

int State::getRound(){
    return round;
}

int State::getLevel(){
    return level;
}

EntityMap& State::getEntityMap(){
    return map;
}

vector<shared_ptr<Player>>& State::getPlayerList(){
    return playerList;
}

Cursor& State::getCursor(){
    return cursor;
}

bool State::getEndGame(){
    return endGame;
}

// Setters

void State::setRound(int round){
    this->round=round;
}

void State::setLevel(int level){
    this->level=level;
}

void State::setEndGame(bool endGame){
    this->endGame=endGame;
}

// Destructor

State::~State(){

}