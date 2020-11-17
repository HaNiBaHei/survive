#ifndef TILEMAP_H
#define TILEMAP_H

#include"Tile.h"
#include"Entity.h"

class Tile;
class Entity;

class TileMap
{
private:
	void clear();

	float gridSizeF;
	int gridSizeI;
	int layers;
	sf::Vector2i maxSizeWorldGrid;
	sf::Vector2f maxSizeWorldF;
	std::vector< std::vector< std::vector< Tile* > > > map; // x y z //
	std::string textureFile;
	sf::Texture tileSheet;
	sf::RectangleShape collisionBox;

	// Culling //
	int fromX;
	int toX;
	int fromY;
	int toY;
	int layer;

protected:

public:
	TileMap(float gridSize, int width, int height, std::string texture_file);
	virtual ~TileMap();

	// Accessors //
	const sf::Texture* getTileSheet() const;

	// Functions //
	void addTile(const int x, const int y, const int z, const sf::IntRect& texture_rect, const bool collision, const short type);
	void removeTile(const int x, const int y, const int z);
	void saveToFile(const std::string file_name);
	void loadFromeFile(const std::string file_name);

	void updateCollision(Entity* entity, const float& dt);

	void update();
	void render(sf::RenderTarget& target, Entity* entity = NULL);

	

	
};

#endif