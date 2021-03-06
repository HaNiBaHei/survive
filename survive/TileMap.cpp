#include "stdafx.h"
#include "TileMap.h"

void TileMap::clear()
{
	if (!this->map.empty())
	{
		for (int x = 0; x < this->map.size(); x++)
		{
			for (int y = 0; y < this->map[x].size(); y++)
			{
				for (int z = 0; z < this->map[x][y].size(); z++)
				{
					for (size_t k = 0; k < this->map[x][y][z].size(); k++)
					{
						delete this->map[x][y][z][k];
						this->map[x][y][z][k] = NULL;

					}
					this->map[x][y][z].clear();
				}
				this->map[x][y].clear();
			}
			this->map[x].clear();
		}
		this->map.clear();
	}

	// Debug //
	//std::cout << this->map.size() << "\n";
}

TileMap::TileMap(float gridSize, int width, int height, std::string texture_file)
{
	this->gridSizeF = gridSize;
	this->gridSizeI = static_cast<int>(this->gridSizeF);
	this->maxSizeWorldGrid.x = width;
	this->maxSizeWorldGrid.y = height;
	this->maxSizeWorldF.x = static_cast<float>(width) * gridSize;
	this->maxSizeWorldF.y = static_cast<float>(height) * gridSize;
	this->layers = 1;
	this->textureFile = texture_file;

	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;
	
	this->map.resize(this->maxSizeWorldGrid.x, std::vector< std::vector < std::vector < Tile* > > >());
	for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
	{
		for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
		{
			this->map[x].resize(this->maxSizeWorldGrid.y, std::vector< std::vector<Tile*> >());

			for (int z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, std::vector<Tile*>());
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

TileMap::TileMap(const std::string file_name)
{
	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;

	this->loadFromeFile(file_name);

	this->collisionBox.setSize(sf::Vector2f(this->gridSizeF, this->gridSizeF));
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 75));
	this->collisionBox.setOutlineThickness(1.f);
	this->collisionBox.setOutlineColor(sf::Color::Red);
}

TileMap::~TileMap()
{
	this->clear();
}

const bool TileMap::tileEmpty(const int x, const int y, const int z) const
{
	if (x >= 0 && x < this->maxSizeWorldGrid.x &&
		y >= 0 && y < this->maxSizeWorldGrid.y &&
		z >= 0 && z < this->layers)
	{
		return this->map[x][y][z].empty();
	}

	std::cout << "ERROR::TILEMAP::TILEEMPTY::TRYING TO ACCESS OUT OF BOUNDS TILE" << "\n";
	return false;
}

// Accessors //
const sf::Texture* TileMap::getTileSheet() const
{
	return &this->tileSheet;
}

const int TileMap::getLayerSize(const int x, const int y, const int layer) const
{
	if (x >= 0 && x < static_cast<int>(this->map.size()))
	{
		if (y >= 0 && y < static_cast<int>(this->map[x].size()))
		{
			if (layer >= 0 && layer < static_cast<int>(this->map[x][y].size()))
			{
				return this->map[x][y][layer].size();
			}
		}
	}

	return -1;
}

const sf::Vector2i& TileMap::getMaxSizeGrid() const
{
	return this->maxSizeWorldGrid;
}

const sf::Vector2f& TileMap::getMaxSizeF() const
{
	return this->maxSizeWorldF;
}


// Functions //
void TileMap::addTile(const int x, const int y, const int z, const sf::IntRect& texture_rect, const bool collision, const short& type)
{
	/* Take 2 indicies from the mouse pos in the grid and add tile to that pos if tilemap array allows*/

	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
			// Ok to add //
		this->map[x][y][z].push_back(new RegularTile(type, x, y, this->gridSizeF, this->tileSheet, texture_rect, collision));
		
		//std::cout << "DEBUG: ADDED TILE" << "\n";
	}
}

void TileMap::addTile(const int x, const int y, const int z, const sf::IntRect& texture_rect,
	const int enemy_type, const int enemy_amout, const int enemy_tts, const int enemy_md)
{
	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
			this->map[x][y][z].push_back(new EnemySpawnerTile(x, y, this->gridSizeF, this->tileSheet, texture_rect,
				enemy_type, enemy_amout, enemy_tts, enemy_md));
	}
}

void TileMap::removeTile(const int x, const int y, const int z, const int type)
{
	/* Take 2 indicies from the mouse pos in the grid and remove tile to that pos if tilemap array allows*/

	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		if (!this->map[x][y][z].empty())
		{
			// Ok to Remove
			if (type >= 0)
			{
				if (this->map[x][y][z].back()->getType() == type)
				{
					delete this->map[x][y][z][this->map[x][y][z].size() - 1];
					this->map[x][y][z].pop_back();
					//std::cout << "DEBUG: REMOVED TILE" << "\n";
				}
			}
			else
			{
				delete this->map[x][y][z][this->map[x][y][z].size() - 1];
				this->map[x][y][z].pop_back();
				//std::cout << "DEBUG: REMOVED TILE" << "\n";
			}
			

		}

	}
}

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
			type
			gridPos x y layers
			Texture rect x y  
			collision
			tile_specific
	*/

	std::ofstream out_file;

	out_file.open(file_name);

	if (out_file.is_open())
	{
		out_file << this->maxSizeWorldGrid.x << " " << this->maxSizeWorldGrid.y << "\n"
		<< this->gridSizeI << "\n"
		<< this->layers << "\n"
		<< this->textureFile << "\n";

		for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				for (int z = 0; z < this->layers; z++)
				{
					if (!this->map[x][y][z].empty())
					{
						for (size_t k = 0; k < this->map[x][y][z].size(); k++)
						{
							out_file << x << " " << y << " " << z << " " <<
								this->map[x][y][z][k]->getAsString()
								<< " ";
						}
					}
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
		sf::Vector2i size;
		int gridSize = 0;
		int layers = 0;
		std::string texture_file = " ";
		int x = 0;
		int y = 0;
		int z = 0;
		int trX = 0; // TextureRect x //
		int trY = 0; // TextureRect y //
		bool collision = false;
		short type = 0;

		// Basic //
		in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;
		

		// Tile //
		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeI = gridSize;
		this->maxSizeWorldGrid.x = size.x;
		this->maxSizeWorldGrid.y = size.y;
		this->maxSizeWorldF.x = static_cast<float>(size.x * gridSize);
		this->maxSizeWorldF.y = static_cast<float>(size.y * gridSize);
		this->layers = layers;
		this->textureFile = texture_file;
		

		this->clear();

		this->map.resize(this->maxSizeWorldGrid.x, std::vector< std::vector< std::vector<Tile* > > >());
		for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				this->map[x].resize(this->maxSizeWorldGrid.y, std::vector< std::vector<Tile*> >());

				for (int z = 0; z < this->layers; z++)
				{
					this->map[x][y].resize(this->layers, std::vector<Tile*>());
				}
			}
		}

		if (!this->tileSheet.loadFromFile(texture_file))
			std::cout << "ERROR LOADING TILE TEXTURESHEET::FILENAME:" << texture_file << "\n";

		// Load all tiles //
		while (in_file >> x >> y >> z >> type)
		{
			if (type == TileTypes::ENEMYSPAWNER)
			{
				// amount, time, max dis //
				int enemy_type = 0;
				int enemy_am = 0;
				int	enemy_tts = 0;
				int	enemy_md = 0;

				in_file >> trX >> trY >> enemy_type >> enemy_am >> enemy_tts >> enemy_md;

				this->map[x][y][z].push_back(
					new EnemySpawnerTile(
						x, y,
						this->gridSizeF,
						this->tileSheet,
						sf::IntRect(trX, trY, this->gridSizeI, this->gridSizeI),
						enemy_type,
						enemy_am,
						enemy_tts,
						enemy_md
					)
				);
			}
			else
			{
				in_file >> trX >> trY >> collision;

				this->map[x][y][z].push_back(
					new RegularTile(
						type,
						x, y,
						this->gridSizeF,
						this->tileSheet,
						sf::IntRect(trX, trY, this->gridSizeI, this->gridSizeI),
						collision
					)
				);
			}
		}
	}
	else
	{
		std::cout << "ERROE::TILEMAP::COULD NOT LOAD FROM FILE" << file_name << "\n";
	}

	in_file.close();

}

const bool TileMap::checkType(const int x, const int y, const int z, const int type) const
{

	return this->map[x][y][this->layer].back()->getType() == type;
}

void TileMap::updateWorldBoundsCollision(Entity* entity, const float& dt)
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
}

void TileMap::updateTileCollision(Entity* entity, const float& dt)
{
	// Tiles
	this->layer = 0;

	this->fromX = entity->getGridPosition(this->gridSizeI).x - 4;
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSizeWorldGrid.x)
		this->fromX = this->maxSizeWorldGrid.x;

	this->toX = entity->getGridPosition(this->gridSizeI).x + 6;
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSizeWorldGrid.x)
		this->toX = this->maxSizeWorldGrid.x;

	this->fromY = entity->getGridPosition(this->gridSizeI).y - 4;
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSizeWorldGrid.y)
		this->fromY = this->maxSizeWorldGrid.y;

	this->toY = entity->getGridPosition(this->gridSizeI).y + 6;
	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->maxSizeWorldGrid.y)
		this->toY = this->maxSizeWorldGrid.y;


	for (int x = this->fromX; x < this->toX; x++)
	{
		for (int y = this->fromY; y < this->toY; y++)
		{
			for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++)
			{
			

				sf::FloatRect playerBounds = entity->getGlobalBounds();
				sf::FloatRect wallBounds = this->map[x][y][this->layer][k]->getGlobalBounds();
				sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);

				if (this->map[x][y][this->layer][k]->getCollision() &&
					this->map[x][y][this->layer][k]->intersects(nextPositionBounds)
					)
				{
					// Bottom collision //
					if (playerBounds.top < wallBounds.top
						&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left
						)
					{
						entity->stopVelocityY();
						entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
					}

					// Top collision //
					else if (playerBounds.top > wallBounds.top
						&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left
						)
					{
						entity->stopVelocityY();
						entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
					}

					// Right collison //
					if (playerBounds.left < wallBounds.left
						&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top
						)
					{
						entity->stopVelocityX();
						entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
					}

					// Left collision //
					else if (playerBounds.left > wallBounds.left
						&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top
						)
					{
						entity->stopVelocityX();
						entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);

					}
				}
			}
		}
	}
}

void TileMap::updateTiles(Entity* entity, const float& dt, EnemySystem& enemySystem)
{
	// Tiles
	this->layer = 0;

	this->fromX = entity->getGridPosition(this->gridSizeI).x - 14;
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSizeWorldGrid.x)
		this->fromX = this->maxSizeWorldGrid.x;

	this->toX = entity->getGridPosition(this->gridSizeI).x + 14;
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSizeWorldGrid.x)
		this->toX = this->maxSizeWorldGrid.x;

	this->fromY = entity->getGridPosition(this->gridSizeI).y - 14;
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSizeWorldGrid.y)
		this->fromY = this->maxSizeWorldGrid.y;

	this->toY = entity->getGridPosition(this->gridSizeI).y + 14;
	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->maxSizeWorldGrid.y)
		this->toY = this->maxSizeWorldGrid.y;


	for (int x = this->fromX; x < this->toX; x++)
	{
		for (int y = this->fromY; y < this->toY; y++)
		{
			for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++)
			{
				// Update the tile //
				this->map[x][y][this->layer][k]->update();

				// Update tile type specific //
				if (this->map[x][y][this->layer][k]->getType() == TileTypes::ENEMYSPAWNER)
				{
					EnemySpawnerTile* es = dynamic_cast<EnemySpawnerTile*>(this->map[x][y][this->layer][k]);
					if (es)
					{
						if (es->getSpawnTimer() && es->getEnemyCounter() < es->getEnemyAmount())
						{
							enemySystem.createEnemy(es->getEnemyType(), x * this->gridSizeF, y * this->gridSizeF, *es);
						}
					}
				}
			}
		}
	}
}

void TileMap::update(Entity* entity, const float& dt)
{
	

	
}

void TileMap::render(sf::RenderTarget& target,
	const sf::Vector2i& gridPosition,
	sf::Shader* shader,
	const sf::Vector2f playerPosition,
	const bool show_collision)
{
		this->layer = 0;

		this->fromX = gridPosition.x - 14;
		if (this->fromX < 0)
			this->fromX = 0;
		else if (this->fromX > this->maxSizeWorldGrid.x)
			this->fromX = this->maxSizeWorldGrid.x;

		this->toX = gridPosition.x + 14;
		if (this->toX < 0)
			this->toX = 0;
		else if (this->toX > this->maxSizeWorldGrid.x)
			this->toX = this->maxSizeWorldGrid.x;

		this->fromY = gridPosition.y - 14;
		if (this->fromY < 0)
			this->fromY = 0;
		else if (this->fromY > this->maxSizeWorldGrid.y)
			this->fromY = this->maxSizeWorldGrid.y;

		this->toY = gridPosition.y + 14;
		if (this->toY < 0)
			this->toY = 0;
		else if (this->toY > this->maxSizeWorldGrid.y)
			this->toY = this->maxSizeWorldGrid.y;

		for (int x = this->fromX; x < this->toX; x++)
		{
			for (int y = this->fromY; y < this->toY; y++)
			{
				for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++)
				{
					if (this->map[x][y][this->layer][k]->getType() == TileTypes::BEHIDE)
					{
						this->deferredRenderStack.push(this->map[x][y][this->layer][k]);
					}
					else
					{
						if(shader)
							this->map[x][y][this->layer][k]->render(target, shader, playerPosition);
						else
							this->map[x][y][this->layer][k]->render(target);
					}

					if (show_collision)
					{
						if (this->map[x][y][this->layer][k]->getCollision())
						{
							this->collisionBox.setPosition(this->map[x][y][this->layer][k]->getPosition());
							target.draw(this->collisionBox);
						}

						if (this->map[x][y][this->layer][k]->getType() == TileTypes::ENEMYSPAWNER)
						{
							this->collisionBox.setPosition(this->map[x][y][this->layer][k]->getPosition());
							target.draw(this->collisionBox);
						}
					}

					
				}
			}
		}
	
}

void TileMap::renderDeferred(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f playerPosition)
{
	while (!this->deferredRenderStack.empty())
	{
		if(shader)
			deferredRenderStack.top()->render(target, shader, playerPosition);
		else
			deferredRenderStack.top()->render(target);

		deferredRenderStack.pop();
	}
}



