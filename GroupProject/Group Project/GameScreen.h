#ifndef GAMESCREEN_H
#define GAMESCREEN_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include "Player.h"
#include "Tile.h"
#include "GameState.h"

////////////////////////////////////////////////////////////
///	\brief Class Manages what is on the game screen and draws
/// it.
///
////////////////////////////////////////////////////////////

class GameScreen {
public:
	GameScreen();
	//~GameScreen();

	void update(GameStates &currentGameState);

	void draw(sf::RenderWindow &window);
	void changeGameState(GameStates &currentGameState);
private:
	Player m_player;
	vector<shared_ptr<Tile>> m_tiles;
	int keyPressTimer;
};

#endif
