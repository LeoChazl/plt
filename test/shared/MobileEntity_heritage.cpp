
#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"


using namespace ::std;
using namespace state;



BOOST_AUTO_TEST_CASE(Troll_test)
{
  {
    Troll troll;
    //Get EntityId
    BOOST_CHECK_EQUAL(troll.getEntityId(), TROLL);
  }
}
BOOST_AUTO_TEST_CASE(Knight_test)
{
  {
    Knight knight;
    //Get EntityId
    BOOST_CHECK_EQUAL(knight.getEntityId(), KNIGHT);
  }
}

BOOST_AUTO_TEST_CASE(Mage_test)
{
  {
    Mage mage;
    //Get EntityId
    BOOST_CHECK_EQUAL(mage.getEntityId(), MAGE);
    //Get and set Mana
    BOOST_CHECK_EQUAL(mage.getMana(), 100);
    mage.setMana(50);
    BOOST_CHECK_EQUAL(mage.getMana(), 50);
  }

  {
    Mage mage;
    //Get and set Mana
    BOOST_CHECK_EQUAL(mage.getManaMax(), 100);
    mage.setManaMax(50);
    BOOST_CHECK_EQUAL(mage.getManaMax(), 50);
  }

}

/*vim: set sw=2 sts=2 et : */

  /*{
    Exemple ex {};
    BOOST_CHECK_EQUAL(ex.x, 0);
    ex.setX(21);
    BOOST_CHECK_EQUAL(ex.x, 21);
  }

  {
    Exemple ex {};
    ex.setX(21);
    BOOST_CHECK_LE(ex.x, 32); // Less than equal
    BOOST_CHECK_GT(ex.x, 11); // Greater than equl
  }*/

    /*{
    //BOOST_CHECK_EQUAL(1,1);
    //BOOST_CHECK(true);
  }*/