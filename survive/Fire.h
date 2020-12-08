#ifndef FIRE_H
#define FIRE_H

#include "Enemy.h"

class Enemy;

class Fire :
    public Enemy
{
private:
    void initvariables();
    void initAnimations();
    void initGui();

    sf::RectangleShape hpBar;

public:
    Fire(float x, float y, sf::Texture& texture_sheet, EnemySpawnerTile& enemy_spawner_tile);
    virtual ~Fire();

    // Functions //
    void updateAnimation(const float& dt);
    void update(const float& dt, sf::Vector2f& mouse_pos_view);
    void render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox);
};
#endif // !FIRE_H

