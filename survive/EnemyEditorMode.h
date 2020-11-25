#ifndef ENEMYEDITORMODE_H
#define ENEMYEDITORMODE_H

#include "EditorMode.h"
#include "EnemySpawnerTile.h"

class EditorMode;
class State;
class StateData;
class EditorMode;
class TileMap;
class Tile;
class EnemySpawner;

class EnemyEditorMode :
    public EditorMode
{
private:
    // Variables //
    sf::Text cursorText;
    sf::RectangleShape sidebar;
    sf::RectangleShape selectorRect;
    sf::IntRect textureRect;

    int type;
    int amount;
    int timeToSpawn;
    float maxDistance;

    // Initializers //
    void initVariables();
    void initGui();

public:
    EnemyEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
    virtual ~EnemyEditorMode();

    // Functions //
    void updateInput(const float& dt);
    void updateGui(const float& dt);
    void update(const float& dt);

    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget& target);
};

#endif // !ENEMYEDITORMODE_H
