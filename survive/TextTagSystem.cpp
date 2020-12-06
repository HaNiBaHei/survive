#include "stdafx.h"
#include "TextTagSystem.h"
// Private Functions //
void TextTagSystem::initVariables()
{

}

void TextTagSystem::initFont(std::string font_file)
{
	if (!this->font.loadFromFile(font_file))
		std::cout << "ERROR::TEXTTAGSYSTEM::COUNSTRUCTOR::Failed to load font " << font_file << "\n";
}

void TextTagSystem::initTagTemplates()
{
	this->tagTemplates[DEFAULT_TAG] = new TextTag(this->font, "Yeah Boy!", 200.f, 200.f, 0.f, -1.f, sf::Color::Red, 20, 100.f, 100.f);
}

// Constructors //
TextTagSystem::TextTagSystem(std::string font_file)
{
	this->initFont(font_file);
	this->initVariables();
	this->initTagTemplates();
}

TextTagSystem::~TextTagSystem()
{
	// Clean up tags //
	for (auto* tag : this->tags)
	{
		delete tag;
	}

	// Clean up templates //
	for (auto& tag : this->tagTemplates)
	{
		delete tag.second;
	}

}
// Functions //

void TextTagSystem::addTextTag(const unsigned text_tag, const float pos_x, const float pos_y, const std::string str)
{
	this->tags.push_back(new TextTag(this->tagTemplates[DEFAULT_TAG], pos_x, pos_y, str));
}

void TextTagSystem::addTextTag(const unsigned text_tag, const float pos_x, const float pos_y, const int i)
{
	std::stringstream ss;
	ss << i;
	this->tags.push_back(new TextTag(this->tagTemplates[DEFAULT_TAG], pos_x, pos_y, ss.str()));
}

void TextTagSystem::addTextTag(const unsigned text_tag, const float pos_x, const float pos_y, const float f)
{
	std::stringstream ss;
	ss << f;
	this->tags.push_back(new TextTag(this->tagTemplates[DEFAULT_TAG], pos_x, pos_y, ss.str()));
}

void TextTagSystem::update(const float& dt)
{
	for (size_t i = 0; i < this->tags.size(); ++i)
	{
		this->tags[i]->update(dt);

		if (this->tags[i]->isExpired())
		{
			delete this->tags[i];
			this->tags.erase(this->tags.begin() + i);
		}
	}
}

void TextTagSystem::render(sf::RenderTarget& target)
{
	for (auto& tag : this->tags)
	{
		tag->render(target);
	}
}
