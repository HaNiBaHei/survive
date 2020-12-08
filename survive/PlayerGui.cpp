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
	this->expBar = new gui::ProgressBar(
		1.f, 10.18f, 15.62f, 2.77f,
		this->player->getAttributeComponent()->expNext,
		sf::Color::Yellow, 180,
		this->vm, &this->font
	);
}

void PlayerGui::initHpBar()
{
	this->hpBar = new gui::ProgressBar(
		1.f, 5.5f, 10.4f, 2.8f, 
		this->player->getAttributeComponent()->hpMax, 
		sf::Color::Red, 120,
		this->vm, &this->font
	);
}

void PlayerGui::initPlayerTabs(sf::VideoMode& vm, sf::Font& font, Player& player)
{
	this->playerTabs = new PlayerGuiTabs(vm, font, player);
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
	this->initPlayerTabs(vm, font, *player);
}

PlayerGui::~PlayerGui()
{
	delete this->hpBar;
	delete this->expBar;
	delete this->playerTabs;
}

// Accessors //
const bool PlayerGui::getTabsOpen() const
{
	return this->playerTabs->tabsOpen();
}

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
	this->expBar->update(this->player->getAttributeComponent()->exp);
}

void PlayerGui::updateHpBar()
{
	this->hpBar->update(this->player->getAttributeComponent()->hp);
}

void PlayerGui::updatePlayerTabs()
{
	this->playerTabs->update();
}

void PlayerGui::update(const float& dt)
{
	this->updateLevelBar();
	this->updateScore();
	this->updateExpBar();
	this->updateHpBar();
	this->updatePlayerTabs();
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
	this->expBar->render(target);
}

void PlayerGui::renderHpBar(sf::RenderTarget& target)
{
	this->hpBar->render(target);
}
void PlayerGui::renderPlayerTabs(sf::RenderTarget& target)
{
	this->playerTabs->render(target);
}
// Tabs //

void PlayerGui::render(sf::RenderTarget& target)
{
	this->renderLevelBar(target);
	this->renderScore(target);
	this->renderExpBar(target);
	this->renderHpBar(target);
	this->renderPlayerTabs(target);
	
}
