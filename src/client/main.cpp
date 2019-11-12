#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string.h>

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
    }
    return 0;
}


