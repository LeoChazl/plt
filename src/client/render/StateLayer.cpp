#include "../render.h"


using namespace render;
using namespace std;


//Constructor
StateLayer::StateLayer (sf::RenderWindow& window, state::State& State){
    font.loadFromFile("rsc/Font/Game_Played.otf");
    screenHeight=900;
    screenWidth=1950;
    mapWidth=1600;
    mapHeight=800;

	TileSet tileSetTroll(TROLLTILESET);
	std::unique_ptr<TileSet> ptr_trollTileSet (new TileSet(tileSetTroll));
	//tileSets[0]=ptr_trollTileSet;
	
	/*TileSet tilesetPersonnages(PERSONNAGETILESET);
	std::unique_ptr<TileSet> ptr_tilesetPersonnages (new TileSet(tilesetPersonnages));
	tilesets.push_back(move(ptr_tilesetPersonnages));
	
	TileSet tilesetCurseur(CURSEURTILESET);
	std::unique_ptr<TileSet> ptr_tilesetCurseur (new TileSet(tilesetCurseur));
	tilesets.push_back(move(ptr_tilesetCurseur));


    TextureArea units;
    TextureArea cursor;
    //units.loadUnits()

    textureAreas.push_back(battleField);*/

}


//std::vector<std::unique_ptr<TileSet>>& StateLayer::getTileSets(){
  //  return tileSets;
//}

 std::vector<std::unique_ptr<TextureArea>>& StateLayer::getTextureAreas(){
     return textureAreas;
 }

void initTextureAreas (state::State state){

}


void draw (sf::RenderWindow& window){

}
