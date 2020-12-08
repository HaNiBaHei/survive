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

	// Tab //

	// Character Tab //
	

public:
	PlayerGuiTabs(sf::VideoMode& vm, sf::Font& font, Player& player);
	virtual ~PlayerGuiTabs();

	void update();
	void render(sf::RenderTarget& target);

};

#endif
