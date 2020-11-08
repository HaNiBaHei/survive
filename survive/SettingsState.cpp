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
	this->buttons["BACK"] = new gui::Button(960.f, 840.f, 150.f, 50.f,
		&this->font, "Back", 50,
		sf::Color(0, 0, 0, 250), sf::Color(250, 0, 0, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["APPLY"] = new gui::Button(960.f, 640.f, 150.f, 50.f,
		&this->font, "Apply", 50,
		sf::Color(0, 0, 0, 250), sf::Color(250, 0, 0, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	std::vector<std::string> modes_str;
	for (auto& i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}
	this->dropdownList["RESOLUTION"] = new gui::DropDownList(960, 250, 200, 50, font, modes_str.data(), modes_str.size());
}

void SettingsState::initText()
{
	this->optionsText.setFont(this->font);

	this->optionsText.setPosition(sf::Vector2f(700.f, 250.f));

	this->optionsText.setCharacterSize(30);
	this->optionsText.setFillColor(sf::Color(0, 0, 0, 255));


	this->optionsText.setString(
		"Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing \n\n"
	);
}


SettingsState::SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
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
		it.second->update(this->mousePosView);
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
		this->window->create(this->modes[this->dropdownList["RESOLUTION"]->getActiveElementId()], "test", sf::Style::Default);
	}

	// DropdownList // 
	for (auto& it : this->dropdownList)
	{
		// Update all the button in this state //
		it.second->update(this->mousePosView, dt);
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