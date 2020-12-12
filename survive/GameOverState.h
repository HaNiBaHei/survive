#pragma once
#include "State.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "Gui.h"

class GameOverState :
    public State
{
private:

    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    sf::RectangleShape btnBackground;
    std::map<std::string, gui::Button*> buttons;

    sf::Text optionsText;


    void initFont();
    void initKeybinds();
    void initGui();

    void resetGui();

public:
    GameOverState(StateData* state_data);
    virtual ~GameOverState();

    const bool SkipState();

    void updateInput(const float& dt);
    void updateGui(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderGui(sf::RenderTarget& target);
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);
};

