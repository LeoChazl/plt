#include "../render.h"
#include <iostream>
#include <unistd.h>


using namespace render;
using namespace std;
using namespace state;
using namespace engine;

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

    // Loading all the tileset images
	TileSet tileSetCharacters(UNITSTILESET);
	unique_ptr<TileSet> ptr_charTileSet (new TileSet(tileSetCharacters));
    // Store pointer of the TileSet object
	tileSets.push_back(move(ptr_charTileSet));

    TileSet tileSetCursor(CURSORTILESET);
	unique_ptr<TileSet> ptr_cursorTileSet (new TileSet(tileSetCursor));
	tileSets.push_back(move(ptr_cursorTileSet));

    TileSet tileSetMap(MAPTILESET);
	unique_ptr<TileSet> ptr_mapTileSet (new TileSet(tileSetMap));
	tileSets.push_back(move(ptr_mapTileSet));

    // For the units on the HUD
    TileSet tileSetUnitDisplay(UNITDISPLAYTILESET);
    unique_ptr<TileSet> ptr_unitDisplayTileSet (new TileSet(tileSetUnitDisplay));
    tileSets.push_back(move(ptr_unitDisplayTileSet));
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
    TextureArea unitDisplay;

    // Loading the tiles in TextureArea objects
    units.loadUnits(state,*tileSets[0]);
    cursor.loadCursor(state,*tileSets[1]);
    map.loadMap(state,*tileSets[2]);
    unitDisplay.loadUnitDisplay(state,*tileSets[3]);

    // Declaration of pointers to store them in the global array for all the layers
	unique_ptr<TextureArea> ptr_map (new TextureArea(map));
    unique_ptr<TextureArea> ptr_units (new TextureArea(units));
    unique_ptr<TextureArea> ptr_cursor(new TextureArea(cursor));
    unique_ptr<TextureArea> ptr_unitDisplay(new TextureArea(unitDisplay));

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
    textureAreas.push_back(move(ptr_unitDisplay));
}

/** Display each of the TextureArea layer in screen--> initialized in textureArea array with the "initTextureAreas(state)" function
 * 
 * param : 
 * window -> SFML window
 */
void StateLayer::draw (state::State& state){ 
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

    // Control panel
    sf::RectangleShape controlPanel(sf::Vector2f(350.f,100.f));
    controlPanel.setPosition(sf::Vector2f(1600.f,800.f));
    sf::Color colorControlPanel(0,0,0,250);
    controlPanel.setFillColor(colorControlPanel);

    string title = "Controls";
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setString(title);
    titleText.setCharacterSize(12);
    titleText.setFillColor(sf::Color::Cyan);
    titleText.setPosition(1725.f,805.f);

    string controlString1 = "Arrow  keys\n\nEnter\n\nA";
    sf::Text controlText1;
    controlText1.setFont(font);
    controlText1.setString(controlString1);
    controlText1.setCharacterSize(10);
    controlText1.setFillColor(sf::Color::Red);
    controlText1.setPosition(1645.f, 825.f);

    string actionString1 = "Move\n\nSelect\n\nAttack";
    sf::Text actionText1;
    actionText1.setFont(font);
    actionText1.setString(actionString1);
    actionText1.setCharacterSize(10);
    actionText1.setFillColor(sf::Color::White);
    actionText1.setPosition(1715.f, 825.f);

    string controlString2 = "Z\n\nE";
    sf::Text controlText2;
    controlText2.setFont(font);
    controlText2.setString(controlString2);
    controlText2.setCharacterSize(10);
    controlText2.setFillColor(sf::Color::Red);
    controlText2.setPosition(1780.f, 825.f);

    string actionString2 = "Cancel  attack\n\nEnd  unit  round";
    sf::Text actionText2;
    actionText2.setFont(font);
    actionText2.setString(actionString2);
    actionText2.setCharacterSize(10);
    actionText2.setFillColor(sf::Color::White);
    actionText2.setPosition(1800.f, 825.f);

    // Fire Emblem logo put over the rectangle shading
    sf::Texture logo;
    logo.loadFromFile("rsc/Images/fire_emblem_logo.png");
    sf::Sprite spriteLogo;
    spriteLogo.setPosition(1600.f,0.f);
    spriteLogo.setTexture(logo, true);

    window.draw(bottom_right_rectangle); // Draw the colored rectangle in the bottom right
    window.draw(right_rectangle); // Draw the colored rectangle on the right
    window.draw(bottom_rectangle); // Draw the colored rectangle at the bottom
    window.draw(controlPanel);
    window.draw(titleText);
    window.draw(controlText1);
    window.draw(actionText1);
    window.draw(controlText2);
    window.draw(actionText2);
    window.draw(spriteLogo); // Draw the logo 
	window.draw(*textureAreas[0]);	// Draw the map layer with the TextureArea type object as Target		
	window.draw(*textureAreas[1]);	// Draw the units layer
	window.draw(*textureAreas[2]);	// Draw the cursor layer
    window.draw(*textureAreas[3]);  // Draw selected unit picture

    drawBottomInfos(state);
    drawRightInfos(state);
    
	window.display();
}

/** Draw the display in the bottom rectangle, describes current action
 * 
 * param :
 * state -> current state
 */
void StateLayer::drawBottomInfos(state::State& state){

    // Current player rectangle at the bottm
    sf::RectangleShape currentPlayerRectangle(sf::Vector2f(300.f, 30.f));
	currentPlayerRectangle.setPosition(700.f, 810.f);
    sf::Color colorCurrentPlayerRectangle(0,0,0,150);
	currentPlayerRectangle.setFillColor(colorCurrentPlayerRectangle);

    string currentString = "Player " + to_string(state.getCurrentPlayerID()) + " is playing";
    sf::Text currentText;
    currentText.setFont(font);
    currentText.setString(currentString);
    currentText.setCharacterSize(16);
    currentText.setFillColor(sf::Color::White);
    currentText.setPosition(765.f ,815.f);

    // Current action rectangle at the bottom
    sf::RectangleShape currentActionRectangle(sf::Vector2f(300.f, 25.f));
	currentActionRectangle.setPosition(700.f, 850.f);
    sf::Color colorCurrentActionRectangle(0,0,0,200);
	currentActionRectangle.setFillColor(colorCurrentActionRectangle);

    string currentActionString = "Smth is moving";
    sf::Text currentAction;
    currentAction.setFont(font);
    currentAction.setString(currentActionString);
    currentAction.setCharacterSize(12);
    currentAction.setFillColor(sf::Color::White);
    currentAction.setPosition(795.f ,855.f);

    window.draw(currentPlayerRectangle);
    window.draw(currentText);
    window.draw(currentActionRectangle);
    window.draw(currentAction);
}

/** Draw the display in the right rectangle, shows unit caracteristics
 * 
 * param :
 * state -> current state
 */
void StateLayer::drawRightInfos(state::State& state){
    sf::RectangleShape selectedUnitRectangle(sf::Vector2f(250.f, 30.f));
	selectedUnitRectangle.setPosition(1635.f, 110.f);
    sf::Color colorSelectedUnitRectangle(0,0,0,100);
	selectedUnitRectangle.setFillColor(colorSelectedUnitRectangle);

    string selectedString = "Selected unit stats";
    sf::Text selectedText;
    selectedText.setFont(font);
    selectedText.setString(selectedString);
    selectedText.setCharacterSize(14);
    selectedText.setFillColor(sf::Color::White);
    selectedText.setPosition(1675.f ,115.f);

    // Selected unit stats box
    sf::RectangleShape selectedUnitStatsRectangle(sf::Vector2f(250.f, 250.f));
	selectedUnitStatsRectangle.setPosition(1635.f, 160.f);
	selectedUnitStatsRectangle.setFillColor(sf::Color::Black);

    sf::Texture vs;
    vs.loadFromFile("rsc/Images/vs.png");
    sf::Sprite spriteVs;
    spriteVs.setPosition(1720.f,425.f);
    spriteVs.setTexture(vs, true);

    sf::RectangleShape enemyUnitRectangle(sf::Vector2f(250.f, 30.f));
	enemyUnitRectangle.setPosition(1635.f, 475.f);
    sf::Color colorEnemyUnitRectangle(0,0,0,100);
	enemyUnitRectangle.setFillColor(colorEnemyUnitRectangle);

    string enemyString = "Enemy unit stats";
    sf::Text enemyText;
    enemyText.setFont(font);
    enemyText.setString(enemyString);
    enemyText.setCharacterSize(14);
    enemyText.setFillColor(sf::Color::White);
    enemyText.setPosition(1685.f ,480.f);

    // Enemy stats box
    sf::RectangleShape enemyUnitStatsRectangle(sf::Vector2f(250.f, 250.f));
	enemyUnitStatsRectangle.setPosition(1635.f, 520.f);
	enemyUnitStatsRectangle.setFillColor(sf::Color::Black);

    window.draw(selectedUnitRectangle);
    window.draw(selectedText);
    window.draw(selectedUnitStatsRectangle);
    window.draw(spriteVs);
    window.draw(enemyUnitRectangle);
    window.draw(enemyText);
    window.draw(enemyUnitStatsRectangle);
}


/** Called when there has been changes in the state and updates the display
 * 
 */
void StateLayer::stateChanged(const state::StateEvent& stateEvent, state::State& state){
    initTextureAreas(state);
    draw(state);
}

void StateLayer::inputManager(sf::Event event, state::State& state){
    int waitingTime = 60000;

    // To notify the State
    StateEvent stateEvent(PLAYERCHANGE);

    // Arrow keys and return when no unit is selected
    if(event.type==sf::Event::KeyPressed && !state.verifyIsSelected()){
        //Save curosr position in variables
        int cursor_x = state.getCursor().getX(); 
        int cursor_y = state.getCursor().getY();

        //According to the user command on keyboard increase the cursor value
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            if(cursor_x!=0){ //Keep the cursor inside the screen limits
                cursor_x -= 1;
                cout << "Moving the cursor to (" << cursor_x << ", " << cursor_y << ").\n" << endl;
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            if(cursor_x!=state.getEntityMap().getWidth()-1){//Keep the cursor inside the screen limits
                cursor_x += 1;
                cout << "Moving the cursor to (" << cursor_x << ", " << cursor_y << ").\n" << endl;
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            if(cursor_y!=0){//Keep the cursor inside the screen limits
                cursor_y -= 1;
                cout << "Moving the cursor to (" << cursor_x << ", " << cursor_y << ").\n" << endl;
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            if(cursor_y!=state.getEntityMap().getHeight()-1){//Keep the cursor inside the screen limits
                cursor_y += 1;
                cout << "Moving the cursor to (" << cursor_x << ", " << cursor_y << ").\n" << endl;
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){ //User press the following button:"ENTER"
            auto currentMobileEntity = state.getMobileEntity(state.getCursor().getX(), state.getCursor().getY());//Try to have access to a MobileEntity at the cursor actal position
            
            // Test if a unit is on the case
            if(currentMobileEntity!=NULL){ 
                //Test if the unit is belongs to the actual player and if the player didn't already play with the unit in the current round
                if(currentMobileEntity->getPlayerId()==state.getCurrentPlayerID() && currentMobileEntity->getStatus()==AVAILABLE){ 
                    state.getCursor().setCodeTuile(2);//Change the Tile --> set green color cursor tile

                    currentMobileEntity->setStatus(SELECTED);//Change the Selected MobileEntity Status

                    cout << "A unit has been selected.\n" << endl;
                }else if(currentMobileEntity->getStatus()==WAITING){ //the unit is not avaible --> player already play with this unit
                    cout << "This unit already finished his round.\n" << endl;
                }else{
                    cout << "This unit doesn't belong to the current player.\n" << endl;
                }
            }else{ // the currentPLayer pointor is NULL
                cout << "No unit in this case.\n" << endl;
            }
        }
        //Reset the cursor position in the state
        state.getCursor().setX(cursor_x);
        state.getCursor().setY(cursor_y);
        //Notify all registred Observer in "state Observers" list
        state.notifyObservers(stateEvent, state);

        usleep(waitingTime);

    // Case a unit is already selected and attack (Prss "A" button)
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && (state.verifyIsSelected())){
        cout << "An attack is in preparation.\n" << endl;
        auto currentMobileEntity = state.getMobileEntity(state.getCursor().getX(), state.getCursor().getY());

        // Change cursor color
        state.getCursor().setCodeTuile(1); //Change current cursor color to RED
        state.notifyObservers(stateEvent, state); //Notify state Observers that the tile changed 

        // Set different variables to keep track of the unit attack range
        int rightRange=currentMobileEntity->getAttackRange();
        int leftRange=currentMobileEntity->getAttackRange();
        int upRange=currentMobileEntity->getAttackRange();
        int downRange=currentMobileEntity->getAttackRange();

        // Set a target to do a while loop
        auto target = currentMobileEntity;
        bool attackIsOngoing = true;

        //As long as the target is not choose (i.e the Atttacker is the target) and the Attack is not canceled
        while(target==currentMobileEntity && attackIsOngoing){
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                if(state.getCursor().getX()!=0 && leftRange!=0){
                    state.getCursor().setX(state.getCursor().getX()-1);//Set the new cursor position
                    rightRange++; //update attack range variables
                    leftRange--;
                    state.notifyObservers(stateEvent, state);//Notify OBserver in order to update the cursor position on the screen
                    usleep(waitingTime);
                }
            } 
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                if(state.getCursor().getX()!=state.getEntityMap().getWidth()-1 && rightRange!=0){
                    state.getCursor().setX(state.getCursor().getX()+1);
                    rightRange--;
                    leftRange++;
                    state.notifyObservers(stateEvent, state);
                    usleep(waitingTime);
                }
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                if(state.getCursor().getY()!=0 && upRange!=0){
                    state.getCursor().setY(state.getCursor().getY()-1);
                    upRange--;
                    downRange++;
                    state.notifyObservers(stateEvent, state);
                    usleep(waitingTime);
                }
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                if(state.getCursor().getY()!=state.getEntityMap().getWidth()-1 && downRange!=0){
                    state.getCursor().setY(state.getCursor().getY()+1);
                    upRange++;
                    downRange--;
                    state.notifyObservers(stateEvent, state);
                    usleep(waitingTime);
                }
            }
            //Select the target with  "ENTER" button
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
                if(state.isOccupied(state.getCursor().getX(),state.getCursor().getY())){//if there are units in the actual cursor position
                    target = state.getMobileEntity(state.getCursor().getX(), state.getCursor().getY());//chage the target to the selected one
                    EngineRenderEvent engineRenderEvent(ATTACK); //A class to regitrer the type of Engine Event (ATTACK)
                    Position position(0,0);

                    notifyRenderObservers(engineRenderEvent, state, position, currentMobileEntity, target); //Notify Render Observers that there is an Attack event
                        
                    state.getCursor().setCodeTuile(0); //Set the cursor to target selected color
                    state.notifyObservers(stateEvent, state);// Notify State Observers
                }
            }
            //Cancel the attack
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
                attackIsOngoing = false;
                cout << "The attack is canceled.\n" << endl;

                // Cursor back to select color
                state.getCursor().setCodeTuile(2);

                // If Cursor is not on the selected MobileEntity
                if(currentMobileEntity->getX()!=state.getCursor().getX() || currentMobileEntity->getY()!=state.getCursor().getY()){
                    state.getCursor().setX(currentMobileEntity->getX());//ReSet the cursor on the selected mobileEntity--> Attacker
                    state.getCursor().setY(currentMobileEntity->getY());
                }
                state.notifyObservers(stateEvent, state); //Notify the state observer in rder to draw the cursor on the Attacker
                usleep(waitingTime);
            }
        }
    
    // Case a unit is already selected and move or end round
    } else if(event.type==sf::Event::KeyPressed && (state.verifyIsSelected())){
        auto currentMobileEntity = state.getMobileEntity(state.getCursor().getX(), state.getCursor().getY());
        
        int movement_x=0, movement_y=0;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            if(currentMobileEntity->getX()!=0){
                movement_x=-1;
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            if(currentMobileEntity->getX()!=state.getEntityMap().getWidth()-1){
                movement_x=1;
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            if(currentMobileEntity->getY()!=0){
                movement_y=-1;
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            if(currentMobileEntity->getY()!=state.getEntityMap().getHeight()-1){
                movement_y=+1;
            }
        }

        if(movement_x != 0 || movement_y!=0){//If there are any x or y axe movement asked by the player
            Position position(currentMobileEntity->getX()+movement_x,currentMobileEntity->getY()+movement_y);
        
            EngineRenderEvent engineRenderEvent(ARROW_KEYS);

            // Second MobileEntity not used here but filled so it match the function arguments
            notifyRenderObservers(engineRenderEvent, state, position, currentMobileEntity, currentMobileEntity);//Update the unit position on the map by updating the render

            movement_x=0;
            movement_y=0;
        }

        // End round for the unit
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
            Position position(0,0);

            EngineRenderEvent engineRenderEvent(END_UNIT_ROUND);

            // Second MobileEntity not used here but filled so it match the function arguments
            notifyRenderObservers(engineRenderEvent, state, position, currentMobileEntity, currentMobileEntity);
        } 
    }
}

// Getters

vector<unique_ptr<TileSet>>& StateLayer::getTileSets(){
    return tileSets;
}

vector<unique_ptr<TextureArea>>& StateLayer::getTextureAreas(){
    return textureAreas;
 }