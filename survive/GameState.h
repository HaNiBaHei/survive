#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGui.h"
#include "Sword.h"
#include "Bow.h"

class PauseMenu;
class Player;
class PlayerGui;
class TileMap;
class Enemy;
class sf::View;
class sf::Font;
class sf::RenderTexture;


class GameState :
    public State
{
private:
    sf::View view;
    sf::Vector2i viewGridPosition;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    sf::Font font;
    PauseMenu* pmenu;

    sf::Shader core_shader;

    Player* player;
    PlayerGui* playerGui;
    sf::Texture texture;


    TileMap* tileMap;

    std::vector<Enemy*> activeEnemies;

    // Functions //
    void initDeferredRender();
    void initView();
    void initKeybinds();
    void initFonts();
    void initTexture();
    void initPauseMenu();
    void initShaders();
    void initPlayers();
    void initPlayerGui();
    void initTileMap();

public:
    GameState(StateData* state_data);
    virtual ~GameState();

    // Function //
    void updateView(const float& dt);
    void updateInput(const float& dt);
    void updatePlayerInput(const float& dt);
    void updatePlayerGui(const float& dt);
    void updatePauseMenuButtons();
    void updateTileMap(const float& dt);
    void updatePlayer(const float& dt);
    void updateEnemies(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);
};

#endif // !GAMESTATE_H