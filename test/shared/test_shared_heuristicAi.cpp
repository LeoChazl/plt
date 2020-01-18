#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"
#include "../../src/shared/engine.h"
#include "../../src/shared/ai.h"
#include "../../src/client/render.h"


#include <vector>
#include <unistd.h>


#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
using namespace state;
using namespace render;
using namespace engine;
using namespace ai;


BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
    {

    
    //Engine Init
    Engine engine;
    engine.getState().initPlayers();
    
    int artificialIntelligenceID=1;

    HeuristicAI heuristic_ai(artificialIntelligenceID);
    heuristic_ai.run(engine);

    
    }

    

    
}