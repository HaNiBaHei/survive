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
void Enemy::takeDamage(const int damage)
{
	this->attributeComponent->loseHP(damage);
}

