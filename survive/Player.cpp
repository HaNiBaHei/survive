#include "Player.h"

// Initializer //
void Player::initvariables()
{

}

void Player::initComponents()
{
	
}

// Constructors //
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initvariables();

	this->setPosition(x, y);

	this->createMovementComponent(300.f, 15.f, 5.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("IDLE_RIGHT", 10.f, 0, 0, 3, 0, 300, 300);
	this->animationComponent->addAnimation("RUN_RIGHT", 10.f, 0, 1, 5, 1, 300, 300);
}

Player::~Player()
{

}
// Functions //
void Player::update(const float& dt)
{
	this->movementComponent->update(dt);

	if(this->movementComponent->getState(IDLE))
		this->animationComponent->play("IDLE_RIGHT", dt);
	else if(this->movementComponent->getState(MOVING_RIGHT))
		this->animationComponent->play("RUN_RIGHT", dt);
}
