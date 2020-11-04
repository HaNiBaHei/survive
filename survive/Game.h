#ifndef GAME_H
#define GAME_H


#include"MainMenuState.h"

class Game
{
private:
	// Variable //
	sf::RenderWindow* window;
	sf::Event sfEvent;
	std::vector<sf::VideoMode> videoMode;
	sf::ContextSettings windowSettings;
	bool fullscreen;


	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	// Initializer //
	void initVariables();
	void initWindow();
	void initKeys();
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