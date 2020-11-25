#include "stdafx.h"
#include "EnemySpawnerTile.h"
// Constructors //
EnemySpawnerTile::EnemySpawnerTile(int grid_x, int grid_y, float gridSizeF,
	const sf::Texture& texture, const sf::IntRect& texture_rect,
	int enemy_type, 
	int enemy_amount, int enemy_time_to_spawn, float enemy_max_distance)
	: Tile(TileTypes::ENEMYSPAWNER, grid_x, grid_y, gridSizeF, texture, texture_rect, false)
{
	this->enemyType = enemy_type;
	this->enemyAmount = enemy_amount;
	this->enemyTimeToSpawn = enemy_time_to_spawn;
	this->enemyMaxDistance = enemy_max_distance;
	this->spawned = false;
}

EnemySpawnerTile::~EnemySpawnerTile()
{

}
// Accessors //
void EnemySpawnerTile::setSpawned(const bool spawned)
{
	this->spawned = spawned;
}
const bool& EnemySpawnerTile::getSpawned() const
{
	return this->spawned;
}
// Functions //

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

void EnemySpawnerTile::update()
{

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
