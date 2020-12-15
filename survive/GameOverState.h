#pragma once
#include "State.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "Player.h"
#include "Gui.h"
#include "PlayerGui.h"
#include "AttributeComponent.h"
#include "PlayerGui.h"
#include "Sword.h"
#include "Bow.h"
#include "TextTagSystem.h"

class GameOverState :
    public State
{
private:
    AttributeComponent* attri;
    sf::Texture texture;
    /// <summary>
    /// ///////////////////////
    /// </summary>
    /// 
    std::string scoreString;
    sf::Text scoreText;

    Player* player;

    PlayerGui* playerGui;
    sf::RenderTexture renderTexture;

    sf::Texture bgtexture;
    sf::RectangleShape bgsreen;
    sf::Font font;

    sf::VideoMode& vm;

    unsigned score;

    sf::RectangleShape btnBackground;
    std::map<std::string, gui::Button*> buttons;

    sf::Text optionsText;

    sf::Music Death;

    void initVariable();
    void initFont();
    void initKeybinds();
    void initGui();
    void initScore();
    void initSound();

    void resetGui();

public:
    GameOverState(StateData* state_data);
    virtual ~GameOverState();

    void updateScoreText();

    void updateButtons();
    void updateInput(const float& dt);
    void update(const float& dt);
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);
};

