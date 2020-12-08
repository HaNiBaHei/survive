#ifndef PLAYERGUITABS_H
#define PLAYERGUITABS_H

#include "Player.h"
#include "Gui.h"

class PlayerGuiTabs
{
private:

	// Core //
	sf::VideoMode& vm;
	sf::Font& font;
	Player& player;

	// Tab //

	// Character Tab //
	sf::RectangleShape CharacterTabBack;
	sf::Text CharacterInfoText;

public:
	PlayerGuiTabs(sf::VideoMode& vm, sf::Font& font, Player& player);
	virtual ~PlayerGuiTabs();

	// Functions //
	void initTabMenu();
	void initCharacterTab();
};

#endif
