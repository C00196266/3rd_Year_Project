#pragma once
#include "Tile.h"

class Level
{
public:
	Level();
	void draw(sf::RenderWindow & window);
	void update();
	void createMap();
	void changeLevel(int newLevelNum);
	vector<shared_ptr<Tile>>& getTileVector();
private:
	int maxCol;
	int maxRow;
	int maxTiles;
	int tileSize;
	vector<shared_ptr<Tile>> m_tileVector;
	std::shared_ptr<int> numLevel;
	static const int level1[10][34];
	static const int leveltest[10][34];
	sf::Texture grassTexture;
	int *currentLevel;//pointer to current level array
	void resetLevel();
};
