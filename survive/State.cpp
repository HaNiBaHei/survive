#include "stdafx.h"
#include "State.h"

State::State(StateData* state_data)
{
	this->stateData = state_data;
	this->window = state_data->window;
	this->supportedKeys = state_data->supportedKeys;
	this->states = state_data->states;
	this->quit = false;
	this->pause = false;
	this->keytime = 0.f;
	this->keytimeMax = 10.f;
	this->gridSize = state_data->gridSize;
}

State::~State()
{

}

// Accessors //
const bool& State::getQuit() const
{
	return this->quit;
}

const bool State::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}
	return false;
}

// Functions //

const float State::p2pX(const float perc) const
{
	/*
	* Converts a percentage values to pixels to relative to the current resolution in x-axis
	* 
	* @parm				float perc				The percentage values
	* 
	* @return			float					The calculated pixel values
	* 
	*/

	return std::floor(static_cast<float>(this->stateData->gfxSettings->resolution.width) * (perc / 100.f));
}

const float State::p2pY(const float perc) const
{
	/*
	* Converts a percentage values to pixels to relative to the current resolution in y-axis
	*
	* @parm				float perc				The percentage values
	*
	* @return			float					The calculated pixel values
	*
	*/

	return std::floor(static_cast<float>(this->stateData->gfxSettings->resolution.height) * (perc / 100.f));
}

const unsigned State::clacCharSize() const
{
	/*
	* Calculates the character size for text using the current resolution and a constant
	*
	* @return			unsigned					The calculated character size values
	*
	*/
	return static_cast<unsigned>(this->stateData->gfxSettings->resolution.width + this->stateData->gfxSettings->resolution.height) / 80;
}

void State::endState()
{
	this->quit = true;
}

void State::pauseState()
{
	this->pause = true;
}

void State::unpauseState()
{
	this->pause = false;
}

void State::updateMousePositions(sf::View* view )
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);

	if(view)
	this->window->setView(*view);

	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->mousePosGrid = sf::Vector2i(
		static_cast<int>(this->mousePosView.x) / static_cast<int>(this->gridSize),
		static_cast<int>(this->mousePosView.y) / static_cast<int>(this->gridSize)
	);

	this->window->setView(this->window->getDefaultView());
}

void State::updateKeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax)
		this->keytime += 100.f * dt;
}


