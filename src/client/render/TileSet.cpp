#include <string>
#include "../render.h"

using namespace render;

// Constructor

TileSet::TileSet(render::TileSetID newID){
    id = newID;
    
    cellWidth=32;
    cellHeight=32;
    
    switch(id){
        case UNITSTILESET:
            imageFile="rsc/Images/characters_tileset_32.png";
            break;
        case CURSORTILESET:
            imageFile="rsc/Images/cursor_32.png";
            break;
        case MAPTILESET:
            imageFile="rsc/Images/map_tileset.png";
            break;
        default:
            break;
    }

    textureTileSet.loadFromFile(imageFile);
}

// Getters

int const TileSet::getCellWidth(){
    return cellWidth;
}

int const TileSet::getCellHeight(){
    return cellHeight;
}

int const TileSet::getTileSetID(){
    return id;
}

sf::Texture& TileSet::getTexture(){
    return textureTileSet;
}