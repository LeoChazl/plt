#include "../render.h"
#include <iostream>

using namespace render;
using namespace state;
using namespace std;

// Functions

bool TextureArea::loadMap(int mapWidth, int mapHeight , string mapImageDirectory){
    texture.loadFromFile(mapImageDirectory);

	quads.setPrimitiveType(sf::Quads);
    quads.resize(4);

	sf::Vertex* quad = &quads[0];
		
	//Définition quatres coins du vertex dans la fenêtre
	quad[0].position = sf::Vector2f(0, 0);
	quad[1].position = sf::Vector2f(mapWidth, 0);
	quad[2].position = sf::Vector2f(mapWidth, mapHeight);
	quad[3].position = sf::Vector2f(0, mapHeight);
		
    //Définition des coordonnées pour récupérer la première texture
	quad[0].texCoords = sf::Vector2f(0, 0);
	quad[1].texCoords = sf::Vector2f(mapWidth, 0);
	quad[2].texCoords = sf::Vector2f(mapWidth, mapHeight);
	quad[3].texCoords = sf::Vector2f(0, mapHeight);
		
	return true;
}

bool TextureArea::loadMap(int mapWidth, int mapHeight , state::State& currentState, render::TileSet& textureTileSet){
    texture = textureTileSet.getTexture();
    quads.setPrimitiveType(sf::Quads);

    /********************************/
    int mapArray[4][10]={{0,1,1,1,1,1,1,1,1,0},
                      {1,1,0,0,0,0,0,0,0,0},
                      {1,1,1,1,1,1,1,1,1,1},
                      {0,0,0,0,0,0,0,0,0,1}
                     };
    
    
    /********************************/
    int vertexArrayIndex = 0;

    for(int i=0;i<sizeof(mapArray);i++){
        for(int j=0;j<sizeof(mapArray[i]);j++){
            quads.resize(quads.getVertexCount() + 4);
            sf::Vertex* quad = &quads[vertexArrayIndex * 4];  
            vertexArrayIndex += 1;

            if(mapArray[i][j]==1){
 
                //Définition quatres coins du vertex dans la fenêtre
	            quad[0].position = sf::Vector2f(i*32, j*32);
            	quad[1].position = sf::Vector2f((i+1)*32, j*32);
	            quad[2].position = sf::Vector2f((i+1)*32, (j+1)*32);
	            quad[3].position = sf::Vector2f(i*32, (j+1)*32);
		
                 //Définition des coordonnées pour récupérer la première texture
                quad[0].texCoords = sf::Vector2f(0, 0);
                quad[1].texCoords = sf::Vector2f(0, 32);
                quad[2].texCoords = sf::Vector2f(32, 32);
                quad[3].texCoords = sf::Vector2f(32, 0);

            }else{

                //Définition quatres coins du vertex dans la fenêtre
	            quad[0].position = sf::Vector2f(i*32, j*32);
            	quad[1].position = sf::Vector2f((i+1)*32, j*32);
	            quad[2].position = sf::Vector2f((i+1)*32, (j+1)*32);
	            quad[3].position = sf::Vector2f(i*32, (j+1)*32);
		
                 //Définition des coordonnées pour récupérer la première texture
                quad[0].texCoords = sf::Vector2f(32, 32);
                quad[1].texCoords = sf::Vector2f(32, 64);
                quad[2].texCoords = sf::Vector2f(64, 64);
                quad[3].texCoords = sf::Vector2f(64, 32);
            }
        }
    }
		
		
	return true;
}

bool TextureArea::loadUnits(state::State& currentState, TileSet& textureTileset){
    texture = textureTileset.getTexture();

    quads.setPrimitiveType(sf::Quads);

    Player currentPlayer;
    int vertexArrayIndex = 0;

    for(unsigned int i=0;i<currentState.getPlayerList().size();i++){
        currentPlayer=*currentState.getPlayerList()[i];
        cout << "Player id: " << currentPlayer.getId() << endl;
        cout << "Number of units: " << currentPlayer.getMobileEntityList().size() << endl;

        for(unsigned int j=0;j<currentPlayer.getMobileEntityList().size();j++){
            quads.resize(quads.getVertexCount() + 4);
            sf::Vertex* quad = &quads[vertexArrayIndex * 4];  
            vertexArrayIndex += 1;

            int tx = currentPlayer.getMobileEntityList()[j]->getEntityId();
            int ty = currentPlayer.getMobileEntityList()[j]->getDirection();

            //Définition quatres coins du vertex dans la fenêtre
            quad[0].position = sf::Vector2f(currentPlayer.getMobileEntityList()[j]->getX() * textureTileset.getCellWidth(),currentPlayer.getMobileEntityList()[j]->getY() * textureTileset.getCellHeight());
            quad[1].position = sf::Vector2f((currentPlayer.getMobileEntityList()[j]->getX()+1) * textureTileset.getCellWidth(),currentPlayer.getMobileEntityList()[j]->getY() * textureTileset.getCellHeight());
            quad[2].position = sf::Vector2f((currentPlayer.getMobileEntityList()[j]->getX()+1) * textureTileset.getCellWidth(),(currentPlayer.getMobileEntityList()[j]->getY()+1) * textureTileset.getCellHeight());
            quad[3].position = sf::Vector2f(currentPlayer.getMobileEntityList()[j]->getX() * textureTileset.getCellWidth(),(currentPlayer.getMobileEntityList()[j]->getY()+1) * textureTileset.getCellHeight());
            
            //Définition des coordonnées pour récupérer la bonne texture
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