#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

class EnemySpawner
{
private:
	// Variables //
	sf::RectangleShape shape;
	
	sf::Vector2i gridPositions;
	int type;
	int amount;
	int timeToSpawn;
	float maxDistance;


public:
	EnemySpawner(sf::Vector2i grid_position, float grid_size, int type, int amount, int time_to_spawn, float max_distance);
	virtual ~EnemySpawner();

	// Accessors //

	// Modifiers //

	// Functions //

	void update(const float &dt);
	void render(sf::RenderTarget& target);
};

#endif // !ENEMYSPAWNER_H
