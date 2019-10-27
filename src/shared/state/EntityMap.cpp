#include "../state.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace state;
using namespace std;

// Constructor

EntityMap::EntityMap(int level){
    cout<<"ENTITY MAP"<<endl;
        width=50;
        height=25;

        ifstream input("rsc/Images/csvMap.csv");
        
        int level1Map_tile[width*height];
        char data;
        for(int k=0;k<width*height;k++){
            input>>data;
            if(data!=','){
                level1Map_tile[k]=int(data);
                
                cout<<data;
            }
        }

        //int k=0;
        //this way we read the txt file.
       /* std::string content, line, tilecode;
        if (!level1Map_file)
            return;
        while (getline(level1Map_file, line))
        {
            line += ",";
            content += line;
        }
        level1Map_file.close();
            cout<<"e2.1"<<endl;


        // from string to stream
        std::stringstream contentStream(content);
        cout<<"e2.2"<<endl;

        // delimiting by comma
        while (std::getline(contentStream, tilecode, ','))
        {
            level1Map_tile[k] = std::stoi(tilecode);
            k++;
                cout<<"e2.3"<<endl;

        }*/
        /*int i=0;
        ifstream file("rsc/Images/level1.txt", ios::in);
        int level1Map_tile[width * height];
    

        //this way we read the txt file.
        std::string content, line, tilecode;
        if (!file)
            return;
            cout<<"e1"<<endl;
        while (getline(file, line))
        {
            line += ",";
            content += line;
            cout<<line<<endl;
            cout<<"e2"<<endl;
        }
        file.close();
        cout<<"e3"<<endl;
        // from string to stream
       std::stringstream contentStream(content);

        // delimiting by comma
        while (std::getline(contentStream, tilecode, ','))
        {
            level1Map_tile[i] = std::stoi(tilecode);
            i++;
            cout<<level1Map_tile[i]<<endl;
        }*/
    /*************************/

        int k=0;
        for(int i=0;i<50;i++){
            std::vector<std::shared_ptr<StaticEntity>> mapLine;
            for(int j=0;j<25;j++){
                //td::unique_ptr<StaticEntity> ptr_space;
                int var=level1Map_tile[k];
                if(var==GREENSPACETYPE0){
                    std::shared_ptr<StaticEntity> ptr_space (new Space(GREENSPACETYPE0));
                    mapLine.push_back(move(ptr_space));
                }else if(var==GREENSPACETYPE1){
                    std::shared_ptr<StaticEntity> ptr_space(new Space(GREENSPACETYPE1));
                    mapLine.push_back(move(ptr_space));
                }else if(var==GREENSPACETYPE2){
                    std::shared_ptr<StaticEntity> ptr_space(new Space(GREENSPACETYPE2));
                    mapLine.push_back(move(ptr_space));
                }else if(var==GREENSPACETYPE3){
                    std::shared_ptr<StaticEntity> ptr_space(new Space(GREENSPACETYPE3));
                    mapLine.push_back(move(ptr_space));
                }else{
                    std::shared_ptr<StaticEntity> ptr_space(new Space(YELLOWSPACETYPE));
                    mapLine.push_back(move(ptr_space));
                }                

                k++;
            }
            mapArray.push_back(mapLine);

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