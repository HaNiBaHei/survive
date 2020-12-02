#ifndef RANGEWEAPON_H
#define RANGEWEAPON_H

#include "Weapon.h"

class Item;

class RangeWeapon :
    public Weapon
{
private:

protected:

public:
    RangeWeapon(unsigned value, std::string texture_file);
    virtual ~RangeWeapon();

    // Functions //
    virtual RangeWeapon* clone() = 0;

    virtual void update(const sf::Vector2f mouse_pos_view, const sf::Vector2f center) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;
};

#endif