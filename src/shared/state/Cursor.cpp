#include "../state.h"

using namespace state;
using namespace std;

// Constructors

Cursor::Cursor():Position()
{
    this->codeTuile=0;
}

Cursor::Cursor(int x, int y):Position(x,y)
{
    this->codeTuile=0;
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

// Getter
int Cursor::getCodeTuile(){
    return codeTuile;
}

// Setter
void Cursor::setCodeTuile(int newCodeTuile){
    this->codeTuile=newCodeTuile;
}
