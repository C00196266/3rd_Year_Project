#include "EndScreen.h"

EndScreen::EndScreen() {
	if (!m_font.loadFromFile("assets/arial.ttf"))
	{
		std::cout << "Font failed to Load" << std::endl;
	}

	m_victoryText.setString("You won!");
	m_victoryText.setFont(m_font);
	m_victoryText.setCharacterSize(40);
	m_victoryText.setPosition(560, 300);

	m_scoreText.setString("Final Score: 0");
	m_scoreText.setFont(m_font);
	m_scoreText.setCharacterSize(30);
	m_scoreText.setPosition(555, 390);

	m_timeForTransition = 300;

	m_background.setSize(sf::Vector2f(2000, 1000));
	m_background.setFillColor(sf::Color::Black);
}

void EndScreen::update(GameStates &currentGameState) {
	if (m_timeForTransition > 0) {
		m_timeForTransition--;
	}
	else {
		currentGameState = GameStates::MainMenu;
		m_timeForTransition = 300;
	}
}

void EndScreen::draw(sf::RenderWindow &window) {
	window.draw(m_background);
	window.draw(m_victoryText);
	window.draw(m_scoreText);
}

void EndScreen::changeScore(int score) {
	m_scoreText.setString("Final Score: " + to_string(score));
}