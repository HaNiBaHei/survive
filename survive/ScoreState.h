#ifndef SCORESTATE_H
#define SCORESTATE_H

#include "State.h"
#include "Gui.h"

#include "State.h"
class ScoreState :
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
    ScoreState(StateData* state_data);
    virtual ~ScoreState();

    void updateInput(const float& dt);
    void updateGui(const float& dt);
    void update(const float& dt);
    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);
};

#endif // !SCORESTATE_H
