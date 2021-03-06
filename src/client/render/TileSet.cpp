#include <string>
#include "../render.h"

using namespace render;

// Constructor

TileSet::TileSet(render::TileSetID newID){
    id = newID;
    
    switch(id){
        case UNITSTILESET:
            cellWidth=32;
            cellHeight=32;
            imageFile="rsc/Images/characters_tileset_32.png";
            break;
        case CURSORTILESET:
            cellWidth=32;
            cellHeight=32;
            imageFile="rsc/Images/cursor_32.png";
            break;
        case MAPTILESET:
            cellWidth=32;
            cellHeight=32;
            imageFile="rsc/Images/map_tileset.png";
            break;
        case UNITDISPLAYTILESET:
            cellWidth=64;
            cellHeight=64;
            imageFile="rsc/Images/characters_tileset_bottomdisplay.png";
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