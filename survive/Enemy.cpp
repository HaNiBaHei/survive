#include "stdafx.h"
#include "Enemy.h"
// Initializer //
void Enemy::initvariables()
{
	this->gainExp = 10;
}

void Enemy::initAnimations()
{
	
}

// Constructors //
Enemy::Enemy()
	
{
	this->initvariables();
	this->initAnimations();
}

Enemy::~Enemy()
{

}

const unsigned& Enemy::getGainExp() const
{
	return this->gainExp;
}

// Functions //
void Enemy::generateAttributes(const unsigned level)
{
	this->gainExp = level * 5 + (rand() % 10 + 1);
}

void Enemy::loseHp(const int hp)
{
	if (this->attributeComponent)
	{
		this->attributeComponent->loseHP(hp);
	}
}

const bool Enemy::isDead() const
{
	if (this->attributeComponent)
	{
		return this->attributeComponent->isDead();
	}

	return false;
}

const AttributeComponent* Enemy::getAttributeComp() const
{
	if (this->attributeComponent)
		return this->attributeComponent;
	else
	{
		std::cout << "ERROR::ENEMY::ATTRIBUTECOMPONENT IS NOT INITIALIZED" << "\n";
		return nullptr;
	}
}

