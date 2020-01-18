#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"
#include "../../src/shared/engine.h"
#include "../../src/client/render.h"
#include "../../src/client/client.h"



#include <vector>
#include <unistd.h>


#include <fstream>
#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string.h>
#include <thread>
#include <mutex>



using namespace sf;
using namespace std;
using namespace state;
using namespace render;
using namespace engine;
using namespace client;


namespace sf {
  class RenderWindow;
}



BOOST_AUTO_TEST_CASE(TestClientMain)
{
  {    


    //HeuristicAiTest heuristicAiTest;
    //heuristicAiTest.run();
    AiVsAi aiVsAi;
    aiVsAi.run("random_ai","heuristic_ai");
  }

}

/* vim: set sw=2 sts=2 et : */