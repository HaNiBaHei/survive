#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "State.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "TileMap.h"

class State;
class Gui;
class PauseMenu;
class TileMap;

class EditorState :
    public State
{
private:
    // Variable //
    sf::Font font;
    PauseMenu* pmenu;

    std::map<std::string, gui::Button*> buttons;

    TileMap* tileMap;

    sf::RectangleShape selectorRect;

    // Functions //
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initPauseMenu();
    void initButton();
    void initGui();
    void initTileMap();

public:
    EditorState(StateData* state_data);
    virtual ~EditorState();

    // Function //

    void updateInput(const float& dt);
    void updateButtons();
    void updateGui();
    void updatePauseMenuButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget& target);
    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);
	

	
};

#endif // !EDITORSTATE_H