#include "stdafx.h"
#include "GameState.h"



// Initializer //
void GameState::initDeferredRender()
{
	this->renderTexture.create(
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(sf::IntRect(
		0, 
		0, 
		this->stateData->gfxSettings->resolution.width, 
		this->stateData->gfxSettings->resolution.height)
	);

}

void GameState::initView()
{
	this->view.setSize(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width / 1.5f),
			static_cast<float>(this->stateData->gfxSettings->resolution.height / 1.5f)
		)
	);

	this->view.setCenter(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f,
			static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f
		)
	);
}

void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";
		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}


void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/times.ttf"))
	{
		throw("ERROR::MAINMENUSTATE:: COULD NOT LOAD FONTS");
	}
}

void GameState::initTexture()
{
	// Buttons //




	// Player //
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/images/Sprite/Player/PLAYER_SHEET2.png"))
	{
		std::cout << "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE" << "\n";
	}

	// Enemy //
	if (!this->textures["FIRE_BALL"].loadFromFile("Resources/images/Sprite/Enemy/Fire.png"))
	{
		std::cout << "ERROR::GAME_STATE::COULD_NOT_LOAD_FIRE_TEXTURE" << "\n";
	}

	if (!this->textures["RED_BAT"].loadFromFile("Resources/images/Sprite/Enemy/redBat24.png"))
	{
		std::cout << "ERROR::GAME_STATE::COULD_NOT_LOAD_REDBAT_TEXTURE" << "\n";
	}
}

void GameState::initPauseMenu()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
	this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);

	this->pmenu->addButton("QUIT", gui::p2pY(74.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::clacCharSize(vm), "QUIT");
}

void GameState::initShaders()
{
	if (!this->core_shader.loadFromFile("vertex_shader.vert", "fragment_shader.frag"))
	{
		std::cout << "ERROR::GAMESTATE::COULD NOT LOAD SHADER" << "\n";
	}
}

void GameState::initKeyTime()
{
	this->keyTimeMax = 0.2f;
	this->keyTimer.restart();
}

void GameState::initDebugText()
{
	this->debugText.setFont(this->font);
	this->debugText.setFillColor(sf::Color::White);
	this->debugText.setCharacterSize(16);
	this->debugText.setPosition(15.f, this->view.getSize().y / 2.f);
}

void GameState::initPlayers()
{
	this->player = new Player(200, 200, this->textures["PLAYER_SHEET"]);
}

void GameState::initPlayerGui()
{
	this->playerGui = new PlayerGui(this->player, this->stateData->gfxSettings->resolution);
}

void GameState::initEnemySystem()
{
	this->enemySystem = new EnemySystem(this->activeEnemies, this->textures, *this->player);
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap("test.slmp");
}

void GameState::initSystems()
{
	this->tts = new TextTagSystem("Fonts/AGENCYR.TTF");
}

// Constructors //
GameState::GameState(StateData* state_data)
	:State(state_data)
{
	this->initDeferredRender();
	this->initView();
	this->initKeybinds();
	this->initFonts();
	this->initTexture();
	this->initPauseMenu();
	this->initShaders();
	this->initKeyTime();
	this->initDebugText();

	this->initPlayers();
	this->initPlayerGui();
	this->initEnemySystem();
	this->initTileMap();
	this->initSystems();
	
}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
	delete this->playerGui;
	delete this->enemySystem;
	delete this->tileMap;
	delete this->tts;

	// test //
	for (size_t i = 0; i < this->activeEnemies.size(); i++)
	{
		delete this->activeEnemies[i];
	}
}

// Accessors //
const bool GameState::getKeyTime()
{
	if (this->keyTimer.getElapsedTime().asSeconds() >= this->keyTimeMax)
	{
		this->keyTimer.restart();
		return true;
	}
	return false;
}


// functions //

void GameState::updateView(const float& dt)
{
		this->view.setCenter(
			std::floor(this->player->getPosition().x + (static_cast<float>(this->mousePosWindow.x) - static_cast<float>(this->stateData->gfxSettings->resolution.width / 2)) / 10.f),
			std::floor(this->player->getPosition().y + (static_cast<float>(this->mousePosWindow.y) - static_cast<float>(this->stateData->gfxSettings->resolution.height / 2)) / 10.f)
		);
	//std::cout << this->tileMap->getMaxSizeF().x << " " << this->view.getSize().x << "\n";

	if (this->tileMap->getMaxSizeF().x >= this->view.getSize().x)
	{
		if (this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f)
		{
			this->view.setCenter(0.f + this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
		else if (this->view.getCenter().x + this->view.getSize().x / 2.f >= this->tileMap->getMaxSizeF().x) // limit camera to not get out the map //
		{
			this->view.setCenter(this->tileMap->getMaxSizeF().x - this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
	}

	if (this->tileMap->getMaxSizeF().y >= this->view.getSize().y)
	{
		if (this->view.getCenter().y - this->view.getSize().y / 2.f < 0.f)
		{
			this->view.setCenter(this->view.getCenter().x, 0.f + this->view.getSize().y / 2.f);
		}
		else if (this->view.getCenter().y + this->view.getSize().y / 2.f >= this->tileMap->getMaxSizeF().y) // limit camera to not get out the map //
		{
			this->view.setCenter(this->view.getCenter().x, this->tileMap->getMaxSizeF().y - this->view.getSize().y / 2.f);
		}
	}

	this->viewGridPosition.x = static_cast<int>(this->view.getCenter().x) / static_cast<int>(this->stateData->gridSize);
	this->viewGridPosition.y = static_cast<int>(this->view.getCenter().y) / static_cast<int>(this->stateData->gridSize);
	
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->pause)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void GameState::updatePlayerInput(const float& dt)
{

	// Update player Input //
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
			this->player->move(-1.f, 0.f, dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
			this->player->move(1.f, 0.f, dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		{
			this->player->move(0.f, -1.f, dt);

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		{
			this->player->move(0.f, 1.f, dt);
		}
	
}

void GameState::updatePlayerGui(const float& dt)
{
	this->playerGui->update(dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TOGGLE_PLAYER_TAB_CHARACTER"))) && this->getKeyTime())
	{
		this->playerGui->toggleCharacterTab();
	}
}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
}

void GameState::updateTileMap(const float& dt)
{
	this->tileMap->updateWorldBoundsCollision(this->player, dt);
	this->tileMap->updateTileCollision(this->player, dt);
	this->tileMap->updateTiles(this->player, dt, *this->enemySystem);

}

void GameState::updatePlayer(const float& dt)
{
	this->player->update(dt, this->mousePosView, this->view);

}

void GameState::updateCombatAndEnemies(const float& dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->getWeapon()->getAttackTimer())
		this->player->setInitAttack(true);

	unsigned index = 0;
	for (auto* enemy : this->activeEnemies)
	{
		enemy->update(dt, this->mousePosView, this->view);

		this->tileMap->updateWorldBoundsCollision(enemy, dt);
		this->tileMap->updateTileCollision(enemy, dt);

		
		this->updateCombat(enemy, index, dt);

		//Danger!!
		if (enemy->enemyIsDead())
		{
			this->player->gainEXP(enemy->getGainExp());
			this->tts->addTextTag(EXPRIENCE_TAG, this->player->getCenter().x, this->player->getCenter().y - 20.f, static_cast<int>(enemy->getGainExp()), "+", "EXP");
			this->player->gainScore(150);
			this->enemySystem->removeEnemy(index);
			continue;
		}
		else if(enemy->getDespawnTimerDone())
		{
			this->enemySystem->removeEnemy(index);
			continue;
		}

		++index;
	}

	this->player->setInitAttack(false);
}

void GameState::updateCombat(Enemy* enemy, const int index, const float& dt)
{
	if (this->player->getInitAttack() 
		&& enemy->getGlobalBounds().contains(this->mousePosView)
		&& enemy->getSpriteDistance(*this->player) < this->player->getWeapon()->getRange()
		&& enemy->getDamageTimerDone())
	{
			int dmg = static_cast<int>(this->player->getDamage());
			enemy->enemyloseHp(dmg);
			enemy->resetDamageTimer();
			this->player->gainScore(75);
			this->tts->addTextTag(DEFAULT_TAG, enemy->getCenter().x, enemy->getCenter().y + 40.f, dmg, "", "");

	}

	// Check Enemy damage //
	if(EnemyTyeps::RED_BAT)
	
	if (enemy->getGlobalBounds().intersects(this->player->getGlobalBounds()) && this->player->getDamageTimer())
	{
			int dmg = enemy->getFireAttributeComp()->damageMax;
			this->player->loseHP(dmg);
			this->tts->addTextTag(NEGATIVE_TAG, this->player->getCenter().x, this->player->getCenter().y, dmg, "-", "HP");
	}

	
}

void GameState::updateDebugText(const float& dt)
{
	std::stringstream ss;

	ss << "Mouse Pos View: " << this->mousePosView.x << " " << this->mousePosView.y << "\n"
		<< "Active Enemy: " << this->activeEnemies.size() << "\n";

	this->debugText.setString(ss.str());
}

void GameState::update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);

	this->updateDebugText(dt);
	
	// Unpaused update //
	if (!this->pause) 
	{
		this->updateView(dt);

		this->updatePlayerInput(dt);

		this->updateTileMap(dt);

		this->updatePlayer(dt);

		this->updatePlayerGui(dt);

		// Update All Enemies //
		this->updateCombatAndEnemies(dt);

		// Update Systems //
		this->tts->update(dt);
	}
	// Paused update //
	else
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->renderTexture.clear();

	this->renderTexture.setView(this->view);

	this->tileMap->render(
		this->renderTexture,
		this->viewGridPosition,
		&this->core_shader,
		this->player->getCenter(),
		false
	);
	
	// test //
	for (auto* enemy : this->activeEnemies)
	{
		enemy->render(this->renderTexture, &this->core_shader, this->player->getCenter(), true);
	}

	this->player->render(this->renderTexture, &this->core_shader, this->player->getCenter(),true);

	this->tileMap->renderDeferred(this->renderTexture, &this->core_shader, this->player->getCenter());

	this->tts->render(this->renderTexture);

	// Render GUI //
	this->renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGui->render(this->renderTexture);

	if (this->pause) // Pause menu render //
		{
		//this->renderTexture.setView(this->renderTexture.getDefaultView());
			this->pmenu->render(this->renderTexture);
		}

	// Debug Text //
	this->renderTexture.draw(this->debugText);

	// Final render //
	this->renderTexture.display();
	//this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}
