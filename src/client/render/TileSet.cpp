#include <string>
#include "../render.h"

using namespace render;

// Constructor

TileSet::TileSet(TileSetID newID){
    id = newID;

    cellWidth=32;
    cellHeight=32;

    switch(id){
        case CHARTILESET:
            imageFile="res/Images/characters_tileset.png";
            break;
        case CURSORTILESET:
            imageFile="res/Images/cursor.png";
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