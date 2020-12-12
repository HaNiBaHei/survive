#include "stdafx.h"
#include "AttributeComponent.h"

void AttributeComponent::initMusic()
{
	if (!levelup.openFromFile("Resources/Sounds/levelUp.wav"))
	{
		std::cout << "ATTRIBUTECOMPONENT::MUSIC:: CANNOT OPEN FILE" << "\n";
	}
}

AttributeComponent::AttributeComponent(int level)
{
	this->damageSword = 1;
	this->score = 0;
	this->level = level;
	this->exp = 0;
	this->expNext = (50 * pow(this->level, 3) - 120 * pow(this->level, 2) + (UINT64)400 * this->level) / 3;
	this->attributePoints = 2;

	this->vitality = 1;
	this->strength = 1;
	this->dexterity = 1;
	this->agility = 1;
	this->intelligence = 1;

	this->updateLevel();
	this->updateStats(true);
}

AttributeComponent::~AttributeComponent()
{

}



// Functions //
std::string AttributeComponent::debugPrint() const
{
	std::stringstream ss;

	ss << "Level: " << this->level << "\n"
		<< "Exp: " << this->exp << "\n"
		<< "Exp Next:" << this->expNext << "\n"
		<< "Attp: " << this->attributePoints << "\n"
		;

	return ss.str();
}

void AttributeComponent::loseHP(const int hp)
{
	this->hp -= hp;

	if (this->hp < 0)
		this->hp = 0;
}

void AttributeComponent::gainHP(const int hp)
{
	this->hp += hp;

	if (this->hp >= this->hpMax)
		this->hp = this->hpMax;
}

void AttributeComponent::loseEXP(const int exp)
{
	this->exp -= exp;

	if (this->exp < 0)
		this->exp = 0;
}

void AttributeComponent::gainExp(const int exp)
{
	this->exp += exp;

	this->updateLevel();
}

void AttributeComponent::loseScore(const int score)
{
	this->score -= score;

	if (this->score < 0)
		this->score = 0;
}

void AttributeComponent::gainScore(const int score)
{
	this->score += score;
}

void AttributeComponent::resetHp()
{
	this->hp = hpMax;
}

const bool AttributeComponent::isDead() const
{
	return this->hp <= 0;
}

void AttributeComponent::updateStats(const bool reset)
{
	

	this->hpMax = 45 + this->level * 5 + this->vitality + this->strength;
	this->damageMin = this->strength + this->agility * 2;
	this->damageMax = this->strength + this->agility * 2;
	this->def = this->agility * 2 + this->agility / 4 + this->strength;

	if (reset)
	{
		this->hp = this->hpMax ;
	}
}

void AttributeComponent::updateLevel()
{
	
	while (this->exp >= this->expNext)
	{
		this->initMusic();
		levelup.setVolume(20);
		levelup.play();
		++this->level;
		this->damageSword += 5;
		this->damageMax += 5;
		this->hpMax += 20;
		this->strength += 2;
		this->agility += 2;
		this->vitality += 2;
		this->hp = hpMax;
		this->exp -= this->expNext;
		this->expNext = (50 * pow(this->level, 3) - 120 * pow(this->level, 2) + (UINT64)400 * this->level) / 3;
		++this->attributePoints;
		this->score = this->score + (this->level - 1) * 200;
	}
}

void AttributeComponent::update()
{
	this->updateLevel();
}
