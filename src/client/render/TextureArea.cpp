#include "../render.h"
#include "state.h"
#include <string>

using namespace render;
using namespace state;
using namespace std;

// Functions

bool TextureArea::loadBattleField(int mapHeight, int mapWidth , string mapImageDirectory){
     return texture.loadFromFile(mapImageDirectory);
}

bool TextureArea::loadUnits(state::State& currentState, vector<unique_ptr<TileSet>>& textureTileset){

    quads.setPrimitiveType(sf::Quads);

    Player currentPlayer;
    int vertexArrayIndex = 0;

    for(unsigned int i=0;i<currentState.getPlayerList().size();i++){
        currentPlayer=*currentState.getPlayerList()[i];
        for(unsigned int j=0;j<currentPlayer.getMobileEntityList().size();j++){
            quads.resize(quads.getVertexCount() + 4);
            sf::Vertex* quad = &quads[vertexArrayIndex * 4];  
            vertexArrayIndex += 1;

            if(currentPlayer.getMobileEntityList()[j]->getEntityId()==TROLL){
                texture = textureTileset[TROLLTILESET]->getTexture();

                int tx = 1; //on ne prend que dans la première colonne pour l'instant
                int ty = currentPlayer.getMobileEntityList()[j]->getDirection() * 64;

                //Définition quatres coins du vertex dans la fenêtre
                quad[0].position = sf::Vector2f(currentPlayer.getMobileEntityList()[j]->getX() * textureTileset[TROLLTILESET]->getCellWidth(),currentPlayer.getMobileEntityList()[j]->getY() * textureTileset[TROLLTILESET]->getCellHeight());
                quad[1].position = sf::Vector2f((currentPlayer.getMobileEntityList()[j]->getX()+1) * textureTileset[TROLLTILESET]->getCellWidth(),currentPlayer.getMobileEntityList()[j]->getY() * textureTileset[TROLLTILESET]->getCellHeight());
                quad[2].position = sf::Vector2f((currentPlayer.getMobileEntityList()[j]->getX()+1) * textureTileset[TROLLTILESET]->getCellWidth(),(currentPlayer.getMobileEntityList()[j]->getY()+1) * textureTileset[TROLLTILESET]->getCellHeight());
                quad[3].position = sf::Vector2f(currentPlayer.getMobileEntityList()[j]->getX() * textureTileset[TROLLTILESET]->getCellWidth(),(currentPlayer.getMobileEntityList()[j]->getY()+1) * textureTileset[TROLLTILESET]->getCellHeight());

                //Définition des coordonnées pour récupérer la bonne texture
                quad[0].texCoords = sf::Vector2f(tx * textureTileset[TROLLTILESET]->getCellWidth(), ty * textureTileset[TROLLTILESET]->getCellHeight());
                quad[1].texCoords = sf::Vector2f((tx+1) * textureTileset[TROLLTILESET]->getCellWidth(), ty * textureTileset[TROLLTILESET]->getCellHeight());
                quad[2].texCoords = sf::Vector2f((tx+1) * textureTileset[TROLLTILESET]->getCellWidth(), (ty+1) * textureTileset[TROLLTILESET]->getCellHeight());
                quad[3].texCoords = sf::Vector2f(tx * textureTileset[TROLLTILESET]->getCellWidth(), (ty+1) * textureTileset[TROLLTILESET]->getCellHeight());
            } 
            else if(currentPlayer.getMobileEntityList()[j]->getEntityId()==MAGE){
                texture = textureTileset[MAGETILESET]->getTexture();

                int tx = 1; //on ne prend que dans la première colonne pour l'instant
                int ty = currentPlayer.getMobileEntityList()[j]->getDirection() * 64;

                //Définition quatres coins du vertex dans la fenêtre
                quad[0].position = sf::Vector2f(currentPlayer.getMobileEntityList()[j]->getX() * textureTileset[MAGETILESET]->getCellWidth(),currentPlayer.getMobileEntityList()[j]->getY() * textureTileset[MAGETILESET]->getCellHeight());
                quad[1].position = sf::Vector2f((currentPlayer.getMobileEntityList()[j]->getX()+1) * textureTileset[MAGETILESET]->getCellWidth(),currentPlayer.getMobileEntityList()[j]->getY() * textureTileset[MAGETILESET]->getCellHeight());
                quad[2].position = sf::Vector2f((currentPlayer.getMobileEntityList()[j]->getX()+1) * textureTileset[MAGETILESET]->getCellWidth(),(currentPlayer.getMobileEntityList()[j]->getY()+1) * textureTileset[MAGETILESET]->getCellHeight());
                quad[3].position = sf::Vector2f(currentPlayer.getMobileEntityList()[j]->getX() * textureTileset[MAGETILESET]->getCellWidth(),(currentPlayer.getMobileEntityList()[j]->getY()+1) * textureTileset[MAGETILESET]->getCellHeight());

                //Définition des coordonnées pour récupérer la bonne texture
                quad[0].texCoords = sf::Vector2f(tx * textureTileset[MAGETILESET]->getCellWidth(), ty * textureTileset[MAGETILESET]->getCellHeight());
                quad[1].texCoords = sf::Vector2f((tx+1) * textureTileset[MAGETILESET]->getCellWidth(), ty * textureTileset[MAGETILESET]->getCellHeight());
                quad[2].texCoords = sf::Vector2f((tx+1) * textureTileset[MAGETILESET]->getCellWidth(), (ty+1) * textureTileset[MAGETILESET]->getCellHeight());
                quad[3].texCoords = sf::Vector2f(tx * textureTileset[MAGETILESET]->getCellWidth(), (ty+1) * textureTileset[MAGETILESET]->getCellHeight());
            }
            else if(currentPlayer.getMobileEntityList()[j]->getEntityId()==KNIGHT){
                texture = textureTileset[KNIGHTTILESET]->getTexture();

                int tx = 1; //on ne prend que dans la première colonne pour l'instant
                int ty = currentPlayer.getMobileEntityList()[j]->getDirection() * 64;

                //Définition quatres coins du vertex dans la fenêtre
                quad[0].position = sf::Vector2f(currentPlayer.getMobileEntityList()[j]->getX() * textureTileset[KNIGHTTILESET]->getCellWidth(),currentPlayer.getMobileEntityList()[j]->getY() * textureTileset[KNIGHTTILESET]->getCellHeight());
                quad[1].position = sf::Vector2f((currentPlayer.getMobileEntityList()[j]->getX()+1) * textureTileset[KNIGHTTILESET]->getCellWidth(),currentPlayer.getMobileEntityList()[j]->getY() * textureTileset[KNIGHTTILESET]->getCellHeight());
                quad[2].position = sf::Vector2f((currentPlayer.getMobileEntityList()[j]->getX()+1) * textureTileset[KNIGHTTILESET]->getCellWidth(),(currentPlayer.getMobileEntityList()[j]->getY()+1) * textureTileset[KNIGHTTILESET]->getCellHeight());
                quad[3].position = sf::Vector2f(currentPlayer.getMobileEntityList()[j]->getX() * textureTileset[KNIGHTTILESET]->getCellWidth(),(currentPlayer.getMobileEntityList()[j]->getY()+1) * textureTileset[KNIGHTTILESET]->getCellHeight());

                //Définition des coordonnées pour récupérer la bonne texture
                quad[0].texCoords = sf::Vector2f(tx * textureTileset[KNIGHTTILESET]->getCellWidth(), ty * textureTileset[KNIGHTTILESET]->getCellHeight());
                quad[1].texCoords = sf::Vector2f((tx+1) * textureTileset[KNIGHTTILESET]->getCellWidth(), ty * textureTileset[KNIGHTTILESET]->getCellHeight());
                quad[2].texCoords = sf::Vector2f((tx+1) * textureTileset[KNIGHTTILESET]->getCellWidth(), (ty+1) * textureTileset[KNIGHTTILESET]->getCellHeight());
                quad[3].texCoords = sf::Vector2f(tx * textureTileset[KNIGHTTILESET]->getCellWidth(), (ty+1) * textureTileset[KNIGHTTILESET]->getCellHeight());
            }
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