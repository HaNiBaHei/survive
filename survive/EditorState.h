#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "State.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "EditorMode.h"
#include "EditorModes.h"
#include "MainMenuState.h"

class State;
class StateData;
class Gui;
class PauseMenu;
class TileMap;
class Tile;
class EditorMode;
class EditorStateData;
class DefaultEditorMode;
class EnemyEditorMode;

enum EditorModes { DEFAULT_EDITOR_MODE = 0, ENEMY_EDITOR_MODE };

class EditorState :
    public State
{
private:
    EditorStateData ediorStateData;

    // Variable //
    sf::View view;
    float cameraSpeed;

    sf::Font font;
    PauseMenu* pmenu;

    std::map<std::string, gui::Button*> buttons;

    TileMap* tileMap;

    std::vector<EditorMode*> modes;
    unsigned activeMode;

    // Functions //
    void initVariables();
    void initEditorStateData();
    void initView();
    void initFonts();
    void initKeybinds();
    void initPauseMenu();
    void initButton();
    void initGui();
    void initTileMap();
    void initModes();

public:
    EditorState(StateData* state_data);
    virtual ~EditorState();

    // Function //

    void updateInput(const float& dt);
    void updateEditorInput(const float& dt);
    void updateButtons();
    void updateGui(const float& dt);
    void updatePauseMenuButtons();
    void updateModes(const float& dt);
    void update(const float& dt);
    void renderButtons(sf::RenderTarget& target);
    void renderGui(sf::RenderTarget& target);
    void rederModes(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);
	
};

#endif // !EDITORSTATE_H