#include "stdafx.h"
#include "AudioManager.h"
#include "GameState.h"

class Transition {
public:
	Transition();

	void update(GameStates &currentGameState);

	void draw(sf::RenderWindow &window);

	void changeText(int level, int score);

private:
	sf::Font m_font;

	sf::RectangleShape m_background;
	sf::Text m_levelText;
	sf::Text m_scoreText;
	
	int m_timeForTransition;
};
