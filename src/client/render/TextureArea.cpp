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
    for(unsigned int i=0;i<currentState.getPlayerList().size();i++){
        currentPlayer=*currentState.getPlayerList()[i];
        for(unsigned int j=0;j<currentPlayer.getMobileEntityList().size();j++){
            if(currentPlayer.getMobileEntityList()[j]->getEntityId()==TROLL){
                texture = textureTileset[TROLLTILESET]->getTexture();

                quads.resize(quads.getVertexCount() + textureTileset[TROLLTILESET]->getCellHeight() * textureTileset[TROLLTILESET]->getCellWidth() * 4);

                int tx = 1; //on ne prend que dans la première colonne pour
                int ty = currentPlayer.getMobileEntityList()[j]->getDirection() * 64;

                sf::Vertex* quad = &quads[i * 4];  
            }
        }
    }
}

bool TextureArea::loadCursor(state::State& currentState, TileSet& textureTileset){
    
}