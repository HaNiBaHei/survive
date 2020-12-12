#include "stdafx.h"
#include "MainMenuState.h"

// Initializer //
void MainMenuState::initVariables()
{
}

void MainMenuState::initMusic()
{
	if (!this->bgMusic.openFromFile("Resources/Sounds/MainmenuTrack.wav"))
	{
		std::cout << "ERROR::MAINMENUSTATE::COULD NOT LOAD MUSIC" << "\n";
	}
	this->bgMusic.setVolume(3);
	this->bgMusic.setLoop(true);
	this->bgMusic.play();

	
}



void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/times.ttf"))
	{
		throw("ERROR::MAINMENUSTATE:: COULD NOT LOAD FONTS");
	}
}

void MainMenuState::initKeybinds()
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

	ifs.close();
}

void MainMenuState::initGui()
{
	
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
	// Backgrouund //
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);
	if (!this->backgroundTexture.loadFromFile("Resources/images/Backgrounds/background4.png"))
	{
		throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);

	// Buttons background //
	this->btnBackground.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width / 5),
			static_cast<float>(vm.height)
		)
	);

	this->btnBackground.setPosition(gui::p2pX(11.5f, vm), 0.f);
	this->btnBackground.setFillColor(sf::Color(10, 10, 10, 200));

	// Buttons //
	this->buttons["GAME_STATE"] = new gui::Button(
		gui::p2pX(15.f, vm), gui::p2pY(40.f, vm),
		gui::p2pX(13.f, vm), gui:: p2pX(3.5f, vm),
		&this->font, "New Game", gui::clacCharSize(vm, 80), // font size
		sf::Color(0, 0, 0, 250), sf::Color(250, 0, 0, 250), sf::Color(20, 20, 20, 50), // text color
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200)); // background color

	this->buttons["SCORE_STATE"] = new gui::Button(
		gui::p2pX(15.f, vm), gui::p2pY(50.f, vm),
		gui::p2pX(13.f, vm), gui::p2pX(3.5f, vm),
		&this->font, "Leaderboard", gui::clacCharSize(vm, 80),
		sf::Color(0, 0, 0, 250), sf::Color(250, 0, 0, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));

	this->buttons["EDITOR_STATE"] = new gui::Button(
		gui::p2pX(15.f, vm), gui::p2pY(60.f, vm),
		gui::p2pX(13.f, vm), gui::p2pX(3.5f, vm),
		&this->font, "Editor", gui::clacCharSize(vm, 80),
		sf::Color(0, 0, 0, 250), sf::Color(250, 0, 0, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));

	this->buttons["EXIT_STATE"] = new gui::Button(
		gui::p2pX(15.f, vm), gui::p2pY(70.f, vm),
		gui::p2pX(13.f, vm), gui::p2pX(3.5f, vm),
		&this->font, "Quit", gui::clacCharSize(vm, 80),
		sf::Color(0, 0, 0, 250), sf::Color(250, 0, 0, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
}

void MainMenuState::resetGui()
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


// Constructors //
MainMenuState::MainMenuState(StateData* state_data)
	:State(state_data)
{
	this->initVariables();
	this->initMusic();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->resetGui();

	
	
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}


// Functions //

void MainMenuState::updateMusic()
{
	
}

void MainMenuState::updateInput(const float& dt)
{

	// Update player Input //
	
}

void MainMenuState::updateButtons()
{
	for (auto& it : this->buttons)
	{
		// Update all the button in this state //
		it.second->update(this->mousePosWindow);

	}

	// New game //
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->bgMusic.stop();

		this->states->push(new GameState(this->stateData));
		this->endState();
	}

	// Setting //
	if (this->buttons["SCORE_STATE"]->isPressed())
	{
		this->bgMusic.stop();

		this->states->push(new ScoreState(this->stateData));
		this->endState();
	}

	// Editors //
	if (this->buttons["EDITOR_STATE"]->isPressed())
	{
		this->bgMusic.stop();

		this->states->push(new EditorState(this->stateData));
		this->endState();
	}

	// Quit the game //
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->bgMusic.stop();
		
		this->endState();
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);


	this->updateButtons();
	this->updateMusic();
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;


	target->draw(this->background);

	target->draw(this->btnBackground);

	this->renderButtons(*target);

	// Remove later //
	// See Button Position //
	/*sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);*/
}
