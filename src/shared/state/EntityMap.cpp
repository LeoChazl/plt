#include "../state.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace state;
using namespace std;

// Constructor

EntityMap::EntityMap(int level){
    if (level == 1){
        width=50;
        height=25;

        // Open the corresponding csv with the map code tile 
        std::ifstream file("rsc/Images/map.csv", ios::in);    
        std::string content, line, tile_code;
        int map_tile_code[this->width * this->height];

        // Read the file by storing all the data into one string -> content
        if (file){
            while (getline(file,line)){
                line = line + ",";
                content = content + line;
            }
            file.close();
        }

        // Convert into stringStream element in order to use it into getline function
        std::stringstream contentStream(content); 
        int i=0;
        
        while(std::getline(contentStream, tile_code, ',')){ // ',' is a delimiter of a line
            // Convert string tile codes into integers and store it in an array
            map_tile_code[i] = (int) std::stoi(tile_code);
            i++;
        }
        
        // Associate a Space or Obstacle object depending on the tile code and store it in the StaticElement matrix with is the mapArray of the state
        int k=0;
        for(int i=0;i<this->height;i++){
            std::vector<std::shared_ptr<StaticEntity>> mapLine;
            for(int j=0;j<this->width;j++){
                int var=map_tile_code[k];
                
                if(var<8){ // In the map tileset only the first nine tiles are not obstacles
                    std::shared_ptr<StaticEntity> ptr_space (new Space(var));
                    mapLine.push_back(move(ptr_space)); 
                }else{
                    std::shared_ptr<StaticEntity> ptr_obstacle(new Obstacle(var));
                    mapLine.push_back(move(ptr_obstacle));
                }   
                k++;
            }
            mapArray.push_back(move(mapLine));
        }
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