
#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"


using namespace ::std;
using namespace state;

/***************************/
/***************************
 * MobileEntity*/
/**************************/

/*************/
/*CLass Troll*/
/*************/
BOOST_AUTO_TEST_CASE(Troll_test)
{
  //Constructeur de Troll vide
  {
    Troll troll;
    //Getter test
    BOOST_CHECK_EQUAL(troll.getEntityId(), TROLL);
    BOOST_CHECK_EQUAL(troll.getMovementRange(), 1);
    BOOST_CHECK_EQUAL(troll.getAttackRange(), 1);
    BOOST_CHECK_EQUAL(troll.getDamage(), 10);
    BOOST_CHECK_EQUAL(troll.getArmor(), 1);
    BOOST_CHECK_EQUAL(troll.getMaxHealth(), 100);
    BOOST_CHECK_EQUAL(troll.getStatus(), AVAILABLE);
    BOOST_CHECK_EQUAL(troll.getDirection(), DOWN);
  }

  //Test Setter
  {
    Troll troll;

    troll.setHealth(200);
    troll.setMovementRange(2);
    troll.setAttackRange(2);
    troll.setDamage(20);
    troll.setArmor(2);
    troll.setMaxHealth(200);
    troll.setEntityId(MAGE);
    troll.setStatus(SELECTED);
    troll.setDirection(UP);


    BOOST_CHECK_EQUAL(troll.getEntityId(), MAGE);
    BOOST_CHECK_EQUAL(troll.getMovementRange(), 2);
    BOOST_CHECK_EQUAL(troll.getAttackRange(), 2);
    BOOST_CHECK_EQUAL(troll.getDamage(), 20);
    BOOST_CHECK_EQUAL(troll.getArmor(), 2);
    BOOST_CHECK_EQUAL(troll.getMaxHealth(), 200);
    BOOST_CHECK_EQUAL(troll.getStatus(), SELECTED);
    BOOST_CHECK_EQUAL(troll.getDirection(), UP);
  }
}

/*************/
/*CLass Knight*/
/*************/
BOOST_AUTO_TEST_CASE(Knight_test)
{
  {
    Knight knight;
    //Get EntityId
    BOOST_CHECK_EQUAL(knight.getEntityId(), KNIGHT);
  }
}

/*************/
/*CLass Mage*/
/*************/
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

/**********/
/*Position*/
/**********/
BOOST_AUTO_TEST_CASE(Position_test)
{
  {
    Position position;
    //Get EntityId
    BOOST_CHECK_EQUAL(position.getX(), 0);
    BOOST_CHECK_EQUAL(position.getY(), 0);

    position.setX(10);
    position.setY(20);

    BOOST_CHECK_EQUAL(position.getX(), 10);
    BOOST_CHECK_EQUAL(position.getY(), 20);
  }
}


/********/
/*Cursor*/
/********/
BOOST_AUTO_TEST_CASE(Cursor_test)
{
  {
    Cursor cursor;
    //Get EntityId
    BOOST_CHECK_EQUAL(cursor.getX(), 0);
    BOOST_CHECK_EQUAL(cursor.getY(), 0);

    cursor.setX(10);
    cursor.setY(20);
    BOOST_CHECK_EQUAL(cursor.getX(), 10);
    BOOST_CHECK_EQUAL(cursor.getY(), 20);

    cursor.moveCursor(30,30);
    BOOST_CHECK_EQUAL(cursor.getX(), 30);
    BOOST_CHECK_EQUAL(cursor.getY(), 30);
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