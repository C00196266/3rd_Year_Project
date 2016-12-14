#pragma once
#include "Tile.h"
#include "PickupScore.h"
#include "PickupHealth.h"
#include "PickupMana.h"
#include "Enemy.h"
#include "LevelExit.h"
#include "Player.h"
#include "CollisionDetection.h"
#include "Spike.h"

class Level
{
public:
	Level();
	void draw(sf::RenderWindow & window);
	void createMap();
	void changeLevel(int newLevelNum);
	vector<shared_ptr<Tile>>& getTiles();
	vector<shared_ptr<PickupScore>>& getScorePickups();
	vector<shared_ptr<PickupHealth>>& getHealthPickups();
	vector<shared_ptr<PickupMana>>& getManaPickups();
	vector<shared_ptr<Enemy>>& getEnemies();
	vector<shared_ptr<Spike>>& getSpikes();
	shared_ptr<LevelExit> getExit();

private:
	int maxCol;
	int maxRow;
	int maxTiles;
	int tileSize;
	vector<shared_ptr<Tile>> m_tileVector;
	vector<shared_ptr<PickupScore>> m_scorePickups;
	vector<shared_ptr<PickupHealth>> m_healthPickups;
	vector<shared_ptr<PickupMana>> m_manaPickups;
	vector<shared_ptr<Enemy>> m_enemies;
	vector<shared_ptr<Spike>> m_spike;
	std::shared_ptr<int> numLevel;
	std::shared_ptr<LevelExit> m_levelEnd;
	static const int level1[10][75];
	static const int leveltest[10][34];
	sf::Texture grassTexture;
	int *currentLevel;//pointer to current level array
	void resetLevel();
};
