#ifndef PLAYERGUITABS_H
#define PLAYERGUITABS_H

#include "CharacterTab.h"

class PlayerGuiTabs
{
private:
	CharacterTab characterTab;

	// Core //
	sf::VideoMode& vm;
	sf::Font& font;
	Player& player;

	sf::Clock keyTimer;
	float keyTimeMax;

	// Tab //

	// Character Tab //
	

	// Private Functions //
	void initKeyTime();

public:
	PlayerGuiTabs(sf::VideoMode& vm, sf::Font& font, Player& player);
	virtual ~PlayerGuiTabs();

	const bool getKeyTime();
	const bool tabsOpen();

	void update();
	void render(sf::RenderTarget& target);

};

#endif
