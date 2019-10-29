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

       /* ifstream input("rsc/Images/map.txt");
        
        int level1Map_tile[width*height];
        char data;
        for(int k=0;k<width*height;k++){
            input>>data;
            if(data!=','){
                level1Map_tile[k]=int(data);
                
                cout<<data<<' ';
            }
        }*/
	/**************************************/
	/*Step 1 : open the map tile code file*/
	/**************************************/	
    std::ifstream fichier("rsc/Images/map.csv", ios::in);    
    std::string contenu, ligne, code_tuile;
    int map_code_tuile[25*50];


	/***********************************************************/
	/*Step 2 : Store all file elemet into one string -> contenu*/
	/**********************************************************/	
    // Lecture Fichier
    if (fichier){
    	while (getline(fichier,ligne)){
			ligne = ligne + ",";
			contenu = contenu + ligne;
		}
		fichier.close();
    }


    
	/***********************************************************************************/
	/*Step 3 : Convert all string code tuile into "int" element and store it in ana array*/
	/***********************************************************************************/	
    // Conversion des codes des tuiles en int
    std::stringstream contenuStream(contenu); // convert into stringStream element in order to use it into getline function
    int i=0;
    
    while(std::getline(contenuStream, code_tuile, ',')){// ',' is a delimiter of the line
    	map_code_tuile[i] = (int) std::stoi(code_tuile);//convert string into "int" value and store it in an array
    	i++;
    }
    
    /***********************************************************************************/
	/*Step 4 : Associate a Space or Obstacle object to the code Tuile and store it in an StaticELement matrix*/
	/***********************************************************************************/	
    int k=0;
    for(int i=0;i<25;i++){
        std::vector<std::shared_ptr<StaticEntity>> mapLine;
        for(int j=0;j<50;j++){
            int var=map_code_tuile[k];

            if(var<5){
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