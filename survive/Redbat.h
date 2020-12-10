#ifndef REDBAT_H
#define REDBAT_H

#include "Enemy.h"

class Enemy;

class Redbat :
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
    Redbat(float x, float y, sf::Texture& texture_sheet, EnemySpawnerTile& enemy_spawner_tile, Entity& player);
    virtual ~Redbat();

    // Functions //
    void updateAnimation(const float& dt);
    void update(const float& dt, sf::Vector2f& mouse_pos_view, const sf::View& view);
    void render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox);
};
#endif 

