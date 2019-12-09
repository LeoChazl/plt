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

namespace ai{
    class DeepAI;
}

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
    Engine engine;
    engine.setChangeRound(true);
    engine.setStop(true);

    ai::DeepAI deepAi(1);
    Engine copiedEngine;
    //copy engine
    deepAi.copyEngine(engine,copiedEngine);
    
    state::State state;
    state.setEndGame(true);
    copiedEngine.setCurrentState(state);
    //Test if "engine" and copiedEngine" don't have any link
    BOOST_CHECK_EQUAL(engine.getState().getEndGame(),false);
    BOOST_CHECK_EQUAL(copiedEngine.getState().getEndGame(),true);

}