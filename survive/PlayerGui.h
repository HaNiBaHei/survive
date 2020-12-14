#pragma once

#include "PlayerGuiTabs.h"

class Gui;
class Player;
class sf::RectangleShape;

class PlayerGui
{
private:
	Player* player;

	sf::VideoMode& vm;
	sf::Font font;

	// Level //
	std::string levelString;
	sf::Text levelBarText;
	sf::RectangleShape levelBarBack;

	// Score //
	std::string scoreString;
	sf::Text scoreText;

	// EXP Bar //
	std::string expBarString;
	sf::Text expBarText;
	float expBarMaxWidth;
	sf::RectangleShape expBarBack;
	sf::RectangleShape expBarInner;

	gui::ProgressBar* expBar; // Exp remain //

	// HP Bar //
	std::string hpBarString;
	sf::Text hpBarText;
	float hpBarMaxWidth;
	sf::RectangleShape hpBarBack;
	sf::RectangleShape hpBarInner;



	gui::ProgressBar* hpBar; // Hp remain //

	// Player Gui Tabs //
	PlayerGuiTabs* playerTabs;

	// Functions //
	void initFont();
	void initLevelBar();
	void initScore();
	void initExpBar();
	void initHpBar();
	void initPlayerTabs(sf::VideoMode &vm, sf::Font &font, Player &player);

public:
	PlayerGui(Player* player, sf::VideoMode& vm);
	virtual ~PlayerGui();

	// Accessors //
	const bool getTabsOpen() const;
	void toggleCharacterTab();

	// Functions //
	void updateLevelBar();
	void updateScore();
	
	void updateScoreForGameOver(const float& dt);

	void updateExpBar();
	void updateHpBar();
	void updatePlayerTabs();


	void update(const float& dt);

	void renderLevelBar(sf::RenderTarget& target);
	void renderScore(sf::RenderTarget& target);
	void renderExpBar(sf::RenderTarget& target);
	void renderHpBar(sf::RenderTarget& target);
	void renderPlayerTabs(sf::RenderTarget& target);

	void render(sf::RenderTarget& target);
	void renderForGameOver(sf::RenderTarget& target);

	
};

