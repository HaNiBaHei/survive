#include "stdafx.h"
#include "Player.h"

// Initializer //
void Player::initvariables()
{
	this->attacking = false;
}

void Player::initComponents()
{
	
}

// Constructors //
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initvariables();

	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 100.f, 40.f, 150.f, 225.f);
	this->createMovementComponent(400.f, 2000.f, 700.f); // Velocity , Accelerate , Drag //
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(0);

	this->animationComponent->addAnimation("IDLE", 12.f, 0, 0, 3, 0, 300, 300);
	this->animationComponent->addAnimation("RUN", 7.f, 0, 1, 5, 1, 300, 300);
	this->animationComponent->addAnimation("ATTACK", 6.f, 0, 2, 5, 2, 300, 300);
}

Player::~Player()
{

}

// Accessors //

AttributeComponent* Player::getAttributeComponent()
{
	return this->attributeComponent;
}

// Functions //

void Player::loseHP(const int hp)
{
	this->attributeComponent->hp -= hp;

	if (this->attributeComponent->hp < 0)
		this->attributeComponent->hp = 0;
}

void Player::gainHP(const int hp)
{
	this->attributeComponent->hp += hp;

	if (this->attributeComponent->hp >= this->attributeComponent->hpMax)
		this->attributeComponent->hp = this->attributeComponent->hpMax;
}

void Player::loseScore(const int score)
{
	this->attributeComponent->score -= score;

	if (this->attributeComponent->score < 0)
		this->attributeComponent->score = 0;
}

void Player::gainScore(const int score)
{
	this->attributeComponent->score += score;
}

void Player::loseEXP(const int exp)
{
	this->attributeComponent->exp -= exp;

	if (this->attributeComponent->exp < 0)
		this->attributeComponent->exp = 0;
}

void Player::gainEXP(const int exp)
{
	this->attributeComponent->gainExp(exp);
}

void Player::updateAttack()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->attacking = true;
	}
}

void Player::updateAnimation(const float& dt)
{
	if (this->attacking)
	{
		// Set origin depending on direction //
		if (this->sprite.getScale().x > 0.f)		// Facing right //
		{
			this->sprite.setOrigin(-35.f, 0.f);
		}
		else                                        // Facing left //
		{
			this->sprite.setOrigin(340.f -35.f, 0.f);
		}
		// Animate and check for animation end //
		this->animationComponent->play("ATTACK", dt, true);

		if (this->animationComponent->isDone("ATTACK"))
		{
			this->attacking = false;
			// Set origin depending on direction //
			if (this->sprite.getScale().x > 0.f)		// Facing right //
			{
				this->sprite.setOrigin(0.f, 0.f);
			}
			else                                        // Facing left //
			{
				this->sprite.setOrigin(340.f, 0.f);
			}
		}
	}
	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		if (this->sprite.getScale().x < 0.f)
		{
			this->sprite.setOrigin(0.f, 0.f);
			this->sprite.setScale(1.f, 1.f);
		}
		this->animationComponent->play("RUN", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		if (this->sprite.getScale().x > 0.f)
		{
			this->sprite.setOrigin(340.f, 0.f);
			this->sprite.setScale(-1.f, 1.f);
		}
		this->animationComponent->play("RUN", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("RUN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("RUN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
}

void Player::update(const float& dt)
{
	// DEBUG EXP //
	/*if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		this->attributeComponent->gainExp(20);

	system("cls");
	std::cout << this->attributeComponent->debugPrint() << "\n";*/

	this->movementComponent->update(dt);

	this->updateAttack();
	
	this->updateAnimation(dt);

	this->hitboxComponent->update();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	if (this->hitboxComponent)
		this->hitboxComponent->render(target);
}
