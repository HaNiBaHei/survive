#include "stdafx.h"
#include "Game.h"

// Static Function //



// Initializer //
void Game::initVariables()
{
	this->window = NULL;

	this->dt = 0.f;
}

void Game::initGraphicsSettings()
{
	this->gfxSettings.loadFromeFile("Config/graphics.ini");

	

}



void Game::initWindow()
{
	if(this->gfxSettings.fullscreen)
		this->window = new sf::RenderWindow(
			this->gfxSettings.resolution, 
			this->gfxSettings.title, 
			sf::Style::Fullscreen, 
			this->gfxSettings.contextSettings);
	else
		this->window = new sf::RenderWindow(
			this->gfxSettings.resolution,
			this->gfxSettings.title,
			sf::Style::Titlebar | sf::Style::Close, 
			this->gfxSettings.contextSettings);

	this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
	this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);
}

void Game::initKeys()
{
	std::ifstream ifs("Config/supported_keys.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		int key_value = 0;
		while (ifs >> key >> key_value)
		{
			this->supportedKeys[key] = key_value;
		}
	}
		
	ifs.close();

	// Debug Remove later //
	for (auto i : this->supportedKeys)
	{
		std::cout << i.first << " " << i.second << "\n";
	}
}

void Game::initStates()
{
	this->states.push(new MainMenuState(this->window, this->gfxSettings, &this->supportedKeys, &this->states));
}

// Constructor //
Game::Game()
{
	this->initVariables();
	this->initGraphicsSettings();
	this->initWindow();
	this->initKeys();
	this->initStates();
}

Game::~Game()
{
	delete this->window;
	
	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}


// Function //
void Game::endApplication()
{
	std::cout << "Ending Application" << "\n";
}

void Game::updateDt()
{
	this->dt = this->dtClock.restart().asSeconds();


}

void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::update()
{
	this->updateSFMLEvents();

	if (!this->states.empty())
	{
		this->states.top()->update(dt);

		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	// App End
	else
	{
		this->endApplication();
		this->window->close();
	}
}

void Game::render()
{
	this->window->clear();

	// Render Items//
	if (!this->states.empty())
		this->states.top()->render();
	

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();

	}
}

