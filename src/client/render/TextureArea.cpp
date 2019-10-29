#include "../render.h"
#include <iostream>
#include <fstream>

using namespace render;
using namespace state;
using namespace std;

// Functions

bool TextureArea::loadMap(int mapWidth, int mapHeight , string mapImageDirectory){
    texture.loadFromFile(mapImageDirectory);

	quads.setPrimitiveType(sf::Quads);
    quads.resize(4);//quads--> a vertex array with 4 vertex 

	sf::Vertex* quad = &quads[0]; //pointor to the first vertex element of quads
		
	//	Definition of the four corners of the vertex in the window
	quad[0].position = sf::Vector2f(0, 0);
	quad[1].position = sf::Vector2f(mapWidth, 0);
	quad[2].position = sf::Vector2f(mapWidth, mapHeight);
	quad[3].position = sf::Vector2f(0, mapHeight);
		
    //Definition of coordinates to retrieve the first texture
	quad[0].texCoords = sf::Vector2f(0, 0);
	quad[1].texCoords = sf::Vector2f(mapWidth, 0);
	quad[2].texCoords = sf::Vector2f(mapWidth, mapHeight);
	quad[3].texCoords = sf::Vector2f(0, mapHeight);
		
	return true;
}


bool TextureArea::loadMap(int mapWidth, int mapHeight , state::State& currentState, render::TileSet& textureTileSet){
         //std::ifstream file("rsc/Images/csvMap.csv", ios::in);
		texture = textureTileSet.getTexture();
		
      	// on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
	   	quads.setPrimitiveType(sf::Quads);
       	quads.resize(int(mapWidth * mapHeight * 4/32/32));

       int map_code_tuile[25][50]={{1,1,1,1,1,1,1,1,1,1,1,19,19,19,0,0,0,0,2,2,2,5,2,2,2,2,2,4,2,2,2,2,0,0,0,0,19,19,19,1,1,1,1,1,1,1,1,1,1,1},
{1,18,1,1,1,1,1,1,1,1,19,19,19,19,0,0,0,0,2,2,4,2,2,2,2,5,2,2,2,2,2,2,0,0,0,0,19,19,19,19,1,1,17,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,19,20,19,0,0,0,0,0,2,2,24,27,27,27,27,30,30,30,30,33,2,4,0,0,0,0,0,19,20,19,1,1,1,1,1,1,16,1,1,1},
{1,1,1,1,1,1,15,1,1,1,19,19,19,0,0,0,0,0,5,2,25,28,28,28,28,31,31,31,31,34,2,2,0,0,0,0,0,19,19,19,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,19,19,19,0,0,0,0,0,2,2,26,29,29,29,29,32,32,32,32,35,2,2,0,0,0,0,0,19,19,19,1,1,17,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,19,19,19,19,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,19,19,19,1,1,11,1,1,1,1,1,17,1},
{1,15,1,1,1,1,1,1,19,20,19,19,0,0,0,0,0,0,0,2,2,5,2,2,2,2,2,2,4,2,2,0,0,0,0,0,0,0,19,19,20,19,1,1,16,1,1,1,1,1},
{1,1,1,1,1,1,1,19,19,19,19,0,0,0,23,0,0,0,0,0,2,2,2,2,4,2,2,5,2,2,0,0,0,0,0,23,0,0,0,19,19,19,19,1,1,1,1,1,1,1},
{1,1,1,1,1,18,9,11,11,11,11,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,21,0,0,0,0,0,0,0,0,10,11,11,11,11,9,1,1,1,1,1,1},
{1,1,1,1,1,1,6,8,8,8,8,7,0,0,0,0,0,0,0,0,21,0,0,0,0,0,0,0,0,21,0,0,0,0,0,0,0,0,7,8,8,8,8,6,1,1,1,1,1,1},
{1,1,1,1,1,1,6,8,8,8,8,7,0,0,0,0,0,0,0,0,21,0,0,0,0,0,0,0,0,0,0,0,22,0,0,0,0,0,7,8,8,8,8,6,1,1,1,1,1,1},
{1,1,1,1,1,1,6,8,8,8,8,7,0,0,0,22,0,0,0,0,0,0,0,0,0,0,0,21,0,0,0,0,0,0,0,0,0,0,7,8,8,8,8,6,1,1,1,1,1,1},
{1,1,1,1,1,1,6,8,8,8,8,7,0,0,0,0,0,0,0,0,0,21,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,8,8,8,8,6,1,1,1,1,1,1},
{1,1,1,1,1,1,12,14,14,14,14,13,0,0,0,0,0,0,3,3,49,50,50,50,50,50,50,50,50,51,3,3,0,0,0,0,0,0,7,8,8,8,8,6,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,19,19,19,19,23,0,0,0,0,0,46,3,3,45,45,45,3,3,45,45,45,3,3,46,0,0,0,0,0,23,19,19,19,19,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,19,19,20,19,0,0,0,0,0,0,47,3,3,3,3,3,3,3,3,3,3,3,3,47,0,0,22,0,0,0,19,20,19,19,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,19,19,19,19,0,0,0,0,0,47,3,3,3,3,3,3,3,3,3,3,3,3,47,0,0,0,0,0,19,19,19,19,1,1,1,1,1,1,18,1,1},
{1,1,1,1,16,1,1,1,1,1,19,19,19,19,0,0,22,0,48,36,3,3,3,3,3,3,3,3,3,3,37,48,0,0,0,0,19,19,19,19,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,17,1,1,1,19,19,19,0,0,0,3,3,3,3,3,40,43,43,38,3,3,3,3,3,0,0,0,0,19,19,19,1,1,15,1,1,1,1,1,1,1,1},
{1,1,17,1,1,1,1,1,1,1,1,19,19,19,0,0,0,0,3,3,3,3,3,43,3,3,43,3,3,3,3,3,0,0,0,0,19,19,19,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,19,19,19,0,0,0,0,46,3,3,3,3,3,3,3,3,3,3,3,3,46,0,0,0,0,19,20,19,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,16,1,1,1,1,1,1,19,20,19,0,0,0,0,47,3,3,3,3,41,42,41,42,3,3,3,3,47,0,0,0,0,19,19,19,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,17,1,1,19,19,19,0,0,0,0,47,3,3,3,3,3,3,3,3,3,3,3,3,47,0,0,0,0,19,19,19,1,1,1,18,1,1,1,1,1,15,1},
{1,1,1,1,1,1,1,1,1,1,1,19,19,19,19,0,0,0,47,39,39,39,3,3,3,3,3,3,44,44,44,47,0,0,0,19,19,19,19,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,19,19,19,19,0,47,39,39,39,3,3,3,3,3,3,44,44,44,47,0,0,19,19,19,19,1,1,1,1,1,1,1,1,1,1,1,1}};

        int vertexArrayIndex=0;
        // on remplit le tableau de vertex, avec un quad par tuile
        for (unsigned int i = 0; i < int(25); i++){
            for (unsigned int j = 0; j < int(50); j++){

                std::vector<std::vector<shared_ptr<StaticEntity>>> map;
                map=currentState.getEntityMap().getMapArray();
            	// on récupère le numéro de tuile courant
				//int tileNumber=map[i][j]->getSpaceTypeID();
                int tileNumber= map_code_tuile[i][j];
				
                // on en déduit sa position dans la texture du tileset
                int tu = tileNumber % ( 320/ 32);
                int tv = tileNumber / (320 / 32);

                //cout<<"/***************************/"<<endl;
                /*cout<<"i= "<<i<<" j= "<<j<<endl;
                cout<<"tileNumber= "<<tileNumber<<endl;
                cout<<"tu ="<<tu<<" tv= "<<tv<<endl;*/
                //cout<<"/***************************/"<<endl;

                // on récupère un pointeur vers le quad à définir dans le tableau de vertex
                sf::Vertex* quad = &quads[vertexArrayIndex* 4];
				vertexArrayIndex++;
				// on définit ses quatre coins
                //Définition quatres coins du vertex dans la fenêtre
	            quad[0].position = sf::Vector2f(j*32, i*32);
            	quad[1].position = sf::Vector2f(j*32, (i+1)*32);
	            quad[2].position = sf::Vector2f((j+1)*32, (i+1)*32);
	            quad[3].position = sf::Vector2f((j+1)*32, i*32);

                quad[0].texCoords = sf::Vector2f(tu * 32, tv * 32);
				quad[1].texCoords = sf::Vector2f((tu + 1) * 32, tv * 32);
				quad[2].texCoords = sf::Vector2f((tu + 1) * 32, (tv + 1) * 32);
				quad[3].texCoords = sf::Vector2f(tu * 32, (tv + 1) * 32);

               
                
		
           }
		}
		return true;	

}

bool TextureArea::loadUnits(state::State& currentState, TileSet& textureTileset){
    texture = textureTileset.getTexture(); //Recover the sf::Texture with TileSet image loaded initialised in render::TileSet Class

    quads.setPrimitiveType(sf::Quads);

    Player currentPlayer;//Initialise Player class object in order to have the list of units belonging to each player
    int vertexArrayIndex = 0;

    //for each player initialized in the state object 
    for(unsigned int i=0;i<currentState.getPlayerList().size();i++){
        currentPlayer=*currentState.getPlayerList()[i];//take the value of one player pointor adn store it in Player type variable
        cout << "Player id: " << currentPlayer.getId() << endl;
        cout << "Number of units: " << currentPlayer.getMobileEntityList().size() << endl;

        //for each units controlled by the player choose before 
        for(unsigned int j=0;j<currentPlayer.getMobileEntityList().size();j++){
            quads.resize(quads.getVertexCount() + 4);
            sf::Vertex* quad = &quads[vertexArrayIndex * 4];  
            vertexArrayIndex += 1;

            int tx = currentPlayer.getMobileEntityList()[j]->getEntityId();
            int ty = currentPlayer.getMobileEntityList()[j]->getDirection();

            //Definition of the four corners of the vertex in the window
               //2 coordinate(x,y) for each vertx--> x = the unit X position in the map product the width of the unit tileSet
               //                                --> y = the unit Y position in the map product the height of the unit tileSet
            quad[0].position = sf::Vector2f(currentPlayer.getMobileEntityList()[j]->getX() * textureTileset.getCellWidth(),currentPlayer.getMobileEntityList()[j]->getY() * textureTileset.getCellHeight());
            quad[1].position = sf::Vector2f((currentPlayer.getMobileEntityList()[j]->getX()+1) * textureTileset.getCellWidth(),currentPlayer.getMobileEntityList()[j]->getY() * textureTileset.getCellHeight());
            quad[2].position = sf::Vector2f((currentPlayer.getMobileEntityList()[j]->getX()+1) * textureTileset.getCellWidth(),(currentPlayer.getMobileEntityList()[j]->getY()+1) * textureTileset.getCellHeight());
            quad[3].position = sf::Vector2f(currentPlayer.getMobileEntityList()[j]->getX() * textureTileset.getCellWidth(),(currentPlayer.getMobileEntityList()[j]->getY()+1) * textureTileset.getCellHeight());
            
            //Definition of coordinates to retrieve the first texture
               //same as quads position
            quad[0].texCoords = sf::Vector2f(tx * textureTileset.getCellWidth(), ty * textureTileset.getCellHeight());
            quad[1].texCoords = sf::Vector2f((tx+1) * textureTileset.getCellWidth(), ty * textureTileset.getCellHeight());
            quad[2].texCoords = sf::Vector2f((tx+1) * textureTileset.getCellWidth(), (ty+1) * textureTileset.getCellHeight());
            quad[3].texCoords = sf::Vector2f(tx * textureTileset.getCellWidth(), (ty+1) * textureTileset.getCellHeight());
        }
    }
    return true;
}

bool TextureArea::loadCursor(state::State& currentState, TileSet& textureTileset){ 			
	texture = textureTileset.getTexture();

    quads.setPrimitiveType(sf::Quads);
    quads.resize(4);

	sf::Vertex* quad = &quads[0];
		
	//Définition quatres coins du vertex dans la fenêtre
	quad[0].position = sf::Vector2f(currentState.getCursor().getX() * textureTileset.getCellWidth(), currentState.getCursor().getY() * textureTileset.getCellHeight());
	quad[1].position = sf::Vector2f((currentState.getCursor().getX() + 1) * textureTileset.getCellWidth(), currentState.getCursor().getY() * textureTileset.getCellHeight());
	quad[2].position = sf::Vector2f((currentState.getCursor().getX() + 1) * textureTileset.getCellWidth(), (currentState.getCursor().getY() + 1) * textureTileset.getCellHeight());
	quad[3].position = sf::Vector2f(currentState.getCursor().getX() * textureTileset.getCellWidth(), (currentState.getCursor().getY() + 1) * textureTileset.getCellHeight());
		
    //Définition des coordonnées pour récupérer la première texture
	quad[0].texCoords = sf::Vector2f(0, 0);
	quad[1].texCoords = sf::Vector2f(textureTileset.getCellWidth(), 0);
	quad[2].texCoords = sf::Vector2f(textureTileset.getCellWidth(), textureTileset.getCellHeight());
	quad[3].texCoords = sf::Vector2f(0, textureTileset.getCellHeight());
		
	return true;
}

void TextureArea::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        // Apply a transformation
        states.transform *= getTransform();

        // Apply texture of the tileset
        states.texture = &texture;

        // Draw the table with the vertex
        target.draw(quads, states);
}