#include "GameScreen.h"

GameScreen::GameScreen() {
	m_player.setPos(sf::Vector2f(80, 300));
	keyPressTimer = 0;
}

void GameScreen::resumeGame()
{
	m_player.resumeGame();
}

void GameScreen::update(GameStates &currentGameState,sf::View &view,sf::RenderWindow &window) {
	m_player.update();
	view.move(m_player.getPos().x - view.getSize().x / 2, 0);

	// removes any score pickups that are no longer alive
	if (gameLevel.getScorePickups().empty() != true) {
		for (int i = 0; i < gameLevel.getScorePickups().size(); i++) {
			if (gameLevel.getScorePickups().at(i)->getIsAlive() == false) {
				gameLevel.getScorePickups().erase(gameLevel.getScorePickups().begin() + i);
			}
		}
	}

	// removes any health pickups that are no longer alive
	if (gameLevel.getHealthPickups().empty() != true) {
		for (int i = 0; i < gameLevel.getHealthPickups().size(); i++) {
			if (gameLevel.getHealthPickups().at(i)->getIsAlive() == false) {
				gameLevel.getHealthPickups().erase(gameLevel.getHealthPickups().begin() + i);
			}
		}
	}

	// removes any mana pickups that are no longer alive
	if (gameLevel.getManaPickups().empty() != true) {
		for (int i = 0; i < gameLevel.getManaPickups().size(); i++) {
			if (gameLevel.getManaPickups().at(i)->getIsAlive() == false) {
				gameLevel.getManaPickups().erase(gameLevel.getManaPickups().begin() + i);
			}
		}
	}

	// removes any enemies that are no longer alive
	if (gameLevel.getEnemies().empty() != true) {
		for (int i = 0; i < gameLevel.getEnemies().size(); i++) {
			if (gameLevel.getEnemies().at(i)->getIsAlive() == false) {
				gameLevel.getEnemies().erase(gameLevel.getEnemies().begin() + i);
			}
		}
	}

	detectCollisions();
	changeGameState(currentGameState,view,window);
	keyPressTimer++;
}

void GameScreen::draw(sf::RenderWindow &window) {
	gameLevel.draw(window);
	m_player.draw(window);
}

void GameScreen::changeGameState(GameStates &currentGameState, sf::View &view, sf::RenderWindow &window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		//Change Game State to Play Game
		currentGameState = GameStates::PauseMenu;
		keyPressTimer = 0;
		view.reset(sf::FloatRect(0, 0, 1280, 720));
		window.setView(view);
	}
}

void GameScreen::detectCollisions() {
	for (int i = 0; i < gameLevel.getTiles().size(); i++) {
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// detects if player is standing on top of solid ground
		if (m_collisionDetector.boundingBoxCollision(m_player.getPos().x, m_player.getPos().y, m_player.getWidth(), m_player.getHeight(),
			gameLevel.getTiles().at(i)->getPos().x, gameLevel.getTiles().at(i)->getPos().y, gameLevel.getTiles().at(i)->getWidth(), gameLevel.getTiles().at(i)->getHeight()) == true)
		{

			//Collision Top
			if (m_player.getPos().y + m_player.getHeight()> gameLevel.getTiles().at(i)->getPos().y &&	//Checks if player pos y + height is greater than top of tile
				m_player.getPos().x + m_player.getWidth()> gameLevel.getTiles().at(i)->getPos().x && //Player x+width greater than tile x
				m_player.getPos().x< gameLevel.getTiles().at(i)->getPos().x+ gameLevel.getTiles().at(i)->getWidth()//Player x less than tile x+width
				)

			{
				if (m_player.getInAir() == true)
				{
					m_player.setInAir(false);
					m_player.setYPos(m_player.getPos().y-m_player.getVel().y);
					m_player.setVel(sf::Vector2f(m_player.getVel().x, 0));
					std::cout << "Top" << std::endl;
					if (i == 0)
					{
						std::cout << "Top Collision" << std::endl;
					}
				}
			}

			//Collision Left or Right
			if (	
				m_player.getPos().x + m_player.getWidth() > gameLevel.getTiles().at(i)->getPos().x && //If there is collision then if the players x pos+width is greater than tile x
				m_player.getPos().y + m_player.getHeight() > gameLevel.getTiles().at(i)->getPos().y //Check if the bottom the player is below the tile pos y
				)
			{
				m_player.setXPos(m_player.getPos().x-m_player.getVel().x);
				m_player.setVel(sf::Vector2f(0, m_player.getVel().y));
				std::cout << "Left or Right" << std::endl;
			}
			break;
		}
		else
		{

		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (m_player.getProjectiles().empty() != true) {
			for (int j = 0; j < m_player.getProjectiles().size(); j++) {
				// if the bullet collides with the terrain
				if (m_collisionDetector.boundingBoxCollision(m_player.getProjectiles().at(j)->getPos().x, m_player.getProjectiles().at(j)->getPos().y, m_player.getProjectiles().at(j)->getWidth(),
					m_player.getProjectiles().at(j)->getHeight(), gameLevel.getTiles().at(i)->getPos().x, gameLevel.getTiles().at(i)->getPos().y, gameLevel.getTiles().at(i)->getWidth(), gameLevel.getTiles().at(i)->getHeight()) == true)
				{
					m_player.getProjectiles().at(j)->setAlive(false);
				}
			}
		}
	}

	// player collides with score pickup
	if (gameLevel.getScorePickups().empty() != true) {
		for (int i = 0; i < gameLevel.getScorePickups().size(); i++) {
			if (m_collisionDetector.boundingBoxCollision(m_player.getPos().x, m_player.getPos().y, m_player.getWidth(), m_player.getHeight(), 
				gameLevel.getScorePickups().at(i)->getPos().x, gameLevel.getScorePickups().at(i)->getPos().y, gameLevel.getScorePickups().at(i)->getWidth(), gameLevel.getScorePickups().at(i)->getHeight()) ==true)
			{
				m_player.setScore(gameLevel.getScorePickups().at(i)->getScore());
				gameLevel.getScorePickups().at(i)->setIsAlive(false);
			}
		}
	}

	// player collides with health pickup
	if (gameLevel.getHealthPickups().empty() != true) {
		for (int i = 0; i < gameLevel.getHealthPickups().size(); i++) {
			if (m_collisionDetector.boundingBoxCollision(m_player.getPos().x, m_player.getPos().y, m_player.getWidth(), m_player.getHeight(),
				gameLevel.getHealthPickups().at(i)->getPos().x, gameLevel.getHealthPickups().at(i)->getPos().y, gameLevel.getHealthPickups().at(i)->getWidth(), gameLevel.getHealthPickups().at(i)->getHeight()) == true)
			{
				m_player.setHealth(gameLevel.getHealthPickups().at(i)->getHealth());
				gameLevel.getHealthPickups().at(i)->setIsAlive(false);
			}
		}
	}

	// player collides with mana pickup
	if (gameLevel.getManaPickups().empty() != true) {
		for (int i = 0; i < gameLevel.getManaPickups().size(); i++) {
			if (m_collisionDetector.boundingBoxCollision(m_player.getPos().x, m_player.getPos().y, m_player.getWidth(), m_player.getHeight(),
				gameLevel.getManaPickups().at(i)->getPos().x, gameLevel.getManaPickups().at(i)->getPos().y, gameLevel.getManaPickups().at(i)->getWidth(), gameLevel.getManaPickups().at(i)->getHeight()) == true)
			{
				m_player.setMana(gameLevel.getManaPickups().at(i)->getMana());
				gameLevel.getManaPickups().at(i)->setIsAlive(false);
			}
		}
	}

	if (gameLevel.getEnemies().empty() != true) {
		for (int i = 0; i < gameLevel.getEnemies().size(); i++) {
			// if the player isn't invincible after taking damage
			if (m_player.getInvincibilityFrames() == 0) {
				// player collides with enemy
				if (m_collisionDetector.boundingBoxCollision(m_player.getPos().x, m_player.getPos().y, m_player.getWidth(), m_player.getHeight(),
					gameLevel.getEnemies().at(i)->getPos().x, gameLevel.getEnemies().at(i)->getPos().y, gameLevel.getEnemies().at(i)->getWidth(), gameLevel.getEnemies().at(i)->getHeight()) == true)
				{
					m_player.setHealth(-gameLevel.getEnemies().at(i)->damageDealt());
				}
			}

			// player projectile collides with enemy
			for (int j = 0; j < m_player.getProjectiles().size(); j++) {
				if (m_collisionDetector.boundingBoxCollision(m_player.getProjectiles().at(j)->getPos().x, m_player.getProjectiles().at(j)->getPos().y, m_player.getProjectiles().at(j)->getWidth(),
					m_player.getProjectiles().at(j)->getHeight(), gameLevel.getEnemies().at(i)->getPos().x, gameLevel.getEnemies().at(i)->getPos().y, gameLevel.getEnemies().at(i)->getWidth(), gameLevel.getEnemies().at(i)->getHeight()) == true)
				{
					m_player.setScore(gameLevel.getEnemies().at(i)->addScore());
					gameLevel.getEnemies().at(i)->setIsAlive(false);
					m_player.getProjectiles().at(j)->setAlive(false); // projectile is no longer alive on collision with enemy
				}
			}
		}
	}
}