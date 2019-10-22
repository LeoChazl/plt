#include "../render.h"


using namespace render;
using namespace std;


//Constructor
StateLayer::StateLayer (sf::RenderWindow& window, state::State& State){
    font.loadFromFile("rsc/Font/Game_Played.otf");
    screenHeight=900;
    screenWidth=1950;

    TextureArea battleField;
    string mapImageDirectory="rsc/Images/level1_completeMap.png";
    battleField.loadBattleField(mapHeight,mapWidth,mapImageDirectory);


    TextureArea units;
    //units.loadUnits()

    //textureAreas.push_back()

}


std::vector<std::unique_ptr<TileSet>>& StateLayer::getTileSets(){
    return tileSets;
}

 std::vector<std::unique_ptr<TextureArea>>& StateLayer::getTextureAreas(){
     return textureAreas;
 }

void initTextureAreas (state::State state){

}


void draw (sf::RenderWindow& window){

}
