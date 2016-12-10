#ifndef GAMESCREEN_H
#define GAMESCREEN_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include "Player.h"
#include "Tile.h"
#include "GameState.h"
#include "CollisionDetection.h"
#include "PickupScore.h"
#include "PickupHealth.h"
#include "PickupMana.h"
#include "Enemy.h"

////////////////////////////////////////////////////////////
///	\brief Class Manages what is on the game screen and draws
/// it.
///
////////////////////////////////////////////////////////////

class GameScreen {
public:
	GameScreen();
	//~GameScreen();

	void update(GameStates &currentGameState,sf::View &view, sf::RenderWindow &window);

	void draw(sf::RenderWindow &window);

	void detectCollisions();

	void changeGameState(GameStates &currentGameState, sf::View &view, sf::RenderWindow &window);

	void resumeGame();

private:
	Player m_player;

	CollisionDetection m_collisionDetector;
	
	vector<shared_ptr<Tile>> m_tiles;

	vector<shared_ptr<PickupScore>> m_scorePickups;

	vector<shared_ptr<PickupHealth>> m_healthPickups;

	vector<shared_ptr<PickupMana>> m_manaPickups;

	vector<shared_ptr<Enemy>> m_enemies;

	int keyPressTimer;
};

#endif
