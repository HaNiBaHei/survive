#ifndef TILEMAP_H
#define TILEMAP_H

#include"Tile.h"

class TileMap
{
private:
	void clear();

	float gridSizeF;
	unsigned gridSizeU;
	unsigned layers;
	sf::Vector2u maxSize;
	std::vector< std::vector< std::vector< Tile* > > > map; // x y z //
	std::string textureFile;
	sf::Texture tileSheet;

protected:

public:
	TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file);
	virtual ~TileMap();

	// Accessors //
	const sf::Texture* getTileSheet() const;

	// Functions //
	void saveToFile(const std::string file_name);
	void loadFromeFile(const std::string file_name);

	void update();
	void render(sf::RenderTarget& target);

	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect, const bool collision, const short type);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);

	
};

#endif