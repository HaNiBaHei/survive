#include "stdafx.h"
#include "Gui.h"

const float gui::p2pX(const float perc, const sf::VideoMode& vm)
{
	/*
	* Converts a percentage values to pixels to relative to the current resolution in x-axis
	*
	* @parm				float perc						The percentage values
	* @parm				sf::VideoMode& vm				The current videomode of the window (resolution)
	*
	* @return			float							The calculated pixel values
	*
	*/

	return std::floor(static_cast<float>(vm.width) * (perc / 100.f));
}

const float gui::p2pY(const float perc, const sf::VideoMode& vm)
{
	/*
	* Converts a percentage values to pixels to relative to the current resolution in y-axis
	*
	* @parm				float perc						The percentage values
	* @parm				sf::VideoMode& vm				The current videomode of the window (resolution)
	*
	* @return			float							The calculated pixel values
	*
	*/

	return std::floor(static_cast<float>(vm.height) * (perc / 100.f));
}

const unsigned gui::clacCharSize(const sf::VideoMode& vm, const unsigned modifier)
{
	/*
	* Calculates the character size for text using the current resolution and a constant
	*
	* @parm				sf::VideoMode& vm				The current videomode of the window (resolution)
	* @parm				unsigned modifier				Used to custom the character size
	* 
	* @return			unsigned						The calculated character size values
	*
	*/
	return static_cast<unsigned>(vm.width + vm.height) / modifier;
}

gui::Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_Color, sf::Color hover_Color, sf::Color active_Color,
	sf::Color outline_idle_Color , sf::Color outline_hover_Color , sf::Color outline_active_Color,
	short unsigned id)
{
	this->buttonState = BTN_IDLE;
	this->id = id;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idle_Color);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outline_idle_Color);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + 10.f
	);

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->idleColor = idle_Color;
	this->hoverColor = hover_Color;
	this->activeColor = active_Color;

	this->outlineIdleColor = outline_idle_Color;
	this->outlineHoverColor = outline_hover_Color;
	this->outlineActiveColor = outline_active_Color;
}

gui::Button::~Button()
{

}

// Accessory //

const bool gui::Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;

	return false;
}

const std::string gui::Button::getText() const
{
	return this->text.getString();
}

const short unsigned& gui::Button::getId() const
{
	return this->id;
}

// Modifier //

void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}

void gui::Button::setId(const short unsigned id)
{
	this->id = id;
}

// Functions //

void gui::Button::update(const sf::Vector2i& mousePosWindow)
{
	// Update the bool for hover and pressed //

	// Idle //
	this->buttonState = BTN_IDLE;

	// Hover //
	if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
	{
		this->buttonState = BTN_HOVER;

		// Active //
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		this->shape.setOutlineColor(this->outlineIdleColor);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		this->shape.setOutlineColor(this->outlineHoverColor);
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		this->shape.setOutlineColor(this->outlineActiveColor);
		break;

	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		this->shape.setOutlineColor(sf::Color::Green);
		break;
	}
}

void gui::Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}

// Dropdownlist //

gui::DropDownList::DropDownList(float x, float y, float width, float height, 
	sf::Font& font, std::string list[], 
	unsigned nrOfElements, unsigned default_index)
	:font(font), showList(false), KeytimeMax(1.f), Keytime(0.f)
{
	//unsigned nrOfElements = sizeof(list) / sizeof(std::string);

	this->activeElement = new gui::Button(
		x, y, width, height,
		&this->font, list[default_index], 16, // font size
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50), // text color
		sf::Color(0, 0, 0, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),  // background color
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 200)
	);


	for (unsigned i = 0; i < nrOfElements; i++)
	{
		this->list.push_back(
			new gui::Button(
				x, y + ((i+1) * height), width, height,
				&this->font, list[i], 16, // font size
				sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50), // text color
				sf::Color(0, 0, 0, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200), // background color
				sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 200),
				i
			)
		);
	}
	
}

gui::DropDownList::~DropDownList()
{
	delete this->activeElement;
	for (size_t i = 0; i < this->list.size(); i++)
	{
		delete this->list[i];

	}
}


 
// Accessor //

const unsigned short& gui::DropDownList::getActiveElementId() const
{
	return this->activeElement->getId();
}

const bool gui::DropDownList::getKeytime()
{
	if (this->Keytime >= this->KeytimeMax)
	{
		this->Keytime = 0.f;
		return true;
	}

	return false;
}

// Functions //

void gui::DropDownList::updateKeytime(const float& dt)
{
	if (this->Keytime < this->KeytimeMax)
		this->Keytime += 10.f * dt;
}

void gui::DropDownList::update(const sf::Vector2i& mousePosWindow, const float& dt)
{
	this->updateKeytime(dt);

	this->activeElement->update(mousePosWindow);

	if (this->activeElement->isPressed() && this->getKeytime())
	{
		if (this->showList)
			this->showList = false;
		else
			this->showList = true;
	}

	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->update(mousePosWindow);

			if (i->isPressed() && this->getKeytime())
			{
				this->showList = false;
				this->activeElement->setText(i->getText());
				this->activeElement->setId(i->getId());
			}
		}
	}
}

void gui::DropDownList::render(sf::RenderTarget& target)
{
	this->activeElement->render(target);

	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->render(target);
		}
	}
}

// Texture selector //


gui::TextureSelector::TextureSelector(float x, float y, float width, float height, 
	float gridSize, const sf::Texture* texture_sheet, sf::Font& font, std::string text)
	: KeytimeMax(1.f), Keytime(0.f)
{
	this->gridSize = gridSize;
	this->active = false;
	this->hidden = false;
	float offset = gridSize;

	this->bounds.setSize(sf::Vector2f(width, height));
	this->bounds.setPosition(x + offset, y);
	this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
	this->bounds.setOutlineThickness(1.f);
	this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

	this->sheet.setTexture(*texture_sheet);
	this->sheet.setPosition(x + offset, y);

	if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0, static_cast<int>(this->bounds.getGlobalBounds().width), static_cast<int>(this->sheet.getGlobalBounds().height)));
	}
	if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0, static_cast<int>(this->sheet.getGlobalBounds().width), static_cast<int>(this->bounds.getGlobalBounds().height)));
	}

	this->selector.setPosition(x + offset, y);
	this->selector.setSize(sf::Vector2f(gridSize, gridSize));
	this->selector.setFillColor(sf::Color::Transparent);
	this->selector.setOutlineThickness(1.f);
	this->selector.setOutlineColor(sf::Color::Red);

	this->textureRect.width = static_cast<int>(gridSize);
	this->textureRect.height = static_cast<int>(gridSize);

	this->hide_btn = new gui::Button(x, y, 50.f, 50.f,
		&font, text, 30, // font size
		sf::Color(255, 255, 255, 250), sf::Color(250, 0, 0, 250), sf::Color(70, 70, 70, 50), // text color
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)); // background color;
}

gui::TextureSelector::~TextureSelector()
{
	delete this->hide_btn;
}

// Accessors //
const bool& gui::TextureSelector::getActive() const
{
	return this->active;
}

const sf::IntRect& gui::TextureSelector::getTextureRect() const
{
	return this->textureRect;
}

const bool gui::TextureSelector::getKeytime()
{
	if (this->Keytime >= this->KeytimeMax)
	{
		this->Keytime = 0.f;
		return true;
	}

	return false;
}

// functions //
void gui::TextureSelector::updateKeytime(const float& dt)
{
	if (this->Keytime < this->KeytimeMax)
		this->Keytime += 10.f * dt;
}

void gui::TextureSelector::update(const sf::Vector2i& mousePosWindow, const float& dt)
{
	this->updateKeytime(dt);
	this->hide_btn->update(mousePosWindow);

	if (this->hide_btn->isPressed() && this->getKeytime())
	{
		if (this->hidden)
			this->hidden = false;
		else
			this->hidden = true;
	}

	if (!this->hidden)
	{
		this->active = false;

		if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
		{
			this->active = true;

		
			this->mousePosGrid.x = (mousePosWindow.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->gridSize);
			this->mousePosGrid.y = (mousePosWindow.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->gridSize);
			this->selector.setPosition(
				this->bounds.getPosition().x + this->mousePosGrid.x * this->gridSize,
				this->bounds.getPosition().y + this->mousePosGrid.y * this->gridSize
			);

			// Update texture Rect //
			this->textureRect.left = static_cast<int>(this->selector.getPosition().x - this->bounds.getPosition().x);
			this->textureRect.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);
		}
	}
}

void gui::TextureSelector::render(sf::RenderTarget& target)
{
	if (!this->hidden)
	{
		target.draw(this->bounds);
		target.draw(this->sheet);

		if (this->active)
			target.draw(this->selector);
	}
	this->hide_btn->render(target);

}

// ProgressBar // ================================================================================
gui::ProgressBar::ProgressBar(float _x, float _y, float _width, float _height,
	sf::Color inner_color, unsigned character_size,
	sf::VideoMode& vm, sf::Font* font)
{
	float width = gui::p2pX(_width, vm);
	float height = gui::p2pY(_height, vm);
	float x = gui::p2pX(_x, vm);
	float y = gui::p2pY(_y, vm);

	this->maxWidth = width;

	this->back.setSize(sf::Vector2f(width, height));
	this->back.setFillColor(sf::Color(50, 50, 50, 200));
	this->back.setPosition(x, y);

	this->inner.setSize(sf::Vector2f(width, height));
	this->inner.setFillColor(inner_color);
	this->inner.setPosition(this->back.getPosition());

	if (font)
	{
		this->text.setFont(*font);
		this->text.setCharacterSize(gui::clacCharSize(vm, character_size));
		this->text.setPosition(
			this->inner.getPosition().x + gui::p2pX(0.53f, vm),
			this->inner.getPosition().y + gui::p2pY(0.5f, vm)
		);
	}
}

gui::ProgressBar::~ProgressBar()
{

}

//Functions
void gui::ProgressBar::update(const int current_value, const int max_value)
{
	float percent = static_cast<float>(current_value) / static_cast<float>(max_value);

	this->inner.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(max_value * percent)),
			this->inner.getSize().y
		)
	);

	this->barString = std::to_string(current_value) + " / " + std::to_string(max_value);
	this->text.setString(this->barString);
}

void gui::ProgressBar::render(sf::RenderTarget& target)
{
	target.draw(this->back);
	target.draw(this->inner);
	target.draw(this->text);
}