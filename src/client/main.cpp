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
    if(argc>1){
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
    }

    return 0;
}


