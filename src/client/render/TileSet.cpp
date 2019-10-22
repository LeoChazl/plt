#include <string>
#include "../render.h"

using namespace render;

// Constructor

TileSet::TileSet(TileSetID newID){
    id = newID;

    switch (id){
        case TROLLTILESET:
            cellWidth=32;
            cellHeight=32;
            imageFile="res/Images/enemy2.png";
            break;
    
        default:
            break;
    }
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