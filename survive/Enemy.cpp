#include "stdafx.h"
#include "Enemy.h"
// Initializer //
void Enemy::initvariables()
{
	this->damageTimerMax = 300;
	this->despawnTimerMax = 1000;
}

void Enemy::initAnimations()
{
	
}

// Constructors //
Enemy::Enemy(EnemySpawnerTile& enemy_spawner_tile)
	:enemySpawnerTile(enemy_spawner_tile)
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

EnemySpawnerTile& Enemy::getEnemySpawnerTile()
{
	return this->enemySpawnerTile;
}

const bool Enemy::getDamageTimerDone() const
{
	return this->damageTimer.getElapsedTime().asMilliseconds() >= this->damageTimerMax;
}

const bool Enemy::getDespawnTimerDone() const
{
	return this->despawnTimer.getElapsedTime().asMilliseconds() >= this->despawnTimerMax;
}

void Enemy::resetDamageTimer()
{
	this->damageTimer.restart();
}

// Functions //
void Enemy::generateAttributes(const unsigned level)
{
	switch (level)
	{
	case 1:
		this->gainExp = level * 5 + (rand() % 10 + 1);
		break;
	case 2:
		this->gainExp = level * 9 + (rand() % 10 + 1);
		break;
	case 3:
		this->gainExp = level * 15 + (rand() % 10 + 1);
		break;
	case 4:
		this->gainExp = level * 20 + (rand() % 10 + 1);
		break;
	case 5:
		this->gainExp = level * 50 + (rand() % 10 + 1);
		break;
	default:
		break;
	}
}

void Enemy::loseHp(const int hp)
{
	if (this->attributeComponent)
	{
		this->attributeComponent->loseHP(hp);
	}
}

void Enemy::enemyloseHp(const int hp)
{
	if (this->fireattributeComponent)
	{
		this->fireattributeComponent->loseHP(hp);
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

const bool Enemy::enemyIsDead() const
{
	if (this->fireattributeComponent)
	{
		return this->fireattributeComponent->isDead();
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

const FireAttributeComponent* Enemy::getFireAttributeComp() const
{
	if (this->fireattributeComponent)
		return this->fireattributeComponent;
	else
	{
		std::cout << "ERROR::ENEMY::ATTRIBUTECOMPONENT IS NOT INITIALIZED" << "\n";
		return nullptr;
	}
}

void Enemy::update(const float& dt, sf::Vector2f& mouse_pos_view, const sf::View& view)
{
	if (vectorDistance(this->getPosition(), view.getCenter()) < 500.f)
		this->despawnTimer.restart();
}