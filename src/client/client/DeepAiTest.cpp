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

DeepAiTest::DeepAiTest(){

}

void DeepAiTest::run(){
    DeepAI deepAi(2);
    Engine engine;
    deepAi.run(engine);
}