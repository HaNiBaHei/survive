#ifndef TEXTTAGSYSTEM_H
#define TEXTTAGSYSTEM_H

enum TAGTYPES { DEFAULT_TAG, NEGATIVE_TAG, POSITIVE_TAG, EXPRIENCE_TAG, ENVIRONMENTAL_TAG
};

class TextTagSystem
{
private:
	class TextTag
	{
	private:
		sf::Text text;
		float dirY;
		float dirX;
		float lifetime;
		float speed;

	public:
		TextTag(sf::Font& font, std::string text,
			float pos_x, float pos_y,
			float dir_x, float dir_y,
			sf::Color color,
			unsigned char_size,
			float lifetime, float speed)
		{
			this->text.setFont(font);
			this->text.setPosition(pos_x, pos_y);
			this->text.setFillColor(color);
			this->text.setCharacterSize(char_size);
			this->text.setString(text);

			this->dirX = dir_x;
			this->dirY = dir_y;
			this->lifetime = lifetime;
			this->speed = speed;
		}

		~TextTag()
		{

		}

		// Accessors //
		inline const bool canBeRemove() const { return this->lifetime <= 0.f; }


		// Functions //
		void update(const float& dt) 
		{
			if (this->lifetime > 0.f)
			{
				// Update lifetime //
				this->lifetime -= 100.f * dt;

				// Move the tag //
				this->text.move(this->dirX * this->speed * dt, this->dirY * this->speed * dt);


			}
		}
		void render(sf::RenderTarget* target)
		{
			target->draw(this->text);
		}
	};

	sf::Font font;
	std::map<unsigned, TextTag*> tagTemplates;
	std::vector<TextTag*> tags;

	// Private Functions //
	void initVariables();
	void initTagTemplates();
	void initFont(std::string font_file);

public:
	TextTagSystem(std::string font_file);
	virtual ~TextTagSystem();

	// Functions //
	void addTextTag(unsigned text_tag);
	void removeTextTag();

	void update(const float& dt);
	void render(sf::RenderTarget* target);
};

#endif // !TEXTTAGSYSTEM_H
