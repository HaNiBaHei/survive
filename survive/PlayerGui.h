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


	// HP Bar //
	std::string hpBarString;
	sf::Text hpBarText;
	float hpBarMaxSizeWidth;
	sf::RectangleShape hpBarBack;   //
	sf::RectangleShape hpBarInner; // Hp remain //

	// Functions //
	void initFont();
	void initHpBar();

public:
	PlayerGui(Player* player);
	virtual ~PlayerGui();

	// Accessors //

	// Functions //
	void updateHpBar();
	void update(const float& dt);

	void renderHpBar(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);

	
};

