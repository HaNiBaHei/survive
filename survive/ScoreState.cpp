#include "stdafx.h"
#include "ScoreState.h"

void ScoreState::initFont()
{
	if (!this->font.loadFromFile("Fonts/times.ttf"))
	{
		throw("ERROR::MAINMENUSTATE:: COULD NOT LOAD FONTS");
	}
}

void ScoreState::initKeybinds()
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

void ScoreState::initGui()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	

	// Background //
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);
	if (!this->backgroundTexture.loadFromFile("Resources/images/Backgrounds/background2.png"))
	{
		throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);

	

	// Buttons //
	this->buttons["BACK"] = new gui::Button(
		gui::p2pX(90.f, vm), gui::p2pY(90.1f, vm),
		gui::p2pX(7.81f, vm), gui::p2pY(6.f, vm),
		&this->font, "Back", gui::clacCharSize(vm, 80),
		sf::Color(0, 0, 0, 250), sf::Color(250, 0, 0, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 150), sf::Color(150, 150, 150, 150), sf::Color(20, 20, 20, 150));

	// Init Text //
	
}

void ScoreState::resetGui()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	this->buttons.clear();

	this->initGui();
}

ScoreState::ScoreState(StateData* state_data)
	: State(state_data)
{
	this->initFont();
	this->initGui();
	
}

ScoreState::~ScoreState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void ScoreState::updateInput(const float& dt)
{

}

void ScoreState::updateGui(const float& dt)
{
	// Buttons //
	for (auto& it : this->buttons)
	{
		// Update all the button in this state //
		it.second->update(this->mousePosWindow);
	}

	// Buttons Functionality //
	// Quit the game //
		if (this->buttons["BACK"]->isPressed())
		{
			this->states->push(new MainMenuState(this->stateData));
			this->endState();
		}
}

void ScoreState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateGui(dt);

}

void ScoreState::renderGui(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void ScoreState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	target->draw(this->btnBackground);

	this->renderGui(*target);

}
