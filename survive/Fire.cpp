#include "stdafx.h"
#include "Fire.h"


void Fire::initvariables()
{

}

void Fire::initAnimations()
{
	this->animationComponent->addAnimation("IDLE", 12.f, 0, 0, 0, 0, 16, 16);
	this->animationComponent->addAnimation("WALK_DOWN", 7.f, 0, 0, 0, 3, 16, 16);
	this->animationComponent->addAnimation("WALK_LEFT", 7.f, 2, 0, 2, 3, 16, 16);
	this->animationComponent->addAnimation("WALK_RIGHT", 7.f, 3, 0, 3, 3, 16, 16);
	this->animationComponent->addAnimation("WALK_UP", 7.f, 1, 0, 1, 3, 16, 16);
	this->animationComponent->addAnimation("ATTACK", 6.f, 0, 0, 0, 3, 16, 16);
}

void Fire::initAI()
{

}

void Fire::initGui()
{
	this->hpBar.setFillColor(sf::Color::Red);
	this->hpBar.setSize(sf::Vector2f(50.f, 10.f));
	this->hpBar.setPosition(this->sprite.getPosition());
}

Fire::Fire(float x, float y, sf::Texture& texture_sheet, EnemySpawnerTile& enemy_spawner_tile, Entity& player)
	: Enemy(enemy_spawner_tile)
{
	this->initvariables();
	this->initGui();

	this->createHitboxComponent(this->sprite, 0.f, 0.f, 16.f, 16.f);
	this->createMovementComponent(50.f, 2000.f, 900.f); // Velocity , Accelerate , Drag //
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);

	this->generateAttributes(this->attributeComponent->level);

	this->setPosition(x, y);
	this->initAnimations();

	this->follow = new AIFollow(*this, player);
}

Fire::~Fire()
{
	delete this->follow;
}


// Functions //
void Fire::updateAnimation(const float& dt)
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

	if (this->damageTimer.getElapsedTime().asMilliseconds() <= this->damageTimerMax)
	{
		this->sprite.setColor(sf::Color::Red);
	}
	else
		this->sprite.setColor(sf::Color::White);
}

void Fire::update(const float& dt, sf::Vector2f& mouse_pos_view)
{
	this->movementComponent->update(dt);

	// Update GUI Remove later //
	this->hpBar.setSize(sf::Vector2f(50.f * (static_cast<float>(this->attributeComponent->hp) / this->attributeComponent->hpMax), 10.f));
	this->hpBar.setPosition(this->sprite.getPosition());

	//this->updateAttack();

	this->updateAnimation(dt);

	this->hitboxComponent->update();

	this->follow->update(dt);

}

void Fire::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox)
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

	target.draw(this->hpBar);

	if (show_hitbox)
		this->hitboxComponent->render(target);
}