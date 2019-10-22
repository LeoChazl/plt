#include "../render.h"

using namespace render;
using namespace std;

// Constructor

TileSet::TileSet(TileSetID newID){

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
    return 
}