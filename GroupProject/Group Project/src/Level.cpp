#include "Level.h"

Level::Level()
{
	if (!grassTexture.loadFromFile("assets/tileGrass.png"))
	{
		//error
	}

	numLevel = std::shared_ptr<int>(new int(1));
	changeLevel(*numLevel);
}

void Level::draw(sf::RenderWindow & window)
{
	for (int i = 0; i < m_tileVector.size(); i++)
	{
		m_tileVector.at(i)->draw(window);
	}
	for (int i = 0; i < m_scorePickups.size(); i++)
	{
		m_scorePickups.at(i)->draw(window);
	}
	for (int i = 0; i < m_manaPickups.size(); i++)
	{
		m_manaPickups.at(i)->draw(window);
	}
	for (int i = 0; i < m_healthPickups.size(); i++)
	{
		m_healthPickups.at(i)->draw(window);
	}
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies.at(i)->draw(window);
	}
	for (int i = 0; i < m_spike.size(); i++) {
		m_spike.at(i)->draw(window);
	}
	m_levelEnd->draw(window);
}

void Level::createMap()
{
	for (int column = 0; column < maxCol; column++)
	{
		for (int row = 0; row < maxRow; row++)
		{
			if (currentLevel[maxCol*(row)+column] == 0)
			{
				//empty space
			}
			if (currentLevel[maxCol*(row)+column] == 1)
			{
				m_tileVector.push_back(shared_ptr<Tile>(new Tile(sf::Vector2f(column*tileSize, row*tileSize), "assets/tileGrass.png")));
			}
			if (currentLevel[maxCol*(row)+column] == 2)
			{
				m_scorePickups.push_back(shared_ptr<PickupScore>(new PickupScore(sf::Vector2f((column*tileSize) + 10, (row*tileSize) + 10))));
			}
			if (currentLevel[maxCol*(row)+column] == 3)
			{
				m_spike.push_back(shared_ptr<Spike>(new Spike(sf::Vector2f((column*tileSize), (row*tileSize)))));
			}
			if (currentLevel[maxCol*(row)+column] == 4)
			{
				m_manaPickups.push_back(shared_ptr<PickupMana>(new PickupMana(sf::Vector2f((column*tileSize) + 10, (row*tileSize) + 10))));
			}
			if (currentLevel[maxCol*(row)+column] == 5)
			{
				m_enemies.push_back(shared_ptr<Enemy>(new Enemy(sf::Vector2f(column*tileSize, row*tileSize))));
			}
			if (currentLevel[maxCol*(row)+column] == 6)
			{
				m_levelEnd = (shared_ptr<LevelExit>(new LevelExit(sf::Vector2f(column*tileSize, row*tileSize), 0)));
			}
			if (currentLevel[maxCol*(row)+column] == 7)
			{
				m_tileVector.push_back(shared_ptr<Tile>(new Tile(sf::Vector2f(column*tileSize, row*tileSize), "assets/dirt.png")));
			}
			if (currentLevel[maxCol*(row)+column] == 8)
			{
				m_healthPickups.push_back(shared_ptr<PickupHealth>(new PickupHealth(sf::Vector2f((column*tileSize) + 10, (row*tileSize) + 10))));
			}
			if (currentLevel[maxCol*(row)+column] == 9)
			{
				m_newStartPos = sf::Vector2f(column*tileSize, row*tileSize + 26);
			}
		}
	}
}

void Level::resetLevel()
{
	m_tileVector.clear();
	m_scorePickups.clear();
	m_healthPickups.clear();
	m_manaPickups.clear();
	m_enemies.clear();
	m_spike.clear();
	m_levelEnd.reset();
}

void Level::changeLevel(int newLevelNum)
{
	if (newLevelNum == 0)
	{
		resetLevel();
		*numLevel = 0;
		maxRow = 15;
		maxCol = 34;
		currentLevel = (int*)leveltest;
		tileSize = 40;
		createMap();
	}
	else if (newLevelNum == 1)
	{
		resetLevel();
		*numLevel = 1;
		maxRow = 15;
		maxCol = 75;
		currentLevel = (int*)level1;
		tileSize = 40;
		createMap();
	}
}

const int Level::level1[15][75]
{
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 2, 1, 0, 1, 0, 2, 8, 0, 5, 0, 0, 1, 1, 1, 0, 0, 7, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 1, 1, 0, 0, 8, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1, 0, 0, 1, 7, 0, 0, 0, 0, 5, 1, 7, 0, 7, 0, 1, 1, 1, 1, 0, 0, 7, 7, 7, 0, 0, 7, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 7, 7, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 7, 1, 1, 7, 7, 0, 1, 1, 1, 1, 7, 7, 0, 7, 0, 7, 7, 7, 7, 0, 0, 7, 7, 7, 0, 0, 7, 0, 7, 0, 0, 0, 0, 0, 4, 0, 0, 0, 7, 0, 0, 7, 0, 1, 1, 7, 7, 0, 0, 7, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 },
	{ 9, 0, 0, 0, 0, 0, 0, 1, 7, 7, 0, 7, 7, 7, 7, 7, 0, 7, 7, 7, 7, 7, 7, 0, 7, 0, 7, 7, 7, 7, 0, 0, 7, 7, 7, 0, 0, 7, 0, 7, 0, 0, 0, 0, 1, 1, 1, 1, 1, 7, 0, 0, 7, 0, 7, 7, 7, 7, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 6 },
	{ 0, 0, 0, 2, 2, 0, 0, 7, 7, 7, 3, 7, 7, 7, 7, 7, 3, 7, 7, 7, 7, 7, 7, 3, 7, 3, 7, 7, 7, 7, 3, 3, 7, 7, 7, 3, 3, 7, 3, 7, 3, 3, 3, 3, 7, 7, 7, 7, 7, 7, 3, 3, 7, 3, 7, 7, 7, 7, 3, 3, 7, 1, 3, 3, 1, 3, 3, 3, 1, 3, 3, 3, 3, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 1, 1, 1, 7, 1, 1, 1, 1, 7, 7 },
	{ 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7 },
	{ 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7 },
	{ 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7 },
	{ 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7 },
	{ 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7 }
};

const int Level::leveltest[15][34]
{
	{ 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

vector<shared_ptr<Tile>>& Level::getTiles()
{
	return m_tileVector;
}

vector<shared_ptr<PickupScore>>& Level::getScorePickups()
{
	return m_scorePickups;
}

vector<shared_ptr<PickupHealth>>& Level::getHealthPickups()
{
	return m_healthPickups;
}

vector<shared_ptr<PickupMana>>& Level::getManaPickups()
{
	return m_manaPickups;
}

vector<shared_ptr<Enemy>>& Level::getEnemies()
{
	return m_enemies;
}

vector<shared_ptr<Spike>>& Level::getSpikes() {
	return m_spike;
}

shared_ptr<LevelExit> Level::getExit()
{
	return m_levelEnd;
}

sf::Vector2f Level::getNewStartPos() {
	return m_newStartPos;
}