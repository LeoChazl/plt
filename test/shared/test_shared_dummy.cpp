
#include <boost/test/unit_test.hpp>


using namespace ::std;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestExemple)
{
  {
    BOOST_CHECK_EQUAL(1,1);
    BOOST_CHECK(true);
  }

  {

  }

  {
    /*Troll ex {};
    BOOST_CHECK_EQUAL(ex.x, 0);
    ex.setX(21);
    BOOST_CHECK_EQUAL(ex.x, 21);*/
  }

  {
    /*roll ex {};
    ex.setX(21);
    BOOST_CHECK_LE(ex.x, 32); // Less than equal
    BOOST_CHECK_GT(ex.x, 11); // Greater than equl*/
  }
}

/* vim: set sw=2 sts=2 et : */
