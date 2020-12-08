#include "stdafx.h"
#include "PlayerGuiTabs.h"

PlayerGuiTabs::PlayerGuiTabs(sf::VideoMode& vm, sf::Font& font, Player& player)
	: vm(vm), font(font), player(player)
{
	this->initTabMenu();
	this->initCharacterTab();
}

PlayerGuiTabs::~PlayerGuiTabs()
{

}

void PlayerGuiTabs::initTabMenu()
{


}

void PlayerGuiTabs::initCharacterTab()
{
	// Background //
	this->CharacterTabBack.setFillColor(sf::Color(50, 50, 50, 180));
	this->CharacterTabBack.setSize(sf::Vector2f(gui::p2pX(30.f, this->vm), static_cast<float>(this->vm.height)));

	// Text //
	this->CharacterInfoText.setFont(this->font);
	this->CharacterInfoText.setCharacterSize(gui::clacCharSize(this->vm, 120));
	this->CharacterInfoText.setFillColor(sf::Color::White);
	this->CharacterInfoText.setPosition(this->CharacterTabBack.getPosition().x + 20.f, this->CharacterTabBack.getPosition().y + 20.f);

}