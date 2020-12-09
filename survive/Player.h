#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Sword.h"

class Entity;

class Player :
    public Entity
{
private:
    // Variables //
    bool initAttack;
    bool attacking;
    Sword* sword;
    

    // Initializer //
    void initvariables();
    void initComponents();
    void initAnimations();

public:
    Player(float x, float y, sf::Texture& texture);
    virtual ~Player();

    // Accessors //
    AttributeComponent* getAttributeComponent();
    Weapon* getWeapon() const;

    const std::string toStringCharacterTab() const;
    const bool& getInitAttack() const;

    // Modifiers //
    void setInitAttack(const bool initAttack);

    // Functions //
    void loseHP(const int hp);
    void gainHP(const int hp);

    void loseScore(const int score);
    void gainScore(const int score);

    void loseEXP(const int exp);
    void gainEXP(const int exp);
    

    void updateAnimation(const float& dt);
    void update(const float& dt, sf::Vector2f& mouse_pos_view);

    void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false);
};

#endif
