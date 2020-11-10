#ifndef GRAPHICSSETTINGS_H
#define GRAPHICSSETTINGS_H


class GraphicsSettings
{
public:
	GraphicsSettings();
	virtual ~GraphicsSettings();
	
	// Variables //
	std::string title;
	sf::VideoMode resolution;
	bool fullscreen;
	bool verticalSync;
	unsigned frameRateLimit;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> videoModes;

	// Functions //
	void saveToFile(const std::string path);
	void loadFromeFile(const std::string path);
};


#endif // !GRAPHICSSETTINGS_H
