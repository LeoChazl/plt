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
	tileSets.push_back(move(ptr_trollTileSet));
	
	TileSet tileSetMage(MAGETILESET);
	std::unique_ptr<TileSet> ptr_mageTileSet (new TileSet(tileSetMage));
	tileSets.push_back(move(ptr_mageTileSet));

    TileSet tileSetKnight(MAGETILESET);
	std::unique_ptr<TileSet> ptr_knightTileSet (new TileSet(tileSetKnight));
	tileSets.push_back(move(ptr_knightTileSet));

    TileSet tileSetCursor(CURSORTILESET);
	std::unique_ptr<TileSet> ptr_cursorTileSet (new TileSet(tileSetCursor));
	tileSets.push_back(move(ptr_cursorTileSet));

}


 std::vector<std::unique_ptr<TileSet>>& StateLayer::getTileSets(){
     return tileSets;
}

 std::vector<std::unique_ptr<TextureArea>>& StateLayer::getTextureAreas(){
     return textureAreas;
 }

void StateLayer::initTextureAreas (state::State state){
    //Déclaration des textures
    TextureArea units;
    TextureArea map;

    //Chargement des TIles dans Texture
    string directory="rsc/Images/level1_completeMap.png";
    map.loadBattleField(mapHeight,mapWidth,directory);
    units.loadUnits(state,tileSets);

    //Déclaration des pointeurs sur des pbjets de types Texture
    std::unique_ptr<TextureArea> ptr_units (new TextureArea(units));
	std::unique_ptr<TextureArea> ptr_map (new TextureArea(map));

    //Vider la table des éléments de type Texture
    if(textureAreas.size()!=0){
		while(textureAreas.size()!=0){
			textureAreas.pop_back();
		}
	}

    textureAreas.push_back(move(ptr_units));
    textureAreas.push_back(move(ptr_map));
}


void StateLayer::draw (sf::RenderWindow& window){
    /*window.clear();
    window.draw(*textureAreas[0]);	// Dessin de la grille				
	window.draw(*textureAreas[1]);	// Dessin des personnages
	window.draw(*textureAreas[2]);	// Dessin du curseur
	window.display();*/
}


int StateLayer::getMapHeight() const{
    return mapHeight;
}

int StateLayer::getMapWidth() const{
    return mapWidth;
}
