#include "../render.h"


using namespace render;
using namespace std;
using namespace state;

/** Constructor 
 * Store in a TileSet pointer array all the Tileset type object pointers
 * A TileSet object contains an sf::Texture object with the specific image loaded in it
 * 
 */
StateLayer::StateLayer (state::State& State, sf::RenderWindow& window): window(window){
    // Font will be used to draw statistics in the left and bottom space later on
    font.loadFromFile("rsc/Font/Game_Played.otf");

    // SFML window size
    screenWidth=1950;
    screenHeight=900;

    // Load units tileset image
	TileSet tileSetCharacters(UNITSTILESET);
	unique_ptr<TileSet> ptr_charTileSet (new TileSet(tileSetCharacters));
    // Store pointer of the TileSet object
	tileSets.push_back(move(ptr_charTileSet));

    TileSet tileSetCursor(CURSORTILESET);//Load Cursor tileset image
	unique_ptr<TileSet> ptr_cursorTileSet (new TileSet(tileSetCursor));
	tileSets.push_back(move(ptr_cursorTileSet));

    TileSet tileSetMap(MAPTILESET);
	unique_ptr<TileSet> ptr_mapTileSet (new TileSet(tileSetMap));
	tileSets.push_back(move(ptr_mapTileSet));
}

// Functions

/** Initialize all the textures to display them in the window
 * Creates different layers : one for the map, one for the units and one for the cursor
 * 
 * param : 
 * state -> current game state
 */
void StateLayer::initTextureAreas (state::State state){
    // Declaration of the different textures
    TextureArea map;
    TextureArea units;
    TextureArea cursor;

    // Loading the tiles in TextureArea objects
    units.loadUnits(state,*tileSets[0]);
    cursor.loadCursor(state,*tileSets[1]);
    map.loadMap(state,*tileSets[2]);

    // Declaration of pointers to store them in the global array for all the layers
	unique_ptr<TextureArea> ptr_map (new TextureArea(map));
    unique_ptr<TextureArea> ptr_units (new TextureArea(units));
    unique_ptr<TextureArea> ptr_cursor(new TextureArea(cursor));

    // Empty the table of all the elements in case we want to refresh the display
    if(textureAreas.size()!=0){
		while(textureAreas.size()!=0){
			textureAreas.pop_back();
		}
	}

    // Inserting all the textures data in one array
    textureAreas.push_back(move(ptr_map));
    textureAreas.push_back(move(ptr_units));
    textureAreas.push_back(move(ptr_cursor));
}

/** Display each of the TextureArea layer in screen--> initialized in textureArea array with the "initTextureAreas(state)" function
 * 
 * param : 
 * window -> SFML window
 */
void StateLayer::draw (){
    // Clear all the previous display in the window
    window.clear();

    // Rectangle shading at coordinates (1600,800) and size 350x100
	sf::VertexArray bottom_right_rectangle(sf::Quads, 4);
	bottom_right_rectangle[0].position = sf::Vector2f(1600.f, 800.f);
	bottom_right_rectangle[1].position = sf::Vector2f(1950.f, 800.f);
	bottom_right_rectangle[2].position = sf::Vector2f(1950.f, 900.f);
	bottom_right_rectangle[3].position = sf::Vector2f(1600.f, 900.f);
	bottom_right_rectangle[0].color = sf::Color::Red;
	bottom_right_rectangle[1].color = sf::Color::Yellow;
	bottom_right_rectangle[2].color = sf::Color::Red;
	bottom_right_rectangle[3].color = sf::Color::Yellow;

    // Rectangle shading at coordinates (1600,0) and size 350x800
	sf::VertexArray right_rectangle(sf::Quads, 4);
	right_rectangle[0].position = sf::Vector2f(1600.f, 0.f);
	right_rectangle[1].position = sf::Vector2f(1950.f, 0.f);
	right_rectangle[2].position = sf::Vector2f(1950.f, 800.f);
	right_rectangle[3].position = sf::Vector2f(1600.f, 800.f);
	right_rectangle[0].color = sf::Color::Yellow;
	right_rectangle[1].color = sf::Color::Red;
	right_rectangle[2].color = sf::Color::Yellow;
	right_rectangle[3].color = sf::Color::Red;

    // Rectangle shading at coordinates (0,800) and size 1600x100
	sf::VertexArray bottom_rectangle(sf::Quads, 4);
	bottom_rectangle[0].position = sf::Vector2f(0.f, 800.f);
	bottom_rectangle[1].position = sf::Vector2f(1600.f, 800.f);
	bottom_rectangle[2].position = sf::Vector2f(1600.f, 900.f);
	bottom_rectangle[3].position = sf::Vector2f(0.f, 900.f);
	bottom_rectangle[0].color = sf::Color::Yellow;
	bottom_rectangle[1].color = sf::Color::Red;
	bottom_rectangle[2].color = sf::Color::Yellow;
	bottom_rectangle[3].color = sf::Color::Red;

    // Fire Emblem logo put over the rectangle shading
    sf::Texture logo;
    logo.loadFromFile("rsc/Images/fire_emblem_logo.png");
    sf::Sprite spriteLogo;
    spriteLogo.setPosition(1600,800);
    spriteLogo.setTexture(logo, true);

    window.draw(bottom_right_rectangle); // Draw the colored rectangle in the bottom right
    window.draw(right_rectangle); // Draw the colored rectangle on the right
    window.draw(bottom_rectangle); // Draw the colored rectangle at the bottom
    window.draw(spriteLogo); // Draw the logo 
	window.draw(*textureAreas[0]);	// Draw the map layer with the TextureArea type object as Target		
	window.draw(*textureAreas[1]);	// Draw the units layer
	window.draw(*textureAreas[2]);	// Draw the cursor layer
    
	window.display();
}

/**
 * 
 */
void StateLayer::stateChanged(const state::StateEvent& stateEvent, state::State& state){
    initTextureAreas(state);
    draw();
}

// Getters

vector<unique_ptr<TileSet>>& StateLayer::getTileSets(){
     return tileSets;
}

vector<unique_ptr<TextureArea>>& StateLayer::getTextureAreas(){
     return textureAreas;
 }