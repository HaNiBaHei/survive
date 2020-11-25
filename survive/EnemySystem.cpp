#include "stdafx.h"
#include "EnemySystem.h"

EnemySystem::EnemySystem(std::vector<Enemy*>& activeEnemies, std::map<std::string, sf::Texture>& textures)
	:textures(textures), activeEnemies(activeEnemies)
{
	this->textures = textures;
	this->activeEnemies = activeEnemies;
}

EnemySystem::~EnemySystem()
{

}
// Functions //
void EnemySystem::createEnemy(const short type, const float xPos, const float yPos)
{
	switch (type)
	{
	case EnemyTyeps::FIRE:
		this->activeEnemies.push_back(new Fire(xPos, yPos, this->textures["FIRE_BALL"]));
		break;
	default:
		std::cout << "ERROR::ENEMYSYSTEM::CREATEENEMY::TYPE DOSE NOT EXIST" << "\n";
		break;
	}
}

void EnemySystem::update(const float& dt)
{

}

void EnemySystem::render(sf::RenderTarget* target)
{

}
