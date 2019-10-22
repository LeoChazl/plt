#include "../render.h"
#include <string>

using namespace render;
using namespace std;

// Functions

bool TextureArea::loadBattleField(int mapHeight, int mapWidth ,std::string mapImageDirectory){
     return texture.loadFromFile(mapImageDirectory);
}

bool TextureArea::loadUnits(state::State& currentState, sf::Texture& textureTileset){
    texture = textureTileset;

    quads.setPrimitiveType(sf::Quads);
    quads.resize(textureTileset.getSize().x * textureTileset.getSize().y * 4);

    
}

bool TextureArea::loadCursor(state::State& currentState, sf::Texture& textureTileset){
    
}