#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"


class Player :
    public Entity
{
private:
    // Variables //

    // Initializer //
    void initvariables();
    void initComponents();

public:
    Player(float x, float y, sf::Texture& texture);
    virtual ~Player();


    // Functions //
    virtual void update(const float& dt);
};

#endif