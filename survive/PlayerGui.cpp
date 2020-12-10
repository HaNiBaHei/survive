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
	float width = 300.f;
	float height = 25.f;
	float x = 10.f;
	float y = 100.f;

	this->expBarMaxWidth = width;

	this->expBarBack.setSize(sf::Vector2f(width, height));
	this->expBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->expBarBack.setPosition(x, y);

	this->expBarInner.setSize(sf::Vector2f(width, height));
	this->expBarInner.setFillColor(sf::Color::Yellow);
	this->expBarInner.setPosition(this->expBarBack.getPosition());

	this->expBarText.setFont(this->font);
	this->expBarText.setPosition(this->expBarInner.getPosition().x + 10.f, this->expBarInner.getPosition().y + 5.f);
	this->expBarText.setFillColor(sf::Color::Black);
	this->expBarText.setCharacterSize(14);


	/*this->expBar = new gui::ProgressBar(
		1.f, 10.18f, 15.62f, 2.77f,
		sf::Color::Yellow, 180,
		this->vm, &this->font
	);*/
}

void PlayerGui::initHpBar()
{
	float width = 300.f;
	float height = 35.f;
	float x = 10.f;
	float y = 50.f;

	this->hpBarMaxWidth = width;

	this->hpBarBack.setSize(sf::Vector2f(width, height));
	this->hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->hpBarBack.setPosition(x, y);

	this->hpBarInner.setSize(sf::Vector2f(width, height));
	this->hpBarInner.setFillColor(sf::Color::Red);
	this->hpBarInner.setPosition(this->hpBarBack.getPosition());
	
	this->hpBarText.setFont(this->font);
	this->hpBarText.setPosition(this->hpBarInner.getPosition().x + 10.f, this->hpBarInner.getPosition().y + 5.f);
	this->hpBarText.setCharacterSize(16);
	
	
	
	
	/*this->hpBar = new gui::ProgressBar(
		1.f, 5.5f, 10.4f, 2.8f, 
		sf::Color::Red, 120,
		this->vm, &this->font
	);*/
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

void PlayerGui::toggleCharacterTab()
{
	this->playerTabs->toggleTab(PLAYER_TABS::CHARACTER_TAB);
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
	float percent = static_cast<float>(this->player->getattributeComponent()->exp) / static_cast<float>(this->player->getattributeComponent()->expNext);

	this->expBarInner.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(this->expBarMaxWidth * percent)),
			this->expBarInner.getSize().y
		)
	);

	this->expBarString = std::to_string(this->player->getAttributeComponent()->exp) + " / " + std::to_string(this->player->getattributeComponent()->expNext);
	this->expBarText.setString(this->expBarString);

	//this->expBar->update(this->player->getAttributeComponent()->exp, this->player->getAttributeComponent()->expNext);
}

void PlayerGui::updateHpBar()
{
	float percent = static_cast<float>(this->player->getattributeComponent()->hp) / static_cast<float>(this->player->getattributeComponent()->hpMax);

	this->hpBarInner.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(this->hpBarMaxWidth * percent)),
			this->hpBarInner.getSize().y
		)
	);

	this->hpBarString = std::to_string(this->player->getAttributeComponent()->hp) + " / " + std::to_string(this->player->getattributeComponent()->hpMax);
	this->hpBarText.setString(this->hpBarString);

	//this->hpBar->update(this->player->getAttributeComponent()->hp, this->player->getAttributeComponent()->hpMax);
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
	target.draw(this->expBarBack);
	target.draw(this->expBarInner);
	target.draw(this->expBarText);
	//this->expBar->render(target);
}

void PlayerGui::renderHpBar(sf::RenderTarget& target)
{
	target.draw(this->hpBarBack);
	target.draw(this->hpBarInner);
	target.draw(this->hpBarText);
	//this->hpBar->render(target);
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
