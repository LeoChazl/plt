#include "../render.h"

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
                texture = textureTileset[TROLL]->getTexture();

                int tx = TROLL; //on ne prend que dans la première colonne pour l'instant
                int ty = currentPlayer.getMobileEntityList()[j]->getDirection() * 64;

                //Définition quatres coins du vertex dans la fenêtre
                quad[0].position = sf::Vector2f(currentPlayer.getMobileEntityList()[j]->getX() * textureTileset[TROLL]->getCellWidth(),currentPlayer.getMobileEntityList()[j]->getY() * textureTileset[TROLL]->getCellHeight());
                quad[1].position = sf::Vector2f((currentPlayer.getMobileEntityList()[j]->getX()+1) * textureTileset[TROLL]->getCellWidth(),currentPlayer.getMobileEntityList()[j]->getY() * textureTileset[TROLL]->getCellHeight());
                quad[2].position = sf::Vector2f((currentPlayer.getMobileEntityList()[j]->getX()+1) * textureTileset[TROLL]->getCellWidth(),(currentPlayer.getMobileEntityList()[j]->getY()+1) * textureTileset[TROLL]->getCellHeight());
                quad[3].position = sf::Vector2f(currentPlayer.getMobileEntityList()[j]->getX() * textureTileset[TROLL]->getCellWidth(),(currentPlayer.getMobileEntityList()[j]->getY()+1) * textureTileset[TROLL]->getCellHeight());

                //Définition des coordonnées pour récupérer la bonne texture
                quad[0].texCoords = sf::Vector2f(tx * textureTileset[TROLL]->getCellWidth(), ty * textureTileset[TROLL]->getCellHeight());
                quad[1].texCoords = sf::Vector2f((tx+1) * textureTileset[TROLL]->getCellWidth(), ty * textureTileset[TROLL]->getCellHeight());
                quad[2].texCoords = sf::Vector2f((tx+1) * textureTileset[TROLL]->getCellWidth(), (ty+1) * textureTileset[TROLL]->getCellHeight());
                quad[3].texCoords = sf::Vector2f(tx * textureTileset[TROLL]->getCellWidth(), (ty+1) * textureTileset[TROLL]->getCellHeight());
            } 
            else if(currentPlayer.getMobileEntityList()[j]->getEntityId()==MAGE){
                texture = textureTileset[MAGE]->getTexture();

                int tx = MAGE; //on ne prend que dans la première colonne pour l'instant
                int ty = currentPlayer.getMobileEntityList()[j]->getDirection() * 64;

                //Définition quatres coins du vertex dans la fenêtre
                quad[0].position = sf::Vector2f(currentPlayer.getMobileEntityList()[j]->getX() * textureTileset[MAGE]->getCellWidth(),currentPlayer.getMobileEntityList()[j]->getY() * textureTileset[MAGE]->getCellHeight());
                quad[1].position = sf::Vector2f((currentPlayer.getMobileEntityList()[j]->getX()+1) * textureTileset[MAGE]->getCellWidth(),currentPlayer.getMobileEntityList()[j]->getY() * textureTileset[MAGE]->getCellHeight());
                quad[2].position = sf::Vector2f((currentPlayer.getMobileEntityList()[j]->getX()+1) * textureTileset[MAGE]->getCellWidth(),(currentPlayer.getMobileEntityList()[j]->getY()+1) * textureTileset[MAGE]->getCellHeight());
                quad[3].position = sf::Vector2f(currentPlayer.getMobileEntityList()[j]->getX() * textureTileset[MAGE]->getCellWidth(),(currentPlayer.getMobileEntityList()[j]->getY()+1) * textureTileset[MAGE]->getCellHeight());

                //Définition des coordonnées pour récupérer la bonne texture
                quad[0].texCoords = sf::Vector2f(tx * textureTileset[MAGE]->getCellWidth(), ty * textureTileset[MAGE]->getCellHeight());
                quad[1].texCoords = sf::Vector2f((tx+1) * textureTileset[MAGE]->getCellWidth(), ty * textureTileset[MAGE]->getCellHeight());
                quad[2].texCoords = sf::Vector2f((tx+1) * textureTileset[MAGE]->getCellWidth(), (ty+1) * textureTileset[MAGE]->getCellHeight());
                quad[3].texCoords = sf::Vector2f(tx * textureTileset[MAGE]->getCellWidth(), (ty+1) * textureTileset[MAGE]->getCellHeight());
            }
            else if(currentPlayer.getMobileEntityList()[j]->getEntityId()==KNIGHT){
                texture = textureTileset[KNIGHT]->getTexture();

                int tx = KNIGHT; //on ne prend que dans la première colonne pour l'instant
                int ty = currentPlayer.getMobileEntityList()[j]->getDirection() * 64;

                //Définition quatres coins du vertex dans la fenêtre
                quad[0].position = sf::Vector2f(currentPlayer.getMobileEntityList()[j]->getX() * textureTileset[KNIGHT]->getCellWidth(),currentPlayer.getMobileEntityList()[j]->getY() * textureTileset[KNIGHT]->getCellHeight());
                quad[1].position = sf::Vector2f((currentPlayer.getMobileEntityList()[j]->getX()+1) * textureTileset[KNIGHT]->getCellWidth(),currentPlayer.getMobileEntityList()[j]->getY() * textureTileset[KNIGHT]->getCellHeight());
                quad[2].position = sf::Vector2f((currentPlayer.getMobileEntityList()[j]->getX()+1) * textureTileset[KNIGHT]->getCellWidth(),(currentPlayer.getMobileEntityList()[j]->getY()+1) * textureTileset[KNIGHT]->getCellHeight());
                quad[3].position = sf::Vector2f(currentPlayer.getMobileEntityList()[j]->getX() * textureTileset[KNIGHT]->getCellWidth(),(currentPlayer.getMobileEntityList()[j]->getY()+1) * textureTileset[KNIGHT]->getCellHeight());

                //Définition des coordonnées pour récupérer la bonne texture
                quad[0].texCoords = sf::Vector2f(tx * textureTileset[KNIGHT]->getCellWidth(), ty * textureTileset[KNIGHT]->getCellHeight());
                quad[1].texCoords = sf::Vector2f((tx+1) * textureTileset[KNIGHT]->getCellWidth(), ty * textureTileset[KNIGHT]->getCellHeight());
                quad[2].texCoords = sf::Vector2f((tx+1) * textureTileset[KNIGHT]->getCellWidth(), (ty+1) * textureTileset[KNIGHT]->getCellHeight());
                quad[3].texCoords = sf::Vector2f(tx * textureTileset[KNIGHT]->getCellWidth(), (ty+1) * textureTileset[KNIGHT]->getCellHeight());
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

void TextureArea::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        // Apply a transformation
        states.transform *= getTransform();

        // Apply texture of the tileset
        states.texture = &texture;

        // Draw the table with the vertex
        target.draw(quads, states);
}