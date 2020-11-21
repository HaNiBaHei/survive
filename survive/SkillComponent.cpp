#include "stdafx.h"
#include "SkillComponent.h"

SkillComponent::SkillComponent()
{
	this->skills.push_back(Skill(Skills::MELEE));
	this->skills.push_back(Skill(Skills::RANGE));
	this->skills.push_back(Skill(Skills::DEATHEYE));
	this->skills.push_back(Skill(Skills::IRONBODY));
}

SkillComponent::~SkillComponent()
{

}

const int SkillComponent::getSkill(const int skill) const
{
	if (skill < 0 || skill >= this->skills.size())
		throw("ERROR::SKILLCOMPONENT::GETSKILL::SKILL DOSE NOT EXIST" + skill);
	else
		return this->skills[skill].getLevel();
}

const void SkillComponent::gainExp(const int skill, const int exp)
{
	if (skill < 0 || skill >= this->skills.size())
		throw("ERROR::SKILLCOMPONENT::GAINEXP::SKILL DOSE NOT EXIST" + skill);
	else
		this->skills[skill].gainExp(exp);
}
