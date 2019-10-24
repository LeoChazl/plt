#include "../render.h"


using namespace render;
using namespace std;


/*Constructor
*
*store in a TileSet pointor array all the TIleset type object pointor
*this TileSet object containt a sf::Texture object with the specific image loaded on it
**/
StateLayer::StateLayer (sf::RenderWindow& window, state::State& State){
    font.loadFromFile("rsc/Font/Game_Played.otf");
    screenWidth=1950;
    screenHeight=900;

    mapWidth=1600;
    mapHeight=800;

	TileSet tileSetCharacters(UNITSTILESET);//Load units tileset image
	unique_ptr<TileSet> ptr_charTileSet (new TileSet(tileSetCharacters));
	tileSets.push_back(move(ptr_charTileSet));//Store pointor of the TileSet object

    TileSet tileSetCursor(CURSORTILESET);//Load Cursor tileset image
	std::unique_ptr<TileSet> ptr_cursorTileSet (new TileSet(tileSetCursor));
	tileSets.push_back(move(ptr_cursorTileSet));

    TileSet tileSetMap(MAPTILESET);
	std::unique_ptr<TileSet> ptr_mapTileSet (new TileSet(tileSetMap));
	tileSets.push_back(move(ptr_mapTileSet));
}


 std::vector<std::unique_ptr<TileSet>>& StateLayer::getTileSets(){
     return tileSets;
}

 std::vector<std::unique_ptr<TextureArea>>& StateLayer::getTextureAreas(){
     return textureAreas;
 }

/*initTextureAreas
*
*create different layer: one for map,one for units,one for cursor
*store this layer in a array--> type TextureAreas
**/
void StateLayer::initTextureAreas (state::State state){
    //Déclaration des textures
    TextureArea map;
    TextureArea units;
    TextureArea cursor;

    //Chargement des Tiles dans Texture
    string directory="rsc/Images/level1_completeMap.png";
    //map.loadMap(mapWidth,mapHeight,directory);
    map.loadMap(mapWidth,mapHeight,state,*tileSets[2]);

    units.loadUnits(state,*tileSets[0]);
    cursor.loadCursor(state,*tileSets[1]);

    //Déclaration des pointeurs sur des pbjets de types Texture
	std::unique_ptr<TextureArea> ptr_map (new TextureArea(map));
    std::unique_ptr<TextureArea> ptr_units (new TextureArea(units));
    std::unique_ptr<TextureArea> ptr_cursor(new TextureArea(cursor));

    //Vider la table des éléments de type Texture
    if(textureAreas.size()!=0){
		while(textureAreas.size()!=0){
			textureAreas.pop_back();
		}
	}

    textureAreas.push_back(move(ptr_map));
    textureAreas.push_back(move(ptr_units));
    textureAreas.push_back(move(ptr_cursor));
}

/*draw
*
*Display each of the TextureArea layer in screen--> initialized in textureArea array with the "initTextureAreas(state)" function
**/
void StateLayer::draw (sf::RenderWindow& window){
    window.clear();

    //Initialize rectangle Texture in the Window-->LAYER
    // Rectangle degrade en (0,400) et de taille 400x200
	sf::VertexArray quad(sf::Quads, 4);
	quad[0].position = sf::Vector2f(1600.f, 0.f);
	quad[1].position = sf::Vector2f(1950.f, 0.f);
	quad[2].position = sf::Vector2f(1950.f, 800.f);
	quad[3].position = sf::Vector2f(1600.f, 800.f);
	quad[0].color = sf::Color::Blue;
	quad[1].color = sf::Color::Red;
	quad[2].color = sf::Color::Black;
	quad[3].color = sf::Color::Black;

    //Initialise a logo Texture in the Window-->LAYER
    sf::Texture logo;
    logo.loadFromFile("rsc/Images/fire_emblem_logo.png");
    sf::Sprite spriteLogo;
    spriteLogo.setPosition(1600,800);
    spriteLogo.setTexture(logo, true);

    window.draw(spriteLogo); //DRaw the logo layer
    window.draw(quad); //Draw the rectangle layer
	window.draw(*textureAreas[0]);	// Draw the map layer--> With the TextureArea type object as Target --> 			
	window.draw(*textureAreas[1]);	// Draw the units layer
	window.draw(*textureAreas[2]);	// Draw the cursor layer
    
	window.display();
}


int StateLayer::getMapHeight() const{
    return mapHeight;
}

int StateLayer::getMapWidth() const{
    return mapWidth;
}
