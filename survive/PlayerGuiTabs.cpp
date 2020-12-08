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

}

void PlayerGuiTabs::render(sf::RenderTarget* target)
{
	this->characterTab.render(target);
}

