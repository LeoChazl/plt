
#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"
#include <vector>


using namespace std;
using namespace ::state;


BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

/***************************/
/***************************
 * MobileEntity*/
/**************************/

/*************/
/*Class Troll*/
/*************/
BOOST_AUTO_TEST_CASE(Troll_test)
{
  //Constructor Empty Arguments 
  {
    //Nom_de_la_classe * Nom_du_pointeur; Nom_du_pointeur = new Nom_de_la_classe;
    Troll troll;

    //Troll troll();
    //Getter test
    BOOST_CHECK_EQUAL(troll.getX(), 6);
    BOOST_CHECK_EQUAL(troll.getY(), 6);
    BOOST_CHECK_EQUAL(troll.getHealth(), 100);
    BOOST_CHECK_EQUAL(troll.getMovementRange(), 2);
    BOOST_CHECK_EQUAL(troll.getDamage(), 35);
    BOOST_CHECK_EQUAL(troll.getArmor(), 15);
    BOOST_CHECK_EQUAL(troll.getMaxHealth(), 100);
    BOOST_CHECK_EQUAL(troll.getEntityId(), TROLL);
    BOOST_CHECK_EQUAL(troll.getStatus(), AVAILABLE);
    BOOST_CHECK_EQUAL(troll.getDirection(), DOWN);
  }

    //Constructor With Arguments
  {
    Troll troll(1,1);

    printf("%d",troll.getX());

    //Getter test
    BOOST_CHECK_EQUAL(troll.getX(),1);
    BOOST_CHECK_EQUAL(troll.getY(),1);
    BOOST_CHECK_EQUAL(troll.getHealth(),100);
    BOOST_CHECK_EQUAL(troll.getMovementRange(),2);
    BOOST_CHECK_EQUAL(troll.getDamage(),35);
    BOOST_CHECK_EQUAL(troll.getArmor(),15);
    BOOST_CHECK_EQUAL(troll.getMaxHealth(),100);
    BOOST_CHECK_EQUAL(troll.getEntityId(), TROLL);
    BOOST_CHECK_EQUAL(troll.getStatus(), AVAILABLE);
    BOOST_CHECK_EQUAL(troll.getDirection(), DOWN);
  }

  //Test Setter
  {
    Troll troll;

    troll.setHealth(200);
    troll.setMovementRange(2);
    troll.setDamage(20);
    troll.setArmor(2);
    troll.setMaxHealth(200);
    troll.setStatus(SELECTED);
    troll.setDirection(UP);


    BOOST_CHECK_EQUAL(troll.getX(), 6);
    BOOST_CHECK_EQUAL(troll.getY(), 6);
    BOOST_CHECK_EQUAL(troll.getHealth(), 200);
    BOOST_CHECK_EQUAL(troll.getMovementRange(), 2);
    BOOST_CHECK_EQUAL(troll.getDamage(), 20);
    BOOST_CHECK_EQUAL(troll.getArmor(), 2);
    BOOST_CHECK_EQUAL(troll.getMaxHealth(), 200);
    BOOST_CHECK_EQUAL(troll.getEntityId(), TROLL);
    BOOST_CHECK_EQUAL(troll.getStatus(), SELECTED);
    BOOST_CHECK_EQUAL(troll.getDirection(), UP);
  }
}

/*************/
/*Class Knight*/
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
/*Class Mage*/
/*************/
BOOST_AUTO_TEST_CASE(Mage_test)
{
  {
    Mage mage;
    //Get EntityId
    BOOST_CHECK_EQUAL(mage.getEntityId(), MAGE);
    //Get and set Mana
    BOOST_CHECK_EQUAL(mage.getMana(), 100);
    BOOST_CHECK_EQUAL(mage.getManaMax(), 100);
    BOOST_CHECK_EQUAL(mage.getSpellDamage(), 45);
    BOOST_CHECK_EQUAL(mage.getSpellAttackRange(), 2);

  }

  {
    Mage mage(10,10);
    //Get and set Mana

    mage.setX(10);
    mage.setY(10);

    BOOST_CHECK_EQUAL(mage.getX(), 10);
    BOOST_CHECK_EQUAL(mage.getY(), 10);
    BOOST_CHECK_EQUAL(mage.getMana(), 100);
    BOOST_CHECK_EQUAL(mage.getManaMax(), 100);
    BOOST_CHECK_EQUAL(mage.getSpellDamage(), 45);
    BOOST_CHECK_EQUAL(mage.getSpellAttackRange(), 2);
  }

  {
    Mage mage1(10,10);
    Mage mage2(12,12);
    mage1.castSpell(mage2);// 70-(45-45/5) = 34;
    BOOST_CHECK_EQUAL(mage2.getHealth(),34);
  }
}

/**********/
/*Position*/
/**********/
BOOST_AUTO_TEST_CASE(Position_test)
{
  {
    Position position;
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

/***************************/
/***************************
 ****** STATIC ENTITY*******/
/**************************/

/**********/
/*Obstacle*/
/**********/
BOOST_AUTO_TEST_CASE(Obstacle_test)
{
  {
    Obstacle obstacle;
    BOOST_CHECK_EQUAL(obstacle.isSpace(), false);
   
  }
}

/*******/
/*Space*/
/*******/
BOOST_AUTO_TEST_CASE(Space_test)
{
  {
    Space space;
    BOOST_CHECK_EQUAL(space.isSpace(), true);
  }
}

/*******/
/*EntityMap*/
/*******/
BOOST_AUTO_TEST_CASE(EntityMap_test)
{
  {
    //Constructor level 1
    EntityMap entityMap(1);

    BOOST_CHECK_EQUAL(entityMap.getWidth(),25);
    BOOST_CHECK_EQUAL(entityMap.getHeight(),25);
  }
}

/*******/
/*State*/
/*******/
BOOST_AUTO_TEST_CASE(State_test)
{
  {
    //Constructor without arguments
    State state;
    EntityMap entityMap(1);
    Cursor cursor;

    BOOST_CHECK_EQUAL(state.getRound(),1);
    BOOST_CHECK_EQUAL(state.getLevel(),1);
    //BOOST_CHECK_EQUAL(state.getEntityMap(),entityMap);
    //BOOST_CHECK_EQUAL(state.getCursor(),cursor);
    BOOST_CHECK_EQUAL(state.getEndGame(),false);

    state.setRound(2);
    state.setLevel(2);
    state.setEndGame(true);
    BOOST_CHECK_EQUAL(state.getRound(),2);
    BOOST_CHECK_EQUAL(state.getLevel(),2);
    BOOST_CHECK_EQUAL(state.getEndGame(),true);
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