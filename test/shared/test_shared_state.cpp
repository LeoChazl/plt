
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
/*CLass Troll*/
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
/*CLass Knight*/
/*************/
BOOST_AUTO_TEST_CASE(Knight_test)
{
  {
    Knight knight;
    //Get EntityId
    BOOST_CHECK_EQUAL(knight.getEntityId(), KNIGHT);
  }

  {
    Knight knight(11,11);
    //Get EntityId
    BOOST_CHECK_EQUAL(knight.getX(), 11);
    BOOST_CHECK_EQUAL(knight.getY(), 11);
  }

  //Physical Attack
  {
    Knight knight1(10,10);
    Knight knight2(11,11);
    float health_k2=knight2.getHealth();
    float damage_k1=knight1.getDamage();
    float armor_k2=knight2.getArmor();
    health_k2-=damage_k1-damage_k1/armor_k2;
    knight1.physicalAttack(knight2);//100-(35-35/15)=67.33
    BOOST_CHECK_EQUAL(knight2.getHealth(), health_k2);

  }
}

/*************/
/*CLass Mage*/
/*************/
BOOST_AUTO_TEST_CASE(Mage_test)
{
  //Constructor 1
  {
    Mage mage;
    //Get EntityId
    BOOST_CHECK_EQUAL(mage.getEntityId(), MAGE);
    //Get and set Mana
    BOOST_CHECK_EQUAL(mage.getX(), 6);
    BOOST_CHECK_EQUAL(mage.getY(), 6);
    BOOST_CHECK_EQUAL(mage.getMana(), 100);
    BOOST_CHECK_EQUAL(mage.getManaMax(), 100);
    BOOST_CHECK_EQUAL(mage.getSpellDamage(), 45);
    BOOST_CHECK_EQUAL(mage.getSpellAttackRange(), 2);

  }

  //Constructor 2
  {
    Mage mage(10,10);
    //Get and set Mana

    BOOST_CHECK_EQUAL(mage.getX(), 10);
    BOOST_CHECK_EQUAL(mage.getY(), 10);
    BOOST_CHECK_EQUAL(mage.getMana(), 100);
    BOOST_CHECK_EQUAL(mage.getManaMax(), 100);
    BOOST_CHECK_EQUAL(mage.getSpellDamage(), 45);
    BOOST_CHECK_EQUAL(mage.getSpellAttackRange(), 2);
  }

  //Constructor 3
  {
    Mage mage(10,10,50,200,50,100);
    //Get and set Mana

    BOOST_CHECK_EQUAL(mage.getX(), 10);
    BOOST_CHECK_EQUAL(mage.getY(), 10);
    BOOST_CHECK_EQUAL(mage.getMana(), 50);
    BOOST_CHECK_EQUAL(mage.getManaMax(), 200);
    BOOST_CHECK_EQUAL(mage.getSpellDamage(), 50);
    BOOST_CHECK_EQUAL(mage.getSpellAttackRange(), 100);

    mage.setMana(200);
    BOOST_CHECK_EQUAL(mage.getMana(), 200);
  }

  //CastSpell
  {
    Mage mage1(10,10);
    Mage mage2(12,12);
    mage1.castSpell(mage2);// 70-(45-45/5) = 34;
    BOOST_CHECK_EQUAL(mage2.getHealth(),34);

    //CastSpell in order to reach helath = 0 condition
    mage1.castSpell(mage2);// 34-(45-45/5) = 34;
    BOOST_CHECK_EQUAL(mage2.getHealth(),0);
  }

  //Move UP
  {
    State state;
    BOOST_CHECK_EQUAL(state.getMap().getHeight(),25);
    BOOST_CHECK_EQUAL(state.getMap().getWidth(),25);
    Mage mage(10,10);
    BOOST_CHECK_EQUAL(mage.getX(),10);
    BOOST_CHECK_EQUAL(mage.getY(),10);
    mage.move(state,UP);
    BOOST_CHECK_EQUAL(mage.getX(),9);
    BOOST_CHECK_EQUAL(mage.getY(),10);
  }

   //Move RIGHT
  {
    State state;
    BOOST_CHECK_EQUAL(state.getMap().getHeight(),25);
    BOOST_CHECK_EQUAL(state.getMap().getWidth(),25);
    Mage mage(10,10);
    BOOST_CHECK_EQUAL(mage.getX(),10);
    BOOST_CHECK_EQUAL(mage.getY(),10);
    mage.move(state,RIGHT);
    BOOST_CHECK_EQUAL(mage.getX(),10);
    BOOST_CHECK_EQUAL(mage.getY(),11);
  }

   //Move DOWN
  {
    State state;
    BOOST_CHECK_EQUAL(state.getMap().getHeight(),25);
    BOOST_CHECK_EQUAL(state.getMap().getWidth(),25);
    Mage mage(10,10);
    BOOST_CHECK_EQUAL(mage.getX(),10);
    BOOST_CHECK_EQUAL(mage.getY(),10);
    mage.move(state,DOWN);
    BOOST_CHECK_EQUAL(mage.getX(),11);
    BOOST_CHECK_EQUAL(mage.getY(),10);
  }

   //Move LEFT
  {
    State state;
    BOOST_CHECK_EQUAL(state.getMap().getHeight(),25);
    BOOST_CHECK_EQUAL(state.getMap().getWidth(),25);
    Mage mage(10,10);
    BOOST_CHECK_EQUAL(mage.getX(),10);
    BOOST_CHECK_EQUAL(mage.getY(),10);
    mage.move(state,LEFT);
    BOOST_CHECK_EQUAL(mage.getX(),10);
    BOOST_CHECK_EQUAL(mage.getY(),9);
  }

  //MOVE UP OR LEFT WHEN MobileEntity is on the map border TOP (0,0)
  {
    State state;
    BOOST_CHECK_EQUAL(state.getMap().getHeight(),25);
    BOOST_CHECK_EQUAL(state.getMap().getWidth(),25);
    Mage mage(0,0); // x=0 ;y=0
    BOOST_CHECK_EQUAL(mage.getX(),0);
    BOOST_CHECK_EQUAL(mage.getY(),0);

    mage.move(state,LEFT);
    BOOST_CHECK_EQUAL(mage.getX(),0);
    BOOST_CHECK_EQUAL(mage.getY(),0);

    mage.move(state,UP);
    BOOST_CHECK_EQUAL(mage.getX(),0);
    BOOST_CHECK_EQUAL(mage.getY(),0);
  }

  //MOVE DOWN OR RIGHT WHEN MobileEntity is on the map border BOTTOM (25,25)=MAP_SIZE
  {
    State state;
    int mapHeight=state.getMap().getHeight();
    int mapWidth=state.getMap().getWidth();

    BOOST_CHECK_EQUAL(mapHeight,25);
    BOOST_CHECK_EQUAL(mapWidth,25);
    Mage mage(mapHeight-1,mapWidth-1); // x=0 ;y=0
    BOOST_CHECK_EQUAL(mage.getX(),mapHeight-1);
    BOOST_CHECK_EQUAL(mage.getY(),mapWidth-1);

    mage.move(state,RIGHT);
    BOOST_CHECK_EQUAL(mage.getX(),mapHeight-1);
    BOOST_CHECK_EQUAL(mage.getY(),mapWidth-1);

    mage.move(state,DOWN);
    BOOST_CHECK_EQUAL(mage.getX(),mapHeight-1);
    BOOST_CHECK_EQUAL(mage.getY(),mapWidth-1);
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
  //Constructor 1
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

  //Constructor 2
  {
    Cursor cursor(10,10);
    BOOST_CHECK_EQUAL(cursor.getX(), 10);
    BOOST_CHECK_EQUAL(cursor.getY(), 10);

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