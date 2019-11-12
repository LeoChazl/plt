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


using namespace std;
using namespace state;
using namespace render;
using namespace engine;
using namespace client;

namespace sf {
  class RenderWindow;
}



BOOST_AUTO_TEST_CASE(TestClient)
{
  {
    ::sf::Texture texture;
    BOOST_CHECK(texture.getSize() == ::sf::Vector2<unsigned int> {});
  }

  {
    RenderTest renderTest;
    renderTest.run();
  }

  {
    //EngineTest engineTest;
    //engineTest.run();
  }
}

/* vim: set sw=2 sts=2 et : */