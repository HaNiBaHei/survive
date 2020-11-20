#include "stdafx.h"
#include "PlayerGui.h"
// Initializers //
void PlayerGui::initFont()
{
	this->font.loadFromFile("Fonts/times.ttf");
}

void PlayerGui::initLevelBar()
{
	float width = gui::p2pX(1.6f, this->vm);
	float height = gui::p2pY(2.8f, this->vm);
	float x = gui::p2pX(1.f, this->vm);
	float y = gui::p2pY(1.9f, this->vm);

	this->levelBarBack.setSize(sf::Vector2f(width, height));
	this->levelBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->levelBarBack.setPosition(x, y);

	this->levelBarText.setFont(this->font);
	this->levelBarText.setCharacterSize(gui::clacCharSize(this->vm, 120));
	this->levelBarText.setPosition(
		this->levelBarBack.getPosition().x + gui::p2pX(0.53f, this->vm),
		this->levelBarBack.getPosition().y + gui::p2pY(0.5f, this->vm)
	);
}

void PlayerGui::initScore()
{
	float x = gui::p2pX(1.f, this->vm);
	float y = gui::p2pY(13.8f, this->vm);

	this->scoreText.setFont(this->font);
	this->scoreText.setCharacterSize(gui::clacCharSize(this->vm, 110));
	this->scoreText.setPosition(x + 10.f, y + 5.f);
}

void PlayerGui::initExpBar()
{
	float width = gui::p2pX(15.62f, this->vm);
	float height = gui::p2pY(2.77f, this->vm);
	float x = gui::p2pX(1.f, this->vm);
	float y = gui::p2pY(10.18f, this->vm);

	this->expBarMaxSizeWidth = width;


	this->expBarBack.setSize(sf::Vector2f(width, height));
	this->expBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->expBarBack.setPosition(x, y);

	this->expBarInner.setSize(sf::Vector2f(width, height));
	this->expBarInner.setFillColor(sf::Color(20, 20, 250, 200));
	this->expBarInner.setPosition(this->expBarBack.getPosition());

	this->expBarText.setFont(this->font);
	this->expBarText.setCharacterSize(gui::clacCharSize(this->vm, 120));
	this->expBarText.setPosition(
		this->expBarInner.getPosition().x + gui::p2pX(0.53f, this->vm),
		this->expBarInner.getPosition().y + gui::p2pY(0.5f, this->vm)
	);
	
}

void PlayerGui::initHpBar()
{
	float width = gui::p2pX(15.62f, this->vm);
	float height = gui::p2pY(3.7f, this->vm);
	float x = gui::p2pX(1.f, this->vm);
	float y = gui::p2pY(5.5f, this->vm);

	this->hpBarMaxSizeWidth = width;


	this->hpBarBack.setSize(sf::Vector2f(width, height));
	this->hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->hpBarBack.setPosition(x, y);

	this->hpBarInner.setSize(sf::Vector2f(width, height));
	this->hpBarInner.setFillColor(sf::Color(250, 20, 20, 200));
	this->hpBarInner.setPosition(this->hpBarBack.getPosition());

	this->hpBarText.setFont(this->font);
	this->hpBarText.setCharacterSize(gui::clacCharSize(this->vm, 110));
	this->hpBarText.setPosition(
		this->hpBarInner.getPosition().x + gui::p2pX(0.53f, this->vm),
		this->hpBarInner.getPosition().y + gui::p2pY(0.5f, this->vm)
	);
}

PlayerGui::PlayerGui(Player* player, sf::VideoMode& vm)
	: vm(vm)
{
	this->player = player;

	this->initFont();
	this->initLevelBar();
	this->initScore();
	this->initExpBar();
	this->initHpBar();
}

PlayerGui::~PlayerGui()
{

}
// Accessors //

// Functions //

void PlayerGui::updateLevelBar()
{
	this->levelString = std::to_string(this->player->getAttributeComponent()->level);
	this->levelBarText.setString(this->levelString);
}

void PlayerGui::updateScore()
{
	this->scoreString = "Score: " + std::to_string(this->player->getAttributeComponent()->score);
	this->scoreText.setString(this->scoreString);
}

void PlayerGui::updateExpBar()
{
	float percent =
		static_cast<float>(this->player->getAttributeComponent()->exp) /
		static_cast<float>(this->player->getAttributeComponent()->expNext);



	this->expBarInner.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(this->expBarMaxSizeWidth * percent)),
			this->expBarInner.getSize().y
		)
	);

	this->expBarString = std::to_string(this->player->getAttributeComponent()->exp) + "/" + std::to_string(this->player->getAttributeComponent()->expNext);
	this->expBarText.setString(this->expBarString);
}

void PlayerGui::updateHpBar()
{
	float percent = 
		static_cast<float>(this->player->getAttributeComponent()->hp) /
		static_cast<float>(this->player->getAttributeComponent()->hpMax);



	this->hpBarInner.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(this->hpBarMaxSizeWidth * percent)), 
			this->hpBarInner.getSize().y
		)
	);

	this->hpBarString = std::to_string(this->player->getAttributeComponent()->hp) + "/" + std::to_string(this->player->getAttributeComponent()->hpMax);
	this->hpBarText.setString(this->hpBarString);
}

void PlayerGui::update(const float& dt)
{
	this->updateLevelBar();
	this->updateScore();
	this->updateExpBar();
	this->updateHpBar();
}

void PlayerGui::renderLevelBar(sf::RenderTarget& target)
{
	target.draw(this->levelBarBack);
	target.draw(this->levelBarText);
}

void PlayerGui::renderScore(sf::RenderTarget& target)
{
	target.draw(this->scoreText);
}

void PlayerGui::renderExpBar(sf::RenderTarget& target)
{
	target.draw(this->expBarBack);
	target.draw(this->expBarInner);
	target.draw(this->expBarText);
}

void PlayerGui::renderHpBar(sf::RenderTarget& target)
{
	target.draw(this->hpBarBack);
	target.draw(this->hpBarInner);
	target.draw(this->hpBarText);
}

void PlayerGui::render(sf::RenderTarget& target)
{
	this->renderLevelBar(target);
	this->renderScore(target);
	this->renderExpBar(target);
	this->renderHpBar(target);
	
}
