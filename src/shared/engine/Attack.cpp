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
    string entityNameAttacker = "";
    switch(attacker.getEntityId()){
        case TROLL: 
            entityNameAttacker = "troll";
            break;
        case MAGE:
            entityNameAttacker = "mage";
            break;
        case KNIGHT:
            entityNameAttacker = "knight";
            break;
    }

    string entityNameTarget = "";
    switch(target.getEntityId()){
        case TROLL: 
            entityNameTarget = "troll";
            break;
        case MAGE:
            entityNameTarget = "mage";
            break;
        case KNIGHT:
            entityNameTarget = "knight";
            break;
    }

    cout << "The " << entityNameAttacker << " will attack or try to attack the " << entityNameTarget << "." << endl;

    bool attackIsPossible=false;
    std::vector<state::Position> listeCoordAtq=attacker.allowedAttack(state);

    if(attacker.getStatus()!=WAITING &&attacker.getStatus()!=DEAD){

        // For each coordinate open to attack we tested if a possible target corresponds to one of the possible attack position
		for(size_t j=0; j<listeCoordAtq.size(); j++){
			if((listeCoordAtq[j].getX()==target.getX()) && (listeCoordAtq[j].getY()==target.getY()) ){
				attackIsPossible=true;
				break;
			}
		}
        attackIsPossible=true;
        // If the attack is possible 
        if(attackIsPossible){
            // Target
            cout<<"The attack is possible !"<<endl;

            float oldTargetHealth=target.getHealth();
            
            // Attack
            attacker.attack(target);

            // Display on console : State 
            cout<<"The " << entityNameTarget << " had " << oldTargetHealth << " health points." << endl;
            cout<<"The " << entityNameTarget << " has now " << target.getHealth() << " health points left.\n" << endl;

            // If the target unit don't have a positif health value after the attack
            if(target.getHealth()==0){
                target.setStatus(DEAD);
                target.setX(-1);
                target.setY(-1);
                cout << "The " << entityNameTarget << " is dead.\n" << endl;
                sleep(2);
            }
        }else{
            cout<<"The " << entityNameTarget << " is not in " << entityNameAttacker << " range.\n" << endl;
        }

    }else if(attacker.getStatus()==WAITING){
        cout<< "The " << entityNameAttacker << " cannot attack because his turn already ended.\n" << endl;
    }
}

