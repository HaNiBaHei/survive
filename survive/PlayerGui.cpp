#include "stdafx.h"
#include "PlayerGui.h"
// Initializers //
void PlayerGui::initFont()
{
	this->font.loadFromFile("Fonts/times.ttf");
}

void PlayerGui::initHpBar()
{
	float width = 500.f;
	float height = 50.f;
	float x = 20.f;
	float y = 20.f;


	this->hpBarBack.setSize(sf::Vector2f(width, height));
	this->hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->hpBarBack.setPosition(x, y);

	this->hpBarInner.setSize(sf::Vector2f(width, height));
	this->hpBarInner.setFillColor(sf::Color(250, 20, 20, 200));
	this->hpBarInner.setPosition(this->hpBarBack.getPosition());
}

PlayerGui::PlayerGui(Player* player)
{
	this->player = player;

	this->initFont();
	this->initHpBar();
}

PlayerGui::~PlayerGui()
{

}

// Accessors //


// Functions //
void PlayerGui::updateHpBar()
{

}

void PlayerGui::update(const float& dt)
{

}

void PlayerGui::renderHpBar(sf::RenderTarget& target)
{
	target.draw(this->hpBarBack);
	target.draw(this->hpBarInner);
}

void PlayerGui::render(sf::RenderTarget& target)
{
	this->renderHpBar(target);
}
