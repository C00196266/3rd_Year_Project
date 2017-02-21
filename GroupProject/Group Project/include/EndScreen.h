#include "stdafx.h"
#include "GameState.h"

class EndScreen {
public:
	EndScreen();

	void update(GameStates &currentGameState);

	void draw(sf::RenderWindow &window);

	void changeScore(int score);

private:
	sf::Font m_font;

	sf::RectangleShape m_background;
	sf::Text m_victoryText;
	sf::Text m_scoreText;

	int m_timeForTransition;
};