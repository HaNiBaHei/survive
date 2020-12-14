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
	this->tagTemplates[DEFAULT_TAG] = new TextTag(this->font, "", 200.f, 200.f, 0.f, -1.f, 
		sf::Color::White, 15, 75.f, true, 200.f, 300.f, 2);
	this->tagTemplates[NEGATIVE_TAG] = new TextTag(this->font, "", 200.f, 200.f, 0.f, 1.f, 
		sf::Color::Red, 20, 75.f, true, 200.f, 300.f, 2);
	this->tagTemplates[EXPRIENCE_TAG] = new TextTag(this->font, "", 200.f, 200.f, 0.f, -1.f, 
		sf::Color::Yellow, 20, 75.f, true, 200.f, 300.f, 2);
	this->tagTemplates[POSITIVE_TAG] = new TextTag(this->font, "", 200.f, 200.f, 0.f, -1.f,
		sf::Color::Green, 20, 75.f, true, 200.f, 300.f, 2);
	
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

void TextTagSystem::addTextTag(const unsigned tag_type, const float pos_x, const float pos_y, const std::string str, const std::string prefix = "", const std::string posefix = "")
{
	std::stringstream ss;
	ss << prefix << " " << str << " " << posefix;
	this->tags.push_back(new TextTag(this->tagTemplates[tag_type], pos_x, pos_y, ss.str()));
}

void TextTagSystem::addTextTag(const unsigned tag_type, const float pos_x, const float pos_y, const int i, const std::string prefix = "", const std::string posefix = "")
{
	std::stringstream ss;
	ss << prefix << " " << i << " " << posefix;
	this->tags.push_back(new TextTag(this->tagTemplates[tag_type], pos_x, pos_y, ss.str()));
}

void TextTagSystem::addTextTag(const unsigned tag_type, const float pos_x, const float pos_y, const float f, const std::string prefix = "", const std::string posefix = "")
{
	std::stringstream ss;
	ss << prefix << " " << f << " " << posefix;
	this->tags.push_back(new TextTag(this->tagTemplates[tag_type], pos_x, pos_y, ss.str()));
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
