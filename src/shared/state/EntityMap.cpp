#include "../state.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace state;
using namespace std;

// Constructor

EntityMap::EntityMap(int level){
    cout<<"ENTITY MAP"<<endl;
        width=1600/32;
        height=800/32;

        ifstream input("rsc/Images/map.txt");
        
        int level1Map_tile[width*height];
        char data;
        for(int k=0;k<width*height;k++){
            input>>data;
            if(data!=','){
                level1Map_tile[k]=int(data);
                
                cout<<data<<' ';
            }
        }



        int k=0;
        for(int i=0;i<50;i++){
            std::vector<std::shared_ptr<StaticEntity>> mapLine;
            for(int j=0;j<25;j++){
                //td::unique_ptr<StaticEntity> ptr_space;
                int var=level1Map_tile[k];
                if(var==GREENSPACETYPE0){
                    std::shared_ptr<StaticEntity> ptr_space (new Space(GREENSPACETYPE0));
                    mapLine.push_back(move(ptr_space));
                }else{
                    std::shared_ptr<StaticEntity> ptr_space(new Space(GREENSPACETYPE1));
                    mapLine.push_back(move(ptr_space));
                }/*else if(var==GREENSPACETYPE2){
                    std::shared_ptr<StaticEntity> ptr_space(new Space(GREENSPACETYPE2));
                    mapLine.push_back(move(ptr_space));
                }else if(var==GREENSPACETYPE3){
                    std::shared_ptr<StaticEntity> ptr_space(new Space(GREENSPACETYPE3));
                    mapLine.push_back(move(ptr_space));
                }else{
                    std::shared_ptr<StaticEntity> ptr_space(new Space(YELLOWSPACETYPE));
                    mapLine.push_back(move(ptr_space));
                }         */       

                k++;
            }
            mapArray.push_back(move(mapLine));

        }
    
}

// Getters

int EntityMap::getWidth(){
    return width;
}

int EntityMap::getHeight(){
    return height;
}

vector<vector<shared_ptr<StaticEntity>>>& EntityMap::getMapArray(){
    return mapArray;
}