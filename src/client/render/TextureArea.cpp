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

bool TextureArea::loadUnits(state::State& currentState, map<int,TileSet&> textureTileset){

    quads.setPrimitiveType(sf::Quads);

    Player currentPlayer;
    for(unsigned int i=0;i<currentState.getPlayerList().size();i++){
        currentPlayer=*currentState.getPlayerList()[i];
        for(unsigned int j=0;j<currentPlayer.getMobileEntityList().size();j++){
            if(currentPlayer.getMobileEntityList()[j]->getEntityId()==TROLL){
                texture = textureTileset.at(TROLL).getTexture();

                quads.resize(textureTileset.at(TROLL).getCellHeight() * textureTileset.at(TROLL).getCellWidth() * 4);


            }
        }
    }
}

bool TextureArea::loadCursor(state::State& currentState, TileSet& textureTileset){
    
}