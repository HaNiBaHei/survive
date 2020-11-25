#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

#include "Tile.h"

class Tile;

class EnemySpawner
	: public Tile
{
private:
	// Variables //
	
	int enemyType;
	int enemyAmount;
	int enemyTimeToSpawn;
	float enemyMaxDistance;


public:
	EnemySpawner(int grid_x, int grid_y, float gridSizeF, 
		const sf::Texture& texture, const sf::IntRect& texture_rect,
		int enemy_type,int enemy_amount, int enemy_time_to_spawn, float enemy_max_distance);
	virtual ~EnemySpawner();

	// Accessors //

	// Modifiers //

	// Functions //
	virtual const std::string getAsString() const;

	void update();
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f player_position = sf::Vector2f());
};

#endif // !ENEMYSPAWNER_H
