#include <string>
#include "../render.h"

using namespace render;

// Constructor

TileSet::TileSet(TileSetID newID){
    id = newID;

    cellWidth=32;
    cellHeight=32;

    switch(id){
        case TROLLTILESET:
            imageFile="res/Images/enemy2.png";
            break;
        case MAGETILESET:
            imageFile="res/Images/enemy.png";
            break;
        case KNIGHTTILESET:
            imageFile="res/Images/hero1.png";
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