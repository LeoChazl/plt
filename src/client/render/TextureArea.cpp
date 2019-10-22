#include "../render.h"
#include "state.h"
#include <string>

using namespace render;
using namespace state;
using namespace std;

// Functions

bool TextureArea::loadBattleField(int mapHeight, int mapWidth ,std::string mapImageDirectory){
     return texture.loadFromFile(mapImageDirectory);
}

bool TextureArea::loadUnits(state::State& currentState, TileSet& textureTileset){
    texture = textureTileset.getTexture();

    quads.setPrimitiveType(sf::Quads);
    quads.resize(textureTileset.getCellHeight() * textureTileset.getCellWidth() * 4);

    Player currentPlayer;
    for(unsigned int i=0;i<currentState.getPlayerList().size();i++){
        currentPlayer=*currentState.getPlayerList()[i];
        for(unsigned int j=0;j<currentPlayer.getMobileEntityList().size();j++){
            
        }
    }
}

bool TextureArea::loadCursor(state::State& currentState, TileSet& textureTileset){
    
}