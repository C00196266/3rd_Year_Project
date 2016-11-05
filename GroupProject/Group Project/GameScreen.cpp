#include "GameScreen.h"

GameScreen::GameScreen() {
	for (int i = 0; i < 34; i++) {
		m_tiles.push_back(shared_ptr<Tile>(new Tile(sf::Vector2f(i * 40.0f, 370.0f))));
	}
}

void GameScreen::update(GameStates &currentGameState) {
	m_player.update();
	changeGameState(currentGameState);
	keyPressTimer++;
}

void GameScreen::draw(sf::RenderWindow &window) {
	m_player.draw(window);

	for (int i = 0; i < m_tiles.size(); i++) {
		m_tiles.at(i)->draw(window);
	}
}

void GameScreen::changeGameState(GameStates &currentGameState)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		//Change Game State to Play Game
		currentGameState = GameStates::PauseMenu;
		keyPressTimer = 0;
		
	}
}