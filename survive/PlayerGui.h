#pragma once

#include "Player.h"

class Player;
class sf::RectangleShape;

class PlayerGui
{
private:
	Player* player;

	sf::Font font;

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
	void initExpBar();
	void initHpBar();

public:
	PlayerGui(Player* player);
	virtual ~PlayerGui();

	// Accessors //

	// Functions //
	void updateExpBar();
	void updateHpBar();
	void update(const float& dt);

	void renderExpBar(sf::RenderTarget& target);
	void renderHpBar(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);

	
};

