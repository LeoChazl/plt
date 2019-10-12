#include "EntityMap.h"

using namespace state;
using namespace std;

EntityMap::EntityMap(int level){
    if(level == 1){
        width = 25;
        height = 25;
    }
}

int EntityMap::getWidth(){
    return width;
}

int EntityMap::getHeight(){
    return height;
}

vector<vector<shared_ptr<StaticEntity>>> EntityMap::getMapArray(){
    return mapArray;
}