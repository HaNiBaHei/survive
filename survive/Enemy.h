#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

class Entity;

class Enemy :
    public Entity
{
private:


	// Initializer //
	void initvariables();
	void initAnimations();

public:
    Enemy(float x, float y, sf::Texture& texture_sheet);
	virtual ~Enemy();
	
	// Functions //
	void update(const float& dt, sf::Vector2f& mouse_pos_view);
	void render(sf::RenderTarget& target, sf::Shader* shader, const bool show_hitbox);
	
};

#endif