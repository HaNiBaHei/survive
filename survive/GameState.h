#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGui.h"
#include "Sword.h"
#include "Bow.h"
#include "TextTagSystem.h"

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

    std::vector<Enemy*> activeEnemies;
    EnemySystem* enemySystem;

    TileMap* tileMap;

    // System //
    TextTagSystem* tts;

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
    void initEnemySystem();
    void initTileMap();
    void initSystems();

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
    void updateCombatAndEnemies(const float& dt);
    void updateCombat(Enemy* enemy, const int index, const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);
};

#endif // !GAMESTATE_H