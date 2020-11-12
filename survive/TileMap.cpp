#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(float gridSize, unsigned width, unsigned height)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->layers = 1;

	
	this->map.resize(this->maxSize.x, std::vector < std::vector < Tile* > >());
	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			this->map[x].resize(this->maxSize.y, std::vector<Tile*>());

			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, NULL);
			}
		}
	}

	if (!this->tileSheet.loadFromFile("Resources/images/Tile/tilesheet3.png"))
		std::cout << "ERROR LOADING TILE TEXTURE" << "\n";
}

TileMap::~TileMap()
{
	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			for (size_t z = 0; z < this->layers; z++)
			{
				delete this->map[x][y][z];
			}
		}
	}
}

// Accessors //
const sf::Texture* TileMap::getTileSheet() const
{
	return &this->tileSheet;
}

// Accessors //


// Functions //

void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget& target)
{
	for ( auto &x : this->map)
	{
		for (auto &y : x)
		{
			for (auto *z : y)
			{
				if(z != NULL)
					z->render(target);
			}
		}
	}
}

void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect)
{
	/* Take 2 indicies from the mouse pos in the grid and add tile to that pos if tilemap array allows*/

	if (x < this->maxSize.x && x >= 0 && 
		y < this->maxSize.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] == NULL)  
		{
			// Ok to add
			this->map[x][y][z] = new Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF, this->tileSheet, texture_rect);
			std::cout << "DEBUG: ADDED TILE" << "\n";

		}

	}
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
	/* Take 2 indicies from the mouse pos in the grid and remove tile to that pos if tilemap array allows*/

	if (x < this->maxSize.x && x >= 0 &&
		y < this->maxSize.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] != NULL)
		{
			// Remove
			delete this->map[x][y][z];
			this->map[x][y][z] = NULL;
			std::cout << "DEBUG: REMOVED TILE" << "\n";

		}

	}
}
