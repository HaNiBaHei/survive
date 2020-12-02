#include "stdafx.h"
#include "Enemy.h"
// Initializer //
void Enemy::initvariables()
{
}

void Enemy::initAnimations()
{
	
}

// Constructors //
Enemy::Enemy()
	
{
	
}

Enemy::~Enemy()
{

}

// Functions //
void Enemy::loseHp(const int hp)
{
	if (this->attributeComponent)
	{
		this->attributeComponent->loseHP(hp);
	}
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

