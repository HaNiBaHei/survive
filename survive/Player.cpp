#include "stdafx.h"
#include "Player.h"

// Initializer //
void Player::initvariables()
{
	this->initAttack = false;
	this->attacking = false;
	this->sword = new Sword(1, 2, 5, 30, 20, "Resources/images/Weapon/sword 1.png");
	this->sword->generate(1, 3);
}

void Player::initComponents()
{
	
}

void Player::initAnimations()
{
	this->animationComponent->addAnimation("IDLE", 12.f, 0, 0, 8, 0, 64, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 7.f, 0, 1, 3, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 7.f, 4, 1, 7, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 7.f, 8, 1, 11, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_UP", 7.f, 12, 1, 15, 1, 64, 64);
	this->animationComponent->addAnimation("ATTACK", 6.f, 0, 2, 5, 2, 64, 64);
}

// Constructors //
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initvariables();

	this->createHitboxComponent(this->sprite, 12.f, 10.f, 40.f, 54.f);
	this->createMovementComponent(300.f, 2500.f, 1100.f); // Velocity , Accelerate , Drag //
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);
	this->createSkillComponent();

	this->setPosition(x, y);
	this->initAnimations();
}

Player::~Player()
{
	delete this->sword;
}

// Accessors //

AttributeComponent* Player::getAttributeComponent()
{
	return this->attributeComponent;
}

Weapon* Player::getWeapon() const
{
	return this->sword;
}

const std::string Player::toStringCharacterTab() const
{
	std::stringstream ss;
	AttributeComponent* ac = this->attributeComponent;

	ss << "Level: " << ac->level << "\n"
		<< "Exp: " << ac->exp << "\n"
		<< "Next level: " << ac->expNext << "\n"
		<< "DamageMin: " << ac->damageMin << "\n"
		<< "DamageMax: " << ac->damageMax << "\n";

	return ss.str();
}

const bool& Player::getInitAttack() const
{
	return this->initAttack;
}

void Player::setInitAttack(const bool initAttack)
{
	this->initAttack = initAttack;
}

// Functions //

void Player::loseHP(const int hp)
{
	this->attributeComponent->loseHP(hp);
}

void Player::gainHP(const int hp)
{
	this->attributeComponent->gainHP(hp);
}

void Player::loseScore(const int score)
{
	this->attributeComponent->loseScore(score);
}

void Player::gainScore(const int score)
{
	this->attributeComponent->gainScore(score);
}

void Player::loseEXP(const int exp)
{
	this->attributeComponent->loseEXP(exp);
}

void Player::gainEXP(const int exp)
{
	this->attributeComponent->gainExp(exp);
}



void Player::updateAnimation(const float& dt)
{
	if (this->attacking)
	{

	}

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

void Player::update(const float& dt, sf::Vector2f& mouse_pos_view)
{
	// DEBUG EXP //
	/*if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		this->attributeComponent->gainExp(20);

	system("cls");
	std::cout << this->attributeComponent->debugPrint() << "\n";*/

	this->movementComponent->update(dt);

	
	this->updateAnimation(dt);

	this->hitboxComponent->update();

	this->sword->update(mouse_pos_view, this->getCenter());
}

void Player::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", light_position);

		target.draw(this->sprite, shader);

		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", light_position);

		this->sword->render(target, shader);
	}
	else
	{
		target.draw(this->sprite);
		this->sword->render(target);
	}

	if (show_hitbox)
		this->hitboxComponent->render(target);
}
