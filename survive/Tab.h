#ifndef TAP_H
#define TAP_H

#include "Player.h"
#include "Gui.h"

class Tab
{
protected:
	sf::VideoMode& vm;
	sf::Font& font;
	Player& player;

	bool hidden;

public:
	Tab(sf::VideoMode& vm, sf::Font& font, Player& player, bool hidden);
	virtual ~Tab();

	// Accessors //
	const bool& getHidden() const;

	// Functions //
	void hide();
	void show();

	virtual void update() = 0;
	virtual void render(sf::RenderTarget& target) = 0;

};

#endif // !TAP_H
