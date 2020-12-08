#include "stdafx.h"
#include "PlayerGuiTabs.h"

void PlayerGuiTabs::initTabs()
{
	this->tabs.push_back(new CharacterTab(vm, font, player));
}

void PlayerGuiTabs::initKeyTime()
{
	this->keyTimeMax = 0.2f;
	this->keyTimer.restart();
}

PlayerGuiTabs::PlayerGuiTabs(sf::VideoMode& vm, sf::Font& font, Player& player)
	: vm(vm), font(font), player(player)
{
	this->initTabs();
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
	// Loop tabs and check if any are open //
	bool open = false;
	for (size_t i = 0; i < this->tabs.size() && !open; i++)
	{
		if (this->tabs[i]->getOpen())
			open = true;
	}
	return open;
}

void PlayerGuiTabs::toggleTab(const int tab_index)
{
	if(tab_index >= 0 || tab_index < this->tabs.size())
	this->tabs[tab_index]->toggle();
}

void PlayerGuiTabs::update()
{
	for (size_t i = 0; i < this->tabs.size(); i++)
	{
		if(this->tabs[i]->getOpen())
		   this->tabs[i]->update();
	}
}

void PlayerGuiTabs::render(sf::RenderTarget& target)
{
	for (size_t i = 0; i < this->tabs.size(); i++)
	{
		if (this->tabs[i]->getOpen())
			this->tabs[i]->render(target);
	}
	
}

