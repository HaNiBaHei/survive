#pragma once

#include "Player.h"

class Player;
class sf::RectangleShape;

class PlayerGui
{
private:
	Player* player;

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
	float expBarMaxSizeWidth;
	sf::RectangleShape expBarBack;   //
	sf::RectangleShape expBarInner; // Exp remain //

	// HP Bar //
	std::string hpBarString;
	sf::Text hpBarText;
	float hpBarMaxSizeWidth;
	sf::RectangleShape hpBarBack;   //
	sf::RectangleShape hpBarInner; // Hp remain //

	// Functions //
	void initFont();
	void initLevelBar();
	void initScore();
	void initExpBar();
	void initHpBar();

public:
	PlayerGui(Player* player);
	virtual ~PlayerGui();

	// Accessors //

	// Functions //
	void updateLevelBar();
	void updateScore();
	void updateExpBar();
	void updateHpBar();
	void update(const float& dt);

	void renderLevelBar(sf::RenderTarget& target);
	void renderScore(sf::RenderTarget& target);
	void renderExpBar(sf::RenderTarget& target);
	void renderHpBar(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);

	
};

