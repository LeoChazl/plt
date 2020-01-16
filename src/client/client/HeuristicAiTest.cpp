#include "../client.h"
#include "../render.h"
#include "../../shared/ai.h"
#include "../../shared/engine.h"
#include <unistd.h>


#include <fstream>
#include <iostream>
#include <sstream>


using namespace std;
using namespace client;
using namespace state;
using namespace render;
using namespace engine;
using namespace ai;

HeuristicAiTest::HeuristicAiTest(){

}

void HeuristicAiTest::run(){
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
            //engine.checkRoundStart();
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
                cout<<"Round  change"<<endl;
                engine.checkRoundStart();
                StateEvent stateEvent(ALLCHANGE);
                engine.getState().notifyObservers(stateEvent, engine.getState());
            }

            window.pollEvent(event);
            if (event.type == sf::Event::Closed){
                    window.close();
            }
            
            ai::HeuristicAI heuristic2(2);
            heuristic2.run(engine);
            /******** Erase Comments if you want to control a player*************/
            //stateLayer.inputManager(event, engine.getState());
            engine.screenRefresh();
            usleep(50000);
        }
    }
}