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
	this->tagTemplates[DEFAULT_TAG] = new TextTag(this->font, "", 0.f, 0.f, 0.f, -1.f, sf::Color::White, 12, 1000.f, 200.f);
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

}
// Functions //

void TextTagSystem::addTextTag(unsigned text_tag)
{

}
void TextTagSystem::removeTextTag()
{

}
void TextTagSystem::update(const float& dt)
{
	for (auto& tag : this->tags)
	{
		tag->update(dt);
	}
}
void TextTagSystem::render(sf::RenderTarget* target)
{
	for (auto& tag : this->tags)
	{
		tag->render(target);
	}
}
