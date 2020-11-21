#include "stdafx.h"
#include "SkillComponent.h"

SkillComponent::SkillComponent()
{
	this->skills["health"];
	this->skills["erdurance"];
	this->skills["melee"];
	this->skills["range"];
	this->skills["accuracy"]; // death eyes //
	this->skills["defence"];  // iron body //

	this->skills["dash"];
}

SkillComponent::~SkillComponent()
{

}

const int SkillComponent::getSkill(std::string key) const
{
	if (this->skills.count(key))
		return this->skills.at(key).getLevel();
	else
		throw("ERROR::SKILLCOMPONENT::SKILL DOSE NOT EXIST" + key);
}
