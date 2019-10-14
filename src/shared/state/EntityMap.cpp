#include "EntityMap.h"

using namespace state;
using namespace std;

EntityMap::EntityMap(int level){
    if(level == 1){
        width = 25;
        height = 25;

        int defineSpace;
        ifstream level1("level1.txt");
        if(level1){
            for(int i=0;i<width;i++)
                for(int j=0;j<height;j++){
                    level1 >> defineSpace;
                    if(defineSpace==0)
                        mapArray[i][j].reset(new Space());
                    else
                        mapArray[i][j].reset(new Obstacle());
                }
        }else
            cout << "Error : file for level 1 is not found" << endl;
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