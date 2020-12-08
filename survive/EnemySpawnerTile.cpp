#include "stdafx.h"
#include "EnemySpawnerTile.h"
// Constructors //
EnemySpawnerTile::EnemySpawnerTile(int grid_x, int grid_y, float gridSizeF,
	const sf::Texture& texture, const sf::IntRect& texture_rect,
	int enemy_type, 
	int enemy_amount, sf::Int32 enemy_time_to_spawn, float enemy_max_distance)
	: Tile(TileTypes::ENEMYSPAWNER, grid_x, grid_y, gridSizeF, texture, texture_rect, false)
{
	this->enemyType = enemy_type;
	this->enemyAmount = enemy_amount;
	this->enemyCounter = 0;
	this->enemySpawnTimer.restart();
	this->enemyTimeToSpawn = enemy_time_to_spawn;
	this->enemyMaxDistance = enemy_max_distance;
	this->spawned = false;
}

EnemySpawnerTile::~EnemySpawnerTile()
{

}
// Accessors //
const bool& EnemySpawnerTile::getSpawned() const
{
	return this->spawned;
}
const int& EnemySpawnerTile::getEnemyAmount() const
{
	return this->enemyAmount;
}
const int& EnemySpawnerTile::getEnemyCounter() const
{
	return this->enemyCounter;
}
void EnemySpawnerTile::setSpawned(const bool spawned)
{
	this->spawned = spawned;
	this->enemySpawnTimer.restart();
}

const bool EnemySpawnerTile::canSpawn() const
{
	if (this->enemySpawnTimer.getElapsedTime().asMilliseconds() >= this->enemyTimeToSpawn)
	{

		return true;
	}
	return false;
}

void EnemySpawnerTile::increaseEnemyCounter()
{
	if (this->enemyCounter > this->enemyAmount)
		this->enemyCounter = this->enemyAmount;
	else
		++this->enemyCounter;
}

void EnemySpawnerTile::decreaseEnemyCounter()
{
	if (this->enemyCounter < 0)
		this->enemyCounter = 0;
	else
		--this->enemyCounter;
}

const std::string EnemySpawnerTile::getAsString() const
{
	std::stringstream ss;

	/*
	* x y z
	* type
	* rect x, rext y
	* enemy_type
	* enemy_amount
	* enemy_time to spawn
	* enemy max distance
	* 
	*/

	ss << this->type << " " << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " "
		<< this->enemyType << " " << this->enemyAmount << " " << this->enemyTimeToSpawn << " " << this->enemyMaxDistance;

	return ss.str();
}


// Functions //

void EnemySpawnerTile::update()
{
	if (this->canSpawn())
		this->spawned = false;
}

void EnemySpawnerTile::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f player_position)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", player_position);

		target.draw(this->shape, shader);
	}
	else
		target.draw(this->shape);
}
