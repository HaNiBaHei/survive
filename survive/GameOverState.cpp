#include "stdafx.h"
#include "GameOverState.h"

void GameOverState::initFont()
{
	if (!this->font.loadFromFile("Fonts/times.ttf"))
	{
		throw("ERROR::MAINMENUSTATE:: COULD NOT LOAD FONTS");
	}
}

void GameOverState::initKeybinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";
		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}
}

void GameOverState::initGui()
{
	if (!this->Death.openFromFile("Resources/Sounds/GameOver.wav"))
	{
		std::cout << "ERROR::GAMEOVERSTATE::COULD NOT LOAD SOUND" << "\n";
	}
	Death.setVolume(10);
	Death.play();

	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	//  background //
	this->bgsreen.setSize(
		sf::Vector2f
		(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);
	if (!this->bgtexture.loadFromFile("Resources/images/Backgrounds/GameOver.png"))
	{
		throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->bgsreen.setTexture(&this->bgtexture);

	// Buttons //

	this->buttons["EXIT_TOMENU"] = new gui::Button(
		gui::p2pX(45.f, vm), gui::p2pY(70.f, vm),
		gui::p2pX(13.f, vm), gui::p2pX(3.5f, vm),
		&this->font, "MainMenu", gui::clacCharSize(vm, 80),
		sf::Color(0, 0, 0, 250), sf::Color(250, 0, 0, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
}

void GameOverState::initScore()
{

}

void GameOverState::initSound()
{
	
}




void GameOverState::resetGui()
{
	/*
	* Clear the gui elements and re-initialises the gui
	*
	* @reture void
	*/
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
	this->buttons.clear();

	this->initGui();
}

GameOverState::GameOverState(StateData* state_data)
	:State(state_data), vm(vm)
{
	this->initScore();
	this->initFont();
	this->initKeybinds();
	this->initGui();
	
	this->resetGui();

}

GameOverState::~GameOverState()
{

	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}






void GameOverState::updateButtons()
{
	for (auto& it : this->buttons)
	{
		// Update all the button in this state //
		it.second->update(this->mousePosWindow);

	}

	// New game //
	if (this->buttons["EXIT_TOMENU"]->isPressed())
	{
		this->states->pop();
		this->states->push(new MainMenuState(this->stateData));
	}
}

void GameOverState::updateInput(const float& dt)
{
}

void GameOverState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();
}


void GameOverState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void GameOverState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;


	target->draw(this->bgsreen);


	this->renderButtons(*target);
}
