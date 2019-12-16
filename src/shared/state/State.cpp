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
    currentPlayerID=1;
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

    // Initialization of the first player
    shared_ptr<Player> ptrPlayer1(make_shared<Player> (1));


    shared_ptr<MobileEntity> ptrMage(make_shared<Mage> (2,2,ptrPlayer1->getId()));
    ptrPlayer1->getMobileEntityList().push_back(ptrMage);
    //shared_ptr<MobileEntity> ptrMage2(make_shared<Mage> (20,20,ptrPlayer1->getId()));
    //ptrPlayer1->getMobileEntityList().push_back(ptrMage2);
    //shared_ptr<MobileEntity> ptrKnight(make_shared<Knight> (10,10,ptrPlayer1->getId()));
    //ptrPlayer1->getMobileEntityList().push_back(ptrKnight);
    //shared_ptr<MobileEntity> ptrKnight2(make_shared<Knight> (15,15,ptrPlayer1->getId()));
    //ptrPlayer1->getMobileEntityList().push_back(ptrKnight2);
    shared_ptr<MobileEntity> ptrKnight3(make_shared<Knight> (ptrPlayer1->getId()));
    ptrPlayer1->getMobileEntityList().push_back(ptrKnight3);

    playerList.push_back(ptrPlayer1);

    // Initialization of the second player
    shared_ptr<Player> ptrPlayer2(make_shared<Player> (2));

    shared_ptr<MobileEntity> ptrTroll(make_shared<Troll> (ptrPlayer2->getId()));
    shared_ptr<MobileEntity> ptrTroll2(make_shared<Troll> (15,10,ptrPlayer2->getId()));
    //shared_ptr<MobileEntity> ptrTroll3(make_shared<Troll> (15,9,ptrPlayer2->getId()));


    ptrPlayer2->getMobileEntityList().push_back(ptrTroll);
    ptrPlayer2->getMobileEntityList().push_back(ptrTroll2);
    //ptrPlayer2->getMobileEntityList().push_back(ptrTroll3);

    playerList.push_back(ptrPlayer2);

    return true;
}

/** Test if a case is occupied by a MobileEntity
 * 
 * param : 
 * x and y coordinates of the case to test
 */
bool State::isOccupied(int x, int y){
    Player currentPlayer;

    for(unsigned int i=0;i<playerList.size();i++){
        currentPlayer = *playerList[i];
        for(unsigned int j=0;j<currentPlayer.getMobileEntityList().size();j++){
            if(x==(*currentPlayer.getMobileEntityList()[j]).getX() && y==(*currentPlayer.getMobileEntityList()[j]).getY())
                return true;
        }
    }

    return false;
}

/** Test if a unit is already selected 
 * 
 */
bool State::verifyIsSelected(){
    Player currentPlayer;

    for(unsigned int i=0;i<playerList.size();i++){
        currentPlayer = *playerList[i];
        for(unsigned int j=0;j<currentPlayer.getMobileEntityList().size();j++){
            if(currentPlayer.getMobileEntityList()[j]->getStatus() == SELECTED)
                return true;
        }
    }

    return false;
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

shared_ptr<MobileEntity> State::getMobileEntity(int x, int y){
    Player currentPlayer;
    int mobileEntityIndex=-1;
    int playerIndex;

    for(unsigned int i=0;i<playerList.size();i++){
        currentPlayer=*playerList[i];
        for(unsigned int j=0;j<currentPlayer.getMobileEntityList().size();j++){
            if(currentPlayer.getMobileEntityList()[j]->getX()==x && currentPlayer.getMobileEntityList()[j]->getY()==y){
                mobileEntityIndex=j;
                playerIndex=i;
            }
        }
    }
    if(mobileEntityIndex!=-1)
        return playerList[playerIndex]->getMobileEntityList()[mobileEntityIndex];
    
    return NULL;
}

shared_ptr<Player> State::getPlayer(int playerId){
    int wantedPlayerIndex;

    for(unsigned int i=0;i<playerList.size();i++){
        if(playerList[i]->getId()==playerId)
            wantedPlayerIndex = i;
    }

    return playerList[wantedPlayerIndex];
}

int State::getCurrentPlayerID(){
    return currentPlayerID;
}

Position State::getClosestEnemyPosition(Position& position){
    Position closestPosition(0,0);
    Position playerClosestPosition(0,0);
    int lowestDistance=1000; // Value above any distance possible
    for(size_t i=0; i<playerList.size(); i++){
        if(playerList[i]->getId()!=currentPlayerID){
            playerClosestPosition = playerList[i]->getClosestPosition(position);
            if(lowestDistance > position.distance(playerClosestPosition)){
                closestPosition = playerClosestPosition;
            }
        }
    }

    return closestPosition;
}


std::shared_ptr<state::MobileEntity> State::ptrReferenceToPlayingEntity (int playingEntityIndex){
    return playerList[currentPlayerID-1]->getMobileEntityList()[playingEntityIndex];
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

void State::setCurrentPlayerID (int currentPlayerID){
    this->currentPlayerID=currentPlayerID;
}


// Destructor

State::~State(){

}