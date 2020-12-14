#include "stdafx.h"
#include "EnemySystem.h"

EnemySystem::EnemySystem(std::vector<Enemy*>& activeEnemies, std::map<std::string, sf::Texture>& textures, Entity& player)
	:textures(textures), activeEnemies(activeEnemies), player(player)
{
	this->textures = textures;
	this->activeEnemies = activeEnemies;
}

EnemySystem::~EnemySystem()
{

}
// Functions //
void EnemySystem::createEnemy(const short type, const float xPos, const float yPos, EnemySpawnerTile& enemy_spawner_tile)
{
	switch (type)
	{
	case EnemyTyeps::FIRE:
		this->activeEnemies.push_back(new Fire(xPos, yPos, this->textures["FIRE_BALL"], enemy_spawner_tile, this->player));
		enemy_spawner_tile.increaseEnemyCounter();
		break;
	case EnemyTyeps::RED_BAT:
		this->activeEnemies.push_back(new Redbat(xPos, yPos, this->textures["RED_BAT"], enemy_spawner_tile, this->player));
		enemy_spawner_tile.increaseEnemyCounter();
		break;
	case EnemyTyeps::ORC:
		this->activeEnemies.push_back(new Orc(xPos, yPos, this->textures["Orc"], enemy_spawner_tile, this->player));
		enemy_spawner_tile.increaseEnemyCounter();
		break;
	case EnemyTyeps::BOSS:
		this->activeEnemies.push_back(new Boss1(xPos, yPos, this->textures["BOSS"], enemy_spawner_tile, this->player));
		enemy_spawner_tile.increaseEnemyCounter();
		break;
	default:
		std::cout << "ERROR::ENEMYSYSTEM::CREATEENEMY::TYPE DOSE NOT EXIST" << "\n";
		break;
	}
}

void EnemySystem::removeEnemy(const int index)
{
	this->activeEnemies[index]->getEnemySpawnerTile().decreaseEnemyCounter();
	delete this->activeEnemies[index];
	this->activeEnemies.erase(this->activeEnemies.begin() + index);
}

void EnemySystem::update(const float& dt)
{

}

void EnemySystem::render(sf::RenderTarget* target)
{

}
