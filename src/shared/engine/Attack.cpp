#include "../engine.h"
#include "../state.h"
#include <iostream> 
#include <unistd.h>
#include <stdlib.h>

using namespace engine;
using namespace state;
using namespace std;

// Constructor

Attack::Attack (state::MobileEntity& attacker, state::MobileEntity& target): attacker(attacker),target(target){

}

// Function

void Attack::execute (state::State& state){
    bool attackIsPossible=false;
    //Store all the possible coordinates for the attack
    std::vector<state::Position> listeCoordAtq=attacker.allowedAttack(state);

    if(attacker.getStatus()!=WAITING &&attacker.getStatus()!=DEAD){

        //for each open to attack coordinate we tested if tha target possible coorespond to one of the possible attack position
		for(size_t j=0; j<listeCoordAtq.size(); j++){
			if((listeCoordAtq[j].getX()==target.getX()) && (listeCoordAtq[j].getY()==target.getY()) ){
				attackIsPossible=true;
				break;
			}
		}
        attackIsPossible=true;
        //If the attack is possible 
        if(attackIsPossible){
            //Target
            cout<<"Attack is possible"<<endl;
            //target.setHealth(50);
            float oldTargetHealth=target.getHealth();
            

            //Attack
            attacker.attack(target);
            //target.setHealth(oldTargetHealth-attacker.getDamage());

            //Display on console : State 
            cout<<"Le target avait "<<oldTargetHealth<<" points de vie."<<endl;
            cout<<"Le target a "<<target.getHealth()<<" de points de vie restant."<<endl;

            //If the target unit don't have a positif health value after the attack
            if(target.getHealth()==0){
                target.setStatus(DEAD);
                target.setX(-1);
                target.setY(-1);
                cout << "Le target est mort." << endl;
                sleep(2);
            }
        }else{
            cout<<"Aucun ennemie dans la zone d'attaque"<<endl;
        }

    }else if(attacker.getStatus()==WAITING){
        cout<<"Ce personnage ne peut plus attaquer-->raison: Son tour d'actions est terminé "<<endl;
    }
}

