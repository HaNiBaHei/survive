#include "stdafx.h"
#include "AttributeComponent.h"

AttributeComponent::AttributeComponent(int level)
{
	this->score = 0;
	this->level = level;
	this->exp = 0;
	this->expNext = 0;
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

void AttributeComponent::updateStats(const bool reset)
{
	
	this->hpMax		= this->vitality * 3 + (this->strength / 3);
	this->damageMin = this->strength * 2 + (this->strength / 4) + (this->agility / 3);
	this->damageMax = this->strength * 2 + this->strength + (this->agility / 3);
	this->accuracy	= this->dexterity * 2 + (this->agility * 2);
	this->def		= this->dexterity * 2 + (this->agility / 3);
	this->luck		= this->intelligence * 2 + (this->intelligence / 5);

	if (reset)
	{
		this->hp = this->hpMax ;
	}
}

void AttributeComponent::updateLevel()
{
	while (this->exp >= this->expNext)
	{
		this->level++;
		this->exp -= this->expNext;
		this->expNext = static_cast<int>((50 / 3) * (pow(this->level + 1, 2)) - 8 * pow(this->level + 1, 2) + ((this->level + 1) * 20) - 12);
		++this->attributePoints;
		this->score = (this->level - 1) * 200;
	}
}

void AttributeComponent::update()
{
	this->updateLevel();
}
