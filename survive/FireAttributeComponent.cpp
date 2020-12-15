#include "stdafx.h"
#include "FireAttributeComponent.h"

FireAttributeComponent::FireAttributeComponent(int level)
{
	
	this->score = 0;
	this->level = level;
	this->exp = 0;
	this->expNext = (50 * pow(this->level, 3) - 150 * pow(this->level, 2) + (UINT64)400 * this->level) / 3;
	this->attributePoints = 2;

	switch (level)
	{
	case 1:
		this->updateStatsLevel1(true);
		break;
	case 2:
		this->updateStatsLevel2(true);
		break;
	case 3:
		this->updateStatsLevel3(true);
		break;
	case 4:
		this->updateStatsLevel4(true);
		break;
	case 5:
		this->updateStatsLevel5(true);
		break;
	default:
		break;
	}



}

FireAttributeComponent::~FireAttributeComponent()
{
}

void FireAttributeComponent::loseHP(const int hp)
{
	this->hp -= hp;

	if (this->hp < 0)
		this->hp = 0;
}

void FireAttributeComponent::gainHP(const int hp)
{
	this->hp += hp;

	if (this->hp >= this->hpMax)
		this->hp = this->hpMax;
}

const bool FireAttributeComponent::isDead() const
{
	return this->hp <= 0;
}

void FireAttributeComponent::updateStatsLevel1(const bool reset)
{
	this->hpMax = 15 ;
	this->damageMax = 2;

	if (reset)
	{
		this->hp = this->hpMax;
	}
}

void FireAttributeComponent::updateStatsLevel2(const bool reset)
{
	this->hpMax = 30;
	this->damageMax = 5;

	if (reset)
	{
		this->hp = this->hpMax;
	}
}

void FireAttributeComponent::updateStatsLevel3(const bool reset)
{
	this->hpMax = 40;
	this->damageMax = 10;

	if (reset)
	{
		this->hp = this->hpMax;
	}
}

void FireAttributeComponent::updateStatsLevel4(const bool reset)
{
	this->hpMax = 48;
	this->damageMax = 15;

	if (reset)
	{
		this->hp = this->hpMax;
	}
}

void FireAttributeComponent::updateStatsLevel5(const bool reset)
{
	this->hpMax = 300;
	this->damageMax = 30;

	if (reset)
	{
		this->hp = this->hpMax;
	}
}


void FireAttributeComponent::update()
{
}
