#include "stdafx.h"
#include "Sword.h"

Sword::Sword(unsigned value)
	:MeleeWeapon(value)
{
	// Weapon //
	if (!this->weapon_texture.loadFromFile("Resources/images/Weapon/sword 5.png"))
		std::cout << "ERROR::PLAYER::COULD NOT LOAD WEAPON TEXTURE" << "\n";

	this->weapon_sprite.setTexture(this->weapon_texture);
	this->weapon_sprite.setScale(0.5f, 0.5f);

	this->weapon_sprite.setOrigin(
		this->weapon_sprite.getGlobalBounds().width / 2.f,
		this->weapon_sprite.getGlobalBounds().height
	);
}

Sword::~Sword()
{

}

Sword* Sword::clone()
{
	return new Sword(*this);
}

void Sword::update(const sf::Vector2f mouse_pos_view, const sf::Vector2f center)
{
	// Update Weapon //
	this->weapon_sprite.setPosition(center);

	float dX = mouse_pos_view.x - this->weapon_sprite.getPosition().x;
	float dY = mouse_pos_view.y - this->weapon_sprite.getPosition().y;

	const float PI = 3.14159265;
	float deg = atan2(dY, dX) * 180 / PI;

	this->weapon_sprite.setRotation(deg + 135.f); // Need to fix sword picture //
}

void Sword::render(sf::RenderTarget& target, sf::Shader* shader)
{
	if(shader)
		target.draw(this->weapon_sprite, shader);
	else
		target.draw(this->weapon_sprite);
}

