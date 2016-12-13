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
#include "Level.h"
#include "AudioManager.h"

////////////////////////////////////////////////////////////
///	\brief Class Manages what is on the game screen and draws
/// it.
///
////////////////////////////////////////////////////////////

class GameScreen {
public:
	GameScreen();
	//~GameScreen();

	void update(GameStates &currentGameState,sf::View &view, sf::RenderWindow &window, shared_ptr<AudioManager> audioManager);

	void draw(sf::RenderWindow &window);

	void detectCollisions();

	void changeGameState(GameStates &currentGameState, sf::View &view, sf::RenderWindow &window);

	void resumeGame();

private:
	Player m_player;

	CollisionDetection m_collisionDetector;

	int keyPressTimer;

	Level gameLevel;
};

#endif
