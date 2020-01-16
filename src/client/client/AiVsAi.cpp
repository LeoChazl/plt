#include "../client.h"
#include "../render.h"
#include "../../shared/ai.h"
#include "../../shared/engine.h"
#include <unistd.h>
#include <string.h>


#include <fstream>
#include <iostream>
#include <sstream>


using namespace std;
using namespace client;
using namespace state;
using namespace render;
using namespace engine;
using namespace ai;

AiVsAi::AiVsAi(){

}

void AiVsAi::run(std::string firstAi,std::string secondAi){
    cout<<"---- Heuristic AI TEST ----"<<endl;

    //Initialize the window
    sf::RenderWindow window(sf::VideoMode(1950, 900), "Fire Emblem");

    /**************************/
    // la vue de jeu (toute la fenêtre)
    // création d'une vue faisant la moitié de la vue par défaut
    sf::View view = window.getDefaultView();
    window.setView(view);


    /************************/

    //Engine Side
    Engine engine;
    engine.getState().initPlayers();
    //Client Side (Render)
    StateLayer stateLayer(engine.getState(),window);
    stateLayer.initTextureAreas(engine.getState());

    //randomAi.initAi(1,engine);

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
            //Fixe the fist AI
            if(firstAi=="random_ai"){
                ai::RandomAI randomAi1(1);
                randomAi1.run(engine);
            }else if(firstAi=="heuristic_ai"){
                ai::HeuristicAI heuristicAi1(1);
                heuristicAi1.run(engine);
            }else if(firstAi=="deep_ai"){
                ai::DeepAI deepAi1(1);
                deepAi1.run(engine);
            }


            //Check if all ennemy units are dead or not
            if(engine.checkGameEnd()==true){
                window.close();
                cout<<"Game END"<<endl;
                break;
            }

            //Check if all units had played
            if(engine.checkRoundEnd()){
                cout<<"Round  change"<<endl;
                engine.checkRoundStart();
                StateEvent stateEvent(ALLCHANGE);
                engine.getState().notifyObservers(stateEvent, engine.getState());
            }

            window.pollEvent(event);
            if (event.type == sf::Event::Closed){
                    window.close();
            }
            
            //Fixe the second AI
            if(secondAi=="random_ai"){
                ai::RandomAI randomAi2(2);
                randomAi2.run(engine);
            }else if(secondAi=="heuristic_ai"){
                ai::HeuristicAI heuristicAi2(2);
                heuristicAi2.run(engine);
            }else if(secondAi=="deep_ai"){
                ai::DeepAI deepAi2(2);
                deepAi2.run(engine);
            }


            /******** Erase Comments if you want to control a player*************/
            //stateLayer.inputManager(event, engine.getState());
            engine.screenRefresh();
            usleep(50000);
        }
    }
}