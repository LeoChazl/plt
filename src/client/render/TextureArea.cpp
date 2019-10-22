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

bool TextureArea::loadUnits(state::State& currentState, map<string,TileSet&> textureTileset){

    quads.setPrimitiveType(sf::Quads);

    Player currentPlayer;
    for(unsigned int i=0;i<currentState.getPlayerList().size();i++){
        currentPlayer=*currentState.getPlayerList()[i];
        for(unsigned int j=0;j<currentPlayer.getMobileEntityList().size();j++){
            if(currentPlayer.getMobileEntityList()[j]->getEntityId()==TROLL){
                texture = textureTileset[TROLL].getTexture();

                quads.resize(textureTileset[TROLL].getCellHeight() * textureTileset["TROLL"].getCellWidth() * 4);


            }
        }
    }
}

bool TextureArea::loadCursor(state::State& currentState, TileSet& textureTileset){
    
}