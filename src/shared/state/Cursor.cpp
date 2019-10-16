#include "../state.h"

using namespace state;
using namespace std;

// Constructors

Cursor::Cursor():Position()
{

}

Cursor::Cursor(int x, int y):Position(x,y)
{

}

// Function

/** Change cursor position
 * 
 * param :
 * x -> new x coordinate
 * y -> new y coordinate
 */
void Cursor::moveCursor (int x, int y){
    this->x=x;
    this->y=y;
}
