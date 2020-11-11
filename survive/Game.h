#ifndef GAME_H
#define GAME_H


#include"MainMenuState.h"

class Game
{
private:

	// Variable //
	GraphicsSettings gfxSettings;
	StateData stateData;
	sf::RenderWindow* window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	float gridSize;

	// Initializer //
	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initKeys();
	void initStateData();
	void initStates();
	

public:
	Game();
	virtual ~Game();

	// function //

	// Regular //
	void endApplication();

	// Update //
	void updateDt();
	void updateSFMLEvents();
	void update();

	// Render //
	void render();

	// Core //
	void run();
};
#endif // !GAME_H