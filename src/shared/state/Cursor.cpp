#include "../state.h"

using namespace state;
using namespace std;


Cursor::Cursor(){
    Position(x,y);
}   

void Cursor::moveCursor (int x, int y){
    this->x=x;
    this->y=y;
}
