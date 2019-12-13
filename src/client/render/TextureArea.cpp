#include "../render.h"
#include <iostream>
#include <fstream>

using namespace render;
using namespace state;
using namespace std;

// Functions

/** Load all the information needed to draw the map from the tileSet and the mapArray in the state
 * param : 
 * state -> current game state
 * textureTileSet -> corresponding TileSet object with the image loaded
 * 
 * return : boolean when loading was successful
 */
bool TextureArea::loadMap(state::State& currentState, render::TileSet& textureTileSet){
	texture = textureTileSet.getTexture(); // Get the sf::Texture with TileSet image loaded in render::TileSet Class
		
    // Resize vertex table so it can contain all the information for the level
	quads.setPrimitiveType(sf::Quads);
    // 4 vertex per tile (a quad)
    quads.resize(int(currentState.getEntityMap().getHeight() * currentState.getEntityMap().getWidth() * 4));

    // Index to browse the vertex table
    int vertexArrayIndex=0;

    vector<vector<shared_ptr<StaticEntity>>> map;
    map = currentState.getEntityMap().getMapArray();

    // Fill the vertex table for every tile in the map
    for (int i = 0; i < currentState.getEntityMap().getHeight(); i++){
        for (int j = 0; j < currentState.getEntityMap().getWidth(); j++){
            // Get the corresponding number for the current tile in the tileset
            int tileNumber = map[i][j]->getCodeTuile();
				
            // Deducing sprite position in tileset with the tile number
            int tx = tileNumber % (320 / textureTileSet.getCellWidth());
            int ty = tileNumber / (320 / textureTileSet.getCellHeight());

            // Get the pointer to the next quad for the current tile
            sf::Vertex* quad = &quads[vertexArrayIndex* 4];

			vertexArrayIndex++;

            // Definition of the four corners of the vertex in the window
               // 2 coordinates (x,y) for each vertex --> x = the current X position in the map product the width of a map tile in the tileSet
               //                                     --> y = the current Y position in the map product the height of a map tile in the tileSet
	        quad[0].position = sf::Vector2f(j*textureTileSet.getCellWidth(), i*textureTileSet.getCellHeight());
            quad[1].position = sf::Vector2f((j+1)*textureTileSet.getCellWidth(), i*textureTileSet.getCellHeight());
	        quad[2].position = sf::Vector2f((j+1)*textureTileSet.getCellWidth(), (i+1)*textureTileSet.getCellHeight());
	        quad[3].position = sf::Vector2f(j*textureTileSet.getCellWidth(), (i+1)*textureTileSet.getCellHeight());

            // Definition of coordinates in the tileset to retrieve the corresponding sprite
               // Same as quads position
            quad[0].texCoords = sf::Vector2f(tx * textureTileSet.getCellWidth(), ty * textureTileSet.getCellHeight());
			quad[1].texCoords = sf::Vector2f((tx + 1) * textureTileSet.getCellWidth(), ty * textureTileSet.getCellHeight());
			quad[2].texCoords = sf::Vector2f((tx + 1) * textureTileSet.getCellWidth(), (ty + 1) * textureTileSet.getCellHeight());
			quad[3].texCoords = sf::Vector2f(tx * textureTileSet.getCellWidth(), (ty + 1) * textureTileSet.getCellHeight());
        }
	}
	return true;	
}

/** Load all the information needed to draw the units from the tileSet and the MobileEntity objects in the state
 * param : 
 * state -> current game state
 * textureTileSet -> corresponding TileSet object with the image loaded
 * 
 * return : boolean when loading was successful
 */
bool TextureArea::loadUnits(state::State& currentState, render::TileSet& textureTileset){
    texture = textureTileset.getTexture(); 

    quads.setPrimitiveType(sf::Quads);

    Player currentPlayer; // Initialize Player class object in order to have the list of units belonging to each player
    int vertexArrayIndex = 0;

    // For each player initialized in the state object 
    for(unsigned int i=0;i<currentState.getPlayerList().size();i++){
        currentPlayer=*currentState.getPlayerList()[i];

        // For each unit controlled by the current player 
        for(unsigned int j=0;j<currentPlayer.getMobileEntityList().size();j++){
            // Increase vertex table size by a quad everytime there's a new unit
            quads.resize(quads.getVertexCount() + 4);

            sf::Vertex* quad = &quads[vertexArrayIndex * 4];  
            vertexArrayIndex += 1;

            int tx = currentPlayer.getMobileEntityList()[j]->getEntityId();
            int ty = currentPlayer.getMobileEntityList()[j]->getDirection();

            // Definition of the four corners of the vertex in the window
               // 2 coordinates (x,y) for each vertex --> x = the unit X position in the map product the width of the unit tileSet
               //                                     --> y = the unit Y position in the map product the height of the unit tileSet
            quad[0].position = sf::Vector2f(currentPlayer.getMobileEntityList()[j]->getX() * textureTileset.getCellWidth(),currentPlayer.getMobileEntityList()[j]->getY() * textureTileset.getCellHeight());
            quad[1].position = sf::Vector2f((currentPlayer.getMobileEntityList()[j]->getX()+1) * textureTileset.getCellWidth(),currentPlayer.getMobileEntityList()[j]->getY() * textureTileset.getCellHeight());
            quad[2].position = sf::Vector2f((currentPlayer.getMobileEntityList()[j]->getX()+1) * textureTileset.getCellWidth(),(currentPlayer.getMobileEntityList()[j]->getY()+1) * textureTileset.getCellHeight());
            quad[3].position = sf::Vector2f(currentPlayer.getMobileEntityList()[j]->getX() * textureTileset.getCellWidth(),(currentPlayer.getMobileEntityList()[j]->getY()+1) * textureTileset.getCellHeight());
            
            // Definition of coordinates in the tileset to retrieve the corresponding sprite
               // Same as quads position
            quad[0].texCoords = sf::Vector2f(tx * textureTileset.getCellWidth(), ty * textureTileset.getCellHeight());
            quad[1].texCoords = sf::Vector2f((tx+1) * textureTileset.getCellWidth(), ty * textureTileset.getCellHeight());
            quad[2].texCoords = sf::Vector2f((tx+1) * textureTileset.getCellWidth(), (ty+1) * textureTileset.getCellHeight());
            quad[3].texCoords = sf::Vector2f(tx * textureTileset.getCellWidth(), (ty+1) * textureTileset.getCellHeight());
        }
    }
    return true;
}

/** Load all the information needed to draw the units from the tileSet and the MobileEntity objects in the state
 * param : 
 * state -> current game state
 * textureTileSet -> corresponding TileSet object with the image loaded
 * 
 * return : boolean when loading was successful
 */
bool TextureArea::loadUnitDisplay(state::State& currentState, render::TileSet& textureTileset){
    texture = textureTileset.getTexture(); 

    quads.setPrimitiveType(sf::Quads);
    quads.resize(4);

    if(currentState.verifyIsSelected()){
        auto currentMobileEntity = currentState.getMobileEntity(currentState.getCursor().getX(), currentState.getCursor().getY()); // Get the currently selected MobileEntity

        sf::Vertex* quad = &quads[0];

        int tx = currentMobileEntity->getEntityId();
        int ty = currentMobileEntity->getStatus();

        // Definition of the four corners of the vertex in the window
            // 2 coordinates (x,y) for each vertex --> x = the unit X position in the map product the width of the unit tileSet
            //                                     --> y = the unit Y position in the map product the height of the unit tileSet
        quad[0].position = sf::Vector2f(600.f, 810.f);
        quad[1].position = sf::Vector2f(600.f + textureTileset.getCellWidth(), 810.f);
        quad[2].position = sf::Vector2f(600.f + textureTileset.getCellWidth(), 810.f + textureTileset.getCellHeight());
        quad[3].position = sf::Vector2f(600.f, 810.f + textureTileset.getCellHeight());
                
        // Definition of coordinates in the tileset to retrieve the corresponding sprite
            // Same as quads position
        quad[0].texCoords = sf::Vector2f(tx * textureTileset.getCellWidth(), ty * textureTileset.getCellHeight());
        quad[1].texCoords = sf::Vector2f((tx+1) * textureTileset.getCellWidth(), ty * textureTileset.getCellHeight());
        quad[2].texCoords = sf::Vector2f((tx+1) * textureTileset.getCellWidth(), (ty+1) * textureTileset.getCellHeight());
        quad[3].texCoords = sf::Vector2f(tx * textureTileset.getCellWidth(), (ty+1) * textureTileset.getCellHeight());
    }
    return true;
}

/** Load all the information needed to draw the cursor from the tileSet and the Cursor object in the state
 * param : 
 * state -> current game state
 * textureTileSet -> corresponding TileSet object with the image loaded
 * 
 * return : boolean when loading was successful
 */
bool TextureArea::loadCursor(state::State& currentState, render::TileSet& textureTileset){ 			
	texture = textureTileset.getTexture(); 

    quads.setPrimitiveType(sf::Quads);
    quads.resize(4);

    int tileNumber = currentState.getCursor().getCodeTuile();

	sf::Vertex* quad = &quads[0];
		
	quad[0].position = sf::Vector2f(currentState.getCursor().getX() * textureTileset.getCellWidth(), currentState.getCursor().getY() * textureTileset.getCellHeight());
	quad[1].position = sf::Vector2f((currentState.getCursor().getX() + 1) * textureTileset.getCellWidth(), currentState.getCursor().getY() * textureTileset.getCellHeight());
	quad[2].position = sf::Vector2f((currentState.getCursor().getX() + 1) * textureTileset.getCellWidth(), (currentState.getCursor().getY() + 1) * textureTileset.getCellHeight());
	quad[3].position = sf::Vector2f(currentState.getCursor().getX() * textureTileset.getCellWidth(), (currentState.getCursor().getY() + 1) * textureTileset.getCellHeight());
		
	quad[0].texCoords = sf::Vector2f(tileNumber * textureTileset.getCellWidth(), 0);
	quad[1].texCoords = sf::Vector2f((tileNumber + 1) * textureTileset.getCellWidth(), 0);
	quad[2].texCoords = sf::Vector2f((tileNumber + 1) * textureTileset.getCellWidth(), textureTileset.getCellHeight());
	quad[3].texCoords = sf::Vector2f(tileNumber * textureTileset.getCellWidth(), textureTileset.getCellHeight());
		
	return true;
}

void TextureArea::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        // Apply a transformation
        states.transform *= getTransform();

        // Apply texture of the tileset
        states.texture = &texture;

        // Draw the table with the vertex
        target.draw(quads, states);
}