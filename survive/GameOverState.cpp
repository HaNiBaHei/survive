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
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	// Buttons background //
	this->btnBackground.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height / 5)
		)
	);

	//this->btnBackground.setPosition(gui::p2pX(11.5f, vm), 0.f);
	this->btnBackground.setFillColor(sf::Color(10, 10, 10, 200));

	// Buttons //
	this->buttons["RETRY"] = new gui::Button(
		gui::p2pX(15.f, vm), gui::p2pY(40.f, vm),
		gui::p2pX(13.f, vm), gui::p2pX(3.5f, vm),
		&this->font, "Retry", gui::clacCharSize(vm, 80), // font size
		sf::Color(0, 0, 0, 250), sf::Color(250, 0, 0, 250), sf::Color(20, 20, 20, 50), // text color
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200)); // background color

	this->buttons["EXIT_TOMENU"] = new gui::Button(
		gui::p2pX(15.f, vm), gui::p2pY(70.f, vm),
		gui::p2pX(13.f, vm), gui::p2pX(3.5f, vm),
		&this->font, "MainMenu", gui::clacCharSize(vm, 80),
		sf::Color(0, 0, 0, 250), sf::Color(250, 0, 0, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
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
	:State(state_data)
{
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

const bool GameOverState::SkipState() 
{
	return true;
}

void GameOverState::updateInput(const float& dt)
{

}

void GameOverState::updateGui(const float& dt)
{
}

void GameOverState::updateButtons()
{
	for (auto& it : this->buttons)
	{
		// Update all the button in this state //
		it.second->update(this->mousePosWindow);

	}

	// New game //
	if (this->buttons["RETRY"]->isPressed())
	{
		this->endState();
	}

	if (this->buttons["EXIT_TOMENU"]->isPressed())
	{

		this->endState();
	}
}

void GameOverState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);


	this->updateButtons();
}

void GameOverState::renderGui(sf::RenderTarget& target)
{

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


	target->draw(this->background);

	target->draw(this->btnBackground);

	this->renderButtons(*target);
}
