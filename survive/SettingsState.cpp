#include "stdafx.h"
#include "SettingsState.h"

// Initializer //
void SettingsState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();

}

void SettingsState::initBackground()
{
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);
	if (!this->backgroundTexture.loadFromFile("Resources/images/Backgrounds/bg1.png"))
	{
		throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);
}

void SettingsState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/times.ttf"))
	{
		throw("ERROR::MAINMENUSTATE:: COULD NOT LOAD FONTS");
	}
}

void SettingsState::initKeybinds()
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

void SettingsState::initGui()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	this->buttons["BACK"] = new gui::Button(
		gui::p2pX(50.f, vm), gui::p2pY(68.51f, vm),
		gui::p2pX(7.81f, vm), gui::p2pY(3.f, vm),
		&this->font, "Back", gui::clacCharSize(vm),
		sf::Color(0, 0, 0, 250), sf::Color(250, 0, 0, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["APPLY"] = new gui::Button(
		gui::p2pX(50.f, vm), gui::p2pY(59.25f, vm),
		gui::p2pX(7.81f, vm), gui::p2pY(3.f, vm),
		&this->font, "Apply", gui::clacCharSize(vm),
		sf::Color(0, 0, 0, 250), sf::Color(250, 0, 0, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	std::vector<std::string> modes_str;
	for (auto& i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}
	this->dropdownList["RESOLUTION"] = new gui::DropDownList(
		gui::p2pX(50.f, vm), gui::p2pY(23.14f, vm),
		gui::p2pX(10.4f, vm), gui::p2pY(4.62f, vm),
		font, modes_str.data(), modes_str.size());
}

void SettingsState::initText()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	this->optionsText.setFont(this->font);

	this->optionsText.setPosition(sf::Vector2f(gui::p2pX(36.45f, vm), gui::p2pY(23.14f, vm)));

	this->optionsText.setCharacterSize(gui::clacCharSize(vm));
	this->optionsText.setFillColor(sf::Color(0, 0, 0, 255));


	this->optionsText.setString(
		"Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing \n\n"
	);
}


SettingsState::SettingsState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->initText();
}

SettingsState::~SettingsState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	auto it2 = this->dropdownList.begin();
	for (it2 = this->dropdownList.begin(); it2 != this->dropdownList.end(); ++it2)
	{
		delete it2->second;
	}
}

// Accessors //

// Functions //
void SettingsState::updateInput(const float& dt)
{

	// Update player Input //

}

void SettingsState::updateGui(const float& dt)
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
		this->endState();
	}

	// Apply the selected settings //
	if (this->buttons["APPLY"]->isPressed())
	{
		// For Test //
		this->stateData->gfxSettings->resolution = this->modes[this->dropdownList["RESOLUTION"]->getActiveElementId()];

		this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Default);
	}

	// DropdownList // 
	for (auto& it : this->dropdownList)
	{
		// Update all the button in this state //
		it.second->update(this->mousePosWindow, dt);
	}

	// DropdownList Functionality // 
}

void SettingsState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateGui(dt);


}

void SettingsState::renderGui(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

	for (auto& it : this->dropdownList)
	{
		it.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderGui(*target);

	target->draw(this->optionsText);

	// Remove later //
	// See Button Position //
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);
}