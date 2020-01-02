#include "../client.h"
#include "../render.h"
#include "../../shared/ai.h"
#include "../../shared/engine.h"
#include <unistd.h>
#include <thread>
#include <fstream>


#include <fstream>
#include <iostream>
#include <sstream>


using namespace std;
using namespace client;
using namespace state;
using namespace render;
using namespace engine;
using namespace ai;

//Constructor
ModularisationTest::ModularisationTest(){

}

/**run for the thread test
 * 
 * 
 */
void ModularisationTest::run(){
    cout<<"---- THREAD TEST ----"<<endl;

    //Launch engine in another thread
    std::thread t1(&ModularisationTest::engineThread,this);
    std::thread t2(&ModularisationTest::clientThread,this);
    t1.join();
    t2.join();

}

// Run for the record test
void ModularisationTest::runRecord(){
    cout<<"---- RECORD TEST ----"<<endl;

    //Launch engine in another thread
    std::thread t1(&ModularisationTest::engineThread,this);
    std::thread t2(&ModularisationTest::clientThread,this);

    t1.join();
    t2.join();


    Json::FastWriter fastWriter;
    std::string output = fastWriter.write(engine.getRecord());

    ofstream recordFile("record.txt",ios::app);
    if(recordFile){
         cout<<"Record file openned with success"<<endl;
        recordFile<<output<<endl;
    }else{
        cout<<"Record File open failed"<<endl;
    }
}

// Run to play the .txt file
void ModularisationTest::runPlay(){
    cout << "---- PLAY TEST ----" << endl;

    Json::Value root;
			unsigned int longueur_map_cases = 25, largeur_map_cases = 25;
			std::string chemin_fichier_map_txt = "res/map1.txt";
			std::string fichier_commandes = "res/replay.txt";
			
			// Creation des tables de correspondances et du moteur
			Correspondances tab_corres = Correspondances();
			Moteur moteur;
			
			if(	moteur.getEtat().initGrille(chemin_fichier_map_txt, longueur_map_cases, largeur_map_cases, tab_corres)){
				sf::RenderWindow window(sf::VideoMode(largeur_map_cases*16,longueur_map_cases*16 +200),"Map");
				
				moteur.getEtat().initPersonnages(tab_corres);
				moteur.getEtat().initCurseur();
				StateLayer stateLayer(moteur.getEtat(), window);
				stateLayer.initSurfaces(moteur.getEtat());
								
				StateLayer* ptr_stateLayer=&stateLayer;
				moteur.getEtat().registerObserver(ptr_stateLayer);
				
				
								
				cout << "\t\t--- Play ---" << endl;
				cout << "Pour lancer la partie, appuyez sur la touche P\n" << endl;						
				
				bool demarrage = true ;				
				bool partie_rejouee = false;
				sf::Event event;
				StateEvent stateEvent(ALLCHANGED);
				
				while (window.isOpen()){				
					// Au premier appui sur P, on ouvre le fichier et on execute les commandes
					if(partie_rejouee == false && sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
						
						engine.readCommands(commandsFile);
						partie_rejouee = true;
					}
								
					if (demarrage){
						stateLayer.draw(window);
						demarrage = false;
					}
					
					while (window.pollEvent(event)){
						// Fermeture de la fenetre
						if (event.type == sf::Event::Closed){
							window.close();
						}
					}					
				}
			}
		}
}

/**
 * 
 * 
 */
void ModularisationTest::engineThread(){
    engine.getState().initPlayers();
}

/**
 * 
 * 
 */
void ModularisationTest::clientThread(){
    //Initialize the window
    sf::RenderWindow window(sf::VideoMode(1950, 900), "Fire Emblem");

    //Client Side (Render)
    StateLayer stateLayer(engine.getState(),window);
    stateLayer.initTextureAreas(engine.getState());

    StateLayer* ptr_stateLayer=&stateLayer;
    engine.getState().registerObserver(ptr_stateLayer);

    Engine* ptr_engine=&engine;
    stateLayer.registerRenderObserver(ptr_engine);
    bool booting = true;

    while (window.isOpen()){
        sf::Event event;

        //Initialize the scrren by drawing the default State
        if(booting){
            // Draw all the display on the screen
            stateLayer.draw(engine.getState());
            cout << "Start of the game.\n" << endl;
            booting = false;
        }

        while (1){

            ai::HeuristicAI heuristicAi1(1);
            heuristicAi1.run(engine);

            //Check if all ennemy units are dead or not
            if(engine.checkGameEnd()==true){
                window.close();
                cout<<"Game END"<<endl;
                break;
            }

            //Check if all units had played
            if(engine.checkRoundEnd()){
                cout<<"round  change"<<endl;
                engine.checkRoundStart();
                StateEvent stateEvent(PLAYERCHANGE);
                engine.getState().notifyObservers(stateEvent, engine.getState());
            }

            window.pollEvent(event);
            if (event.type == sf::Event::Closed){
                    window.close();
            }
            
            ai::HeuristicAI heuristic2(2);
            heuristic2.run(engine);
            engine.screenRefresh();
            usleep(50000);
        }
    }
}