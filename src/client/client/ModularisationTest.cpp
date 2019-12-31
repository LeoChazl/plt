#include "../client.h"
#include "../render.h"
#include "../../shared/ai.h"
#include "../../shared/engine.h"
#include <unistd.h>
#include <thread>


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

void ModularisationTest::run(){
    cout<<"---- Heuristic AI TEST ----"<<endl;

    //Initialize the window
    sf::RenderWindow window(sf::VideoMode(1950, 900), "Fire Emblem");

    //std::thread t1(engineThread);
    //t1.join();
    engineThread();
    //Engine* ptr_engineThread=(Engine*) engineThread();
    //Engine engine(*ptr_engineThread);

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

/**
 * 
 * 
 */
void ModularisationTest::engineThread(){
    //Engine Side
    engine.getState().initPlayers();
}
