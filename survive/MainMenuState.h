#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
#include "EditorState.h"
#include "SettingsState.h"
#include "Gui.h"

class GameState;
class EditorState;
class SettingsState;
class Gui;


class MainMenuState :
    public State
{
private:
    // Variable //
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;
    std::vector<sf::VideoMode> modes;

    sf::RectangleShape btnBackground;
    std::map<std::string, gui::Button*> buttons;

    // Functions //
    void initVariables();
    void initFonts();
    void initKeybinds();
    void initGui();
    void resetGui();

public:
    MainMenuState(StateData* state_data);
    virtual ~MainMenuState();

    // Function //

    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);
};

#endif 