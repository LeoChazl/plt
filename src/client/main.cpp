#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string.h>
#include <thread>
#include <mutex>

#include "render.h"
#include "../shared/engine.h"
#include "client.h"



using namespace sf;
using namespace std;
using namespace state;
using namespace render;
using namespace engine;
using namespace client;


int main(int argc, char* argv[])
{
    if(argc==2){
        if(strcmp(argv[1],"render")==0){
            RenderTest renderTest;
            renderTest.run();
        }
        else if(strcmp(argv[1],"engine")==0){
            EngineTest engineTest;
            engineTest.run();
        }
        else if(strcmp(argv[1],"random_ai")==0){
            AiTest aiTest;
            aiTest.run();
        }
        else if(strcmp(argv[1],"heuristic_ai")==0){
            HeuristicAiTest heuristicAiTest;
            heuristicAiTest.run();
        }
        else if(strcmp(argv[1],"deep_ai")==0){
            DeepAiTest deepAiTest;
            deepAiTest.run();
        }
        else if(strcmp(argv[1],"thread")==0){
            ModularisationTest modularisationTest;
            modularisationTest.run();
        }
        else if(strcmp(argv[1],"record")==0){
            ModularisationTest modularisationTest;
            modularisationTest.runRecord();
        }
        else if(strcmp(argv[1],"play")==0){
            ModularisationTest modularisationTest;
            modularisationTest.runPlay();
        }
        else if(strcmp(argv[1],"network")==0){
            ServerTest serverTest;
            serverTest.run();
        }
        printf("La taille de la liste d'aguments %d",argc);
    }else if(argc==3){
        AiVsAi aiVsAi;
        aiVsAi.run(argv[1],argv[2]);
    }

    return 0;
}


