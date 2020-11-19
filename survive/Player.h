#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"

class Entity;

class Player :
    public Entity
{
private:
    // Variables //
    bool attacking;

    // Initializer //
    void initvariables();
    void initComponents();

public:
    Player(float x, float y, sf::Texture& texture);
    virtual ~Player();

    // Accessors //
    AttributeComponent* getAttributeComponent();

    // Functions //
    void loseHP(const int hp);
    void gainHP(const int hp);

    void loseEXP(const unsigned exp);
    void gainEXP(const unsigned exp);

    void updateAttack();
    void updateAnimation(const float& dt);
    void update(const float& dt);

    void render(sf::RenderTarget& target);
};

#endif
