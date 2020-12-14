#include "stdafx.h"
#include "Orc.h"


void Orc::initvariables()
{

}

void Orc::initAnimations()
{
	this->animationComponent->addAnimation("IDLE", 6.f, 0, 0, 2, 0, 56, 56);
	this->animationComponent->addAnimation("WALK_DOWN", 7.f, 0, 1, 5, 0, 56, 56);
	this->animationComponent->addAnimation("WALK_LEFT", 7.f, 0, 2, 5, 0, 56, 56);
	this->animationComponent->addAnimation("WALK_RIGHT", 7.f, 0, 1, 5, 0, 56, 56);
	this->animationComponent->addAnimation("WALK_UP", 7.f, 0, 0, 2, 5, 56, 56);
	//this->animationComponent->addAnimation("ATTACK", 7.f, 0, 0, 3, 0, 56, 56);
	/*
	this->animationComponent->addAnimation("IDLE", 25.f, 0, 0, 4, 0, 24, 24);
	this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 0, 4, 0, 24, 24);
	this->animationComponent->addAnimation("WALK_LEFT", 11.f, 0, 2, 4, 2, 24, 24);
	this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 0, 1, 4, 1, 24, 24);
	this->animationComponent->addAnimation("WALK_UP", 11.f, 0, 0, 4, 0, 24, 24);*/
	//this->animationComponent->addAnimation("ATTACK", 6.f, 0, 0, 3, 0, 16, 16);
}

void Orc::initAI()
{

}

void Orc::initGui()
{
	this->hpBar.setFillColor(sf::Color::Red);
	this->hpBar.setSize(sf::Vector2f(50.f, 10.f));
	this->hpBar.setPosition(this->sprite.getPosition().x / 2.f, this->sprite.getPosition().x - 30.f);
}

Orc::Orc(float x, float y, sf::Texture& texture_sheet, EnemySpawnerTile& enemy_spawner_tile, Entity& player)
	: Enemy(enemy_spawner_tile)
{
	this->initvariables();
	this->initGui();

	this->createHitboxComponent(this->sprite, 0.f, 0.f, 56.f, 56.f);
	this->createMovementComponent(130.f, 1400.f, 900.f); // Velocity , Accelerate , Drag //
	this->createAnimationComponent(texture_sheet);
	this->createFireAttributeComponent(3);

	this->generateAttributes(this->fireattributeComponent->level);

	this->setPosition(x, y);
	this->initAnimations();

	this->follow = new AIFollow(*this, player);
}

Orc::~Orc()
{
	delete this->follow;
}

// Functions //
void Orc::updateAnimation(const float& dt)
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

void Orc::update(const float& dt, sf::Vector2f& mouse_pos_view, const sf::View& view)
{
	Enemy::update(dt, mouse_pos_view, view);

	this->movementComponent->update(dt);

	// Update GUI Remove later //
	this->hpBar.setSize(sf::Vector2f(50.f * (static_cast<float>(this->fireattributeComponent->hp) / this->fireattributeComponent->hpMax), 5.f));
	this->hpBar.setPosition(this->sprite.getPosition());

	//this->updateAttack();

	this->updateAnimation(dt);

	this->hitboxComponent->update();

	this->follow->update(dt);

}

void Orc::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox)
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