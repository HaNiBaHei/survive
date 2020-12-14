#pragma once
#include "Enemy.h"
class Orc :
    public Enemy
{
private:
    void initvariables();
    void initAnimations();
    void initAI();
    void initGui();

    sf::RectangleShape hpBar;

    AIFollow* follow;

public:
    Orc(float x, float y, sf::Texture& texture_sheet, EnemySpawnerTile& enemy_spawner_tile, Entity& player);
    virtual ~Orc();

    // Functions //
    void updateAnimation(const float& dt);
    void update(const float& dt, sf::Vector2f& mouse_pos_view, const sf::View& view);
    void render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox);



};

