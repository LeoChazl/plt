#include "../state.h"

using namespace state;
using namespace std;

// Constructors

Knight::Knight(){
    MobileEntity(15,15,100,2,35,15,100,KNIGHT,AVAILABLE,DOWN);
}

Knight::Knight(int x, int y){
    MobileEntity(x,y,100,2,35,15,100,KNIGHT,AVAILABLE,DOWN);
}