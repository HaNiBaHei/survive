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
    Sword* weapon;
    
    sf::Music walksound;

    sf::Clock damageTimer;
    sf::Int32 damageTimerMax;
    
    sf::Clock soundTimer;
    sf::Int32 soundTimerMax;

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

    const bool getDamageTimer();
    const bool getSoundTimer();

    const unsigned getHeal() const;

    const unsigned getDamage() const;
    const bool isDead() const;


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
    void update(const float& dt, sf::Vector2f& mouse_pos_view, const sf::View& view);

    void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false);
};

#endif
