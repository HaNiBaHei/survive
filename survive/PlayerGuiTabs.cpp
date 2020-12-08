#include "stdafx.h"
#include "PlayerGuiTabs.h"

PlayerGuiTabs::PlayerGuiTabs(sf::VideoMode& vm, sf::Font& font, Player& player)
	: vm(vm), font(font), player(player), characterTab(vm, font, player)
{

}

PlayerGuiTabs::~PlayerGuiTabs()
{

}

void PlayerGuiTabs::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		if(this->characterTab.getHidden())
			this->characterTab.show();
		else
			this->characterTab.hide();
	}
}

void PlayerGuiTabs::render(sf::RenderTarget& target)
{
	this->characterTab.render(target);
}

