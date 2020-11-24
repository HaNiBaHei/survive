#include "stdafx.h"
#include "Enemy.h"
// Initializer //
void Enemy::initvariables()
{
}

void Enemy::initAnimations()
{
	this->animationComponent->addAnimation("IDLE", 12.f, 0, 0, 8, 0, 64, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 7.f, 0, 1, 3, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 7.f, 4, 1, 7, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 7.f, 8, 1, 11, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_UP", 7.f, 12, 1, 15, 1, 64, 64);
	this->animationComponent->addAnimation("ATTACK", 6.f, 0, 2, 5, 2, 64, 64);
}

// Constructors //
Enemy::Enemy(EnemySpawner& enemy_spawner, float x, float y, sf::Texture& texture_sheet)
	: enemySpawner(enemy_spawner)
{
	this->initvariables();

	this->createHitboxComponent(this->sprite, 12.f, 10.f, 40.f, 54.f);
	this->createMovementComponent(200.f, 2000.f, 900.f); // Velocity , Accelerate , Drag //
	this->createAnimationComponent(texture_sheet);

	this->setPosition(x, y);
	this->initAnimations();
}

Enemy::~Enemy()
{

}
// Functions //
void Enemy::updateAnimation(const float& dt)
{

	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
}

void Enemy::update(const float& dt, sf::Vector2f& mouse_pos_view)
{
	this->movementComponent->update(dt);

	//this->updateAttack();

	this->updateAnimation(dt);

	this->hitboxComponent->update();

}

void Enemy::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", light_position);
		target.draw(this->sprite, shader);
	}
	else
	{
		target.draw(this->sprite);
	}

	if (show_hitbox)
		this->hitboxComponent->render(target);
}