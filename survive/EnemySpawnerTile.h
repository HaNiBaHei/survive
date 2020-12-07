#ifndef ENEMYSPAWNERTILE_H
#define ENEMYSPAWNERTILE_H

#include "Tile.h"

class Tile;

class EnemySpawnerTile
	: public Tile
{
private:
	// Variables //
	
	int enemyType;
	int enemyAmount;
	sf::Clock enemySpawnTimer;
	sf::Int32 enemyTimeToSpawn;
	float enemyMaxDistance;
	bool spawned;

	// Spawn Timer //


public:
	EnemySpawnerTile(int grid_x, int grid_y, float gridSizeF,
		const sf::Texture& texture, const sf::IntRect& texture_rect,
		int enemy_type,int enemy_amount, sf::Int32 enemy_time_to_spawn, float enemy_max_distance);
	virtual ~EnemySpawnerTile();

	// Accessors //
	virtual const std::string getAsString() const;
	const bool& getSpawned() const;


	// Modifiers //
	void setSpawned(const bool spawned);

	const bool canSpawn() const;

	// Functions //

	void update();
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f player_position = sf::Vector2f());
};

#endif // !ENEMYSPAWNERTILE_H
