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

    ofstream recordFile("record.txt");
    if(recordFile){
         cout<<"Recording file opened with success"<<endl;
        recordFile<<output<<endl;
    }else{
        cout<<"Recording file opening failed"<<endl;
    }
}

// Run to play the .txt file
void ModularisationTest::runPlay(){
    cout << "---- PLAY TEST ----\n" << endl;

	std::string commandsFile = "record.txt";
								

    //Initialize the window
    sf::RenderWindow window(sf::VideoMode(1950, 900), "Fire Emblem");

    //Engine Side
    Engine engine;
    engine.getState().initPlayers();

    //Client Side (Render)
    StateLayer stateLayer(engine.getState(),window);
    stateLayer.initTextureAreas(engine.getState());

    StateLayer* ptr_stateLayer=&stateLayer;
    engine.getState().registerObserver(ptr_stateLayer);

    Engine* ptr_engine=&engine;
    stateLayer.registerRenderObserver(ptr_engine);
    bool booting = true;
    bool alreadyReplayed = false;

    while (window.isOpen()){
        sf::Event event;

        //Initialize the screen by drawing the default State
        if(booting){
            // Draw all the display on the screen
            stateLayer.draw(engine.getState());
            cout << "Start of the game.\n" << endl;
            booting = false;
        }

        while (1){
            window.pollEvent(event);

		    // Open file and read the commands
			engine.replayCommands(commandsFile);
		    alreadyReplayed = true;

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

            if (event.type == sf::Event::Closed){
                    window.close();
            }

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

        //Initialize the screen by drawing the default State
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