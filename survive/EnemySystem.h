#ifndef ENEMYSYSTEM_H
#define ENEMYSYSTEM_H


#include "EnemySpawnerTile.h"
#include "Fire.h"
#include "Redbat.h"
#include "Boss1.h"
#include "Orc.h"

enum EnemyTyeps {FIRE = 0, RED_BAT, BOSS, ORC};

class EnemySystem
{
private:
	std::map<std::string, sf::Texture>& textures;
	std::vector<Enemy*>& activeEnemies;
	Entity& player;
	// Initializers //

public:
	EnemySystem(std::vector<Enemy*>& activeEnemies,
		std::map<std::string, sf::Texture>& textures, Entity& player);
	virtual ~EnemySystem();
	
	// Accessors //

	// Modifiers //

	// Functions //
	void createEnemy(const short type, const float xPos, const float yPos, EnemySpawnerTile& enemy_spawner_tile);
	void removeEnemy(const int index);

	void update(const float& dt);
	void render(sf::RenderTarget* target);

};

#endif // ! ENEMYSYSTEM_H
