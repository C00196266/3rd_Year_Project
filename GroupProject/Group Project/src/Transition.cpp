#include "Transition.h"

Transition::Transition() {
	if (!m_font.loadFromFile("assets/arial.ttf"))
	{
		std::cout << "Font failed to Load" << std::endl;
	}

	m_levelText.setString("Level: 1");
	m_levelText.setFont(m_font);
	m_levelText.setCharacterSize(40);
	m_levelText.setPosition(570, 300);

	m_scoreText.setString("Score: 0");
	m_scoreText.setFont(m_font);
	m_scoreText.setCharacterSize(30);
	m_scoreText.setPosition(585, 380);

	m_timeForTransition = 120;

	m_background.setSize(sf::Vector2f(2000, 1000));
	m_background.setFillColor(sf::Color::Black);
}

void Transition::update(GameStates &currentGameState) {
	if (m_timeForTransition > 0) {
		m_timeForTransition--;
	}
	else {
		currentGameState = GameStates::Game;
		m_timeForTransition = 120;
	}
}

void Transition::draw(sf::RenderWindow &window) {
	window.draw(m_background);
	window.draw(m_levelText);
	window.draw(m_scoreText);
}

void Transition::changeText(int level, int score) {
	m_levelText.setString("Level: " + to_string(level));
	m_scoreText.setString("Score: " + to_string(score));
}