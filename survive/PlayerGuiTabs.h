#ifndef PLAYERGUITABS_H
#define PLAYERGUITABS_H

#include "CharacterTab.h"

enum PLAYER_TABS {CHARACTER_TAB = 0, INVENTORY_TAB};

class PlayerGuiTabs
{
private:
	std::vector<Tab*> tabs;

	// Core //
	sf::VideoMode& vm;
	sf::Font& font;
	Player& player;

	sf::Clock keyTimer;
	float keyTimeMax;

	// Tab //

	// Character Tab //
	

	// Private Functions //
	void initTabs();
	void initKeyTime();

public:
	PlayerGuiTabs(sf::VideoMode& vm, sf::Font& font, Player& player);
	virtual ~PlayerGuiTabs();

	const bool getKeyTime();
	const bool tabsOpen();

	void toggleTab(const int tab_index);

	void update();
	void render(sf::RenderTarget& target);

};

#endif
