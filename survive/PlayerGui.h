#pragma once

#include "Player.h"
#include "Gui.h"

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
	gui::ProgressBar* expBar; // Exp remain //

	// HP Bar //
	gui::ProgressBar* hpBar; // Hp remain //

	// Tab //

	// Character Tab //
	sf::RectangleShape CharacterTabBack;
	sf::Text CharacterInfoText;

	// Functions //
	void initFont();
	void initLevelBar();
	void initScore();
	void initExpBar();
	void initHpBar();

public:
	PlayerGui(Player* player, sf::VideoMode& vm);
	virtual ~PlayerGui();

	// Accessors //

	// Functions //
	void updateLevelBar();
	void updateScore();
	void updateExpBar();
	void updateHpBar();
	void updateCharacterTab();

	// Tab //
	void initTabMenu();
	void initCharacterTab();

	void update(const float& dt);

	void renderLevelBar(sf::RenderTarget& target);
	void renderScore(sf::RenderTarget& target);
	void renderExpBar(sf::RenderTarget& target);
	void renderCharacterTab(sf::RenderTarget& target);
	void renderHpBar(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);

	
};

