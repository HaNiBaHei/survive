#include "stdafx.h"
#include "TileMap.h"

void TileMap::clear()
{
	for (size_t x = 0; x < this->maxSizeWorldGrid.x; x++)
	{
		for (size_t y = 0; y < this->maxSizeWorldGrid.y; y++)
		{
			for (size_t z = 0; z < this->layers; z++)
			{
				delete this->map[x][y][z];
				this->map[x][y][z] = NULL;

			}
			this->map[x][y].clear();
		}
		this->map[x].clear();
	}
	this->map.clear();

	// Debug //
	//std::cout << this->map.size() << "\n";
}

TileMap::TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSizeWorldGrid.x = width;
	this->maxSizeWorldGrid.y = height;
	this->maxSizeWorldF.x = static_cast<float>(width) * gridSize;
	this->maxSizeWorldF.y = static_cast<float>(height) * gridSize;
	this->layers = 1;
	this->textureFile = texture_file;

	
	this->map.resize(this->maxSizeWorldGrid.x, std::vector < std::vector < Tile* > >());
	for (size_t x = 0; x < this->maxSizeWorldGrid.x; x++)
	{
		for (size_t y = 0; y < this->maxSizeWorldGrid.y; y++)
		{
			this->map[x].resize(this->maxSizeWorldGrid.y, std::vector<Tile*>());

			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, NULL);
			}
		}
	}

	if (!this->tileSheet.loadFromFile(texture_file))
		std::cout << "ERROR LOADING TILE TEXTURESHEET::FILENAME:" << texture_file <<"\n";

	this->collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 75));
	this->collisionBox.setOutlineThickness(1.f);
	this->collisionBox.setOutlineColor(sf::Color::Red);
}

TileMap::~TileMap()
{
	this->clear();
}

// Accessors //
const sf::Texture* TileMap::getTileSheet() const
{
	return &this->tileSheet;
}

// Accessors //


// Functions //

void TileMap::saveToFile(const std::string file_name)
{
	/* Save tilemap to text-file 
	Format: 
	Basic:	
			Size x , y
			gridSize
			layers
			texture file

	All tiles:
			gridPos x y layers
			Texture rect x y  type
			
	*/

	std::ofstream out_file;

	out_file.open(file_name);

	if (out_file.is_open())
	{
		out_file << this->maxSizeWorldGrid.x << " " << this->maxSizeWorldGrid.y << "\n"
		<< this->gridSizeU << "\n"
		<< this->layers << "\n"
		<< this->textureFile << "\n";

		for (size_t x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (size_t y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				for (size_t z = 0; z < this->layers; z++)
				{
					if(this->map[x][y][z])
						out_file << x << " " << y << " " << z << " " << this->map[x][y][z]->getAsString() << " ";
				}
			}
		}
	}
	else
	{
		std::cout << "ERROE::TILEMAP::COULD NOT SAVE TO FILE" << file_name << "\n";

	}
	out_file.close();
}

void TileMap::loadFromeFile(const std::string file_name)
{

	std::ifstream in_file;

	in_file.open(file_name);

	if (in_file.is_open())
	{
		sf::Vector2u size;
		unsigned gridSize = 0;
		unsigned layers = 0;
		std::string texture_file = " ";
		unsigned x = 0;
		unsigned y = 0;
		unsigned z = 0;
		unsigned trX = 0; // TextureRect x //
		unsigned trY = 0; // TextureRect y //
		bool collision = false;
		short type = 0;

		// Basic //
		in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;
		

		// Tile //
		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeU = gridSize;
		this->maxSizeWorldGrid.x = size.x;
		this->maxSizeWorldGrid.y = size.y;
		this->layers = layers;
		this->textureFile = texture_file;
		

		this->clear();

		this->map.resize(this->maxSizeWorldGrid.x, std::vector < std::vector < Tile* > >());
		for (size_t x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (size_t y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				this->map[x].resize(this->maxSizeWorldGrid.y, std::vector<Tile*>());

				for (size_t z = 0; z < this->layers; z++)
				{
					this->map[x][y].resize(this->layers, NULL);
				}
			}
		}

		if (!this->tileSheet.loadFromFile(texture_file))
			std::cout << "ERROR LOADING TILE TEXTURESHEET::FILENAME:" << texture_file << "\n";

		// Load all tiles //
		while (in_file >> x >> y >> z >> trX  >> trY >> collision >> type)
		{
			this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileSheet, sf::IntRect(trX, trY, this->gridSizeU, this->gridSizeU) , collision, type);
		}
	}
	else
	{
		std::cout << "ERROE::TILEMAP::COULD NOT LOAD FROM FILE" << file_name << "\n";
	}
	in_file.close();

}


void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect, const bool collision, const short type)
{
	/* Take 2 indicies from the mouse pos in the grid and add tile to that pos if tilemap array allows*/

	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] == NULL)
		{
			// Ok to add
			this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileSheet, texture_rect, collision, type);
			std::cout << "DEBUG: ADDED TILE" << "\n";

		}

	}
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
	/* Take 2 indicies from the mouse pos in the grid and remove tile to that pos if tilemap array allows*/

	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
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

void TileMap::updateCollision(Entity* entity)
{
	// World Bounds //
	if (entity->getPosition().x < 0.f)
	{
		entity->setPosition(0.f, entity->getPosition().y);
		entity->stopVelocityX();
	}
	else if (entity->getPosition().x + entity->getGlobalBounds().width > this->maxSizeWorldF.x)
	{
		entity->setPosition(this->maxSizeWorldF.x - entity->getGlobalBounds().width, entity->getPosition().y);
		entity->stopVelocityX();
	}

	if (entity->getPosition().y < 0.f)
	{
		entity->setPosition(entity->getPosition().x, 0.f);
		entity->stopVelocityY();
	}
	else if (entity->getPosition().y + entity->getGlobalBounds().height > this->maxSizeWorldF.y)
	{
		entity->setPosition(entity->getPosition().x, this->maxSizeWorldF.y - entity->getGlobalBounds().height);
		entity->stopVelocityY();
	}
	// Tiles
	
}


void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget& target, Entity* entity)
{
	for ( auto &x : this->map)
	{
		for (auto &y : x)
		{
			for (auto *z : y)
			{
				if (z != NULL)
				{
					z->render(target);
					if (z->getCollision())
					{
						this->collisionBox.setPosition(z->getPosition());
						target.draw(this->collisionBox);
					}
				}
			}
		}
	}
}



