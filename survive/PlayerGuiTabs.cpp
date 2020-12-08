#include "stdafx.h"
#include "PlayerGuiTabs.h"

void PlayerGuiTabs::initKeyTime()
{
	this->keyTimeMax = 0.2f;
	this->keyTimer.restart();
}

PlayerGuiTabs::PlayerGuiTabs(sf::VideoMode& vm, sf::Font& font, Player& player)
	: vm(vm), font(font), player(player), characterTab(vm, font, player)
{
	this->initKeyTime();
}

PlayerGuiTabs::~PlayerGuiTabs()
{

}

const bool PlayerGuiTabs::getKeyTime()
{
	if (this->keyTimer.getElapsedTime().asSeconds() >= this->keyTimeMax)
	{
		this->keyTimer.restart();
		return true;
	}
	return false;
}

const bool PlayerGuiTabs::tabsOpen()
{
	return this->characterTab.getOpen();
}

void PlayerGuiTabs::toggleCharacterTab()
{
	if (this->characterTab.getHidden() && this->getKeyTime())
		this->characterTab.show();
	else
		this->characterTab.hide();
}

void PlayerGuiTabs::update()
{
	
}

void PlayerGuiTabs::render(sf::RenderTarget& target)
{
	this->characterTab.render(target);
}

