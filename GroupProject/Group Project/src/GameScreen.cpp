#include "GameScreen.h"

GameScreen::GameScreen() {
	m_player.setPos(sf::Vector2f(80, 300));
	//m_player.setInitialPos(m_player.getPos());

	if (!m_image.loadFromFile("assets/Background.png")) {

	}
	if (!m_texture.loadFromImage(m_image)) {

	}
	m_backgroundSprite.setTexture(m_texture);

	keyPressTimer = 0;
}

void GameScreen::resumeGame()
{
	m_player.resumeGame();
}

void GameScreen::update(GameStates &currentGameState, sf::View &view, sf::RenderWindow &window, shared_ptr<AudioManager> audioManager) {
 	m_player.update(audioManager);

	view.move(m_player.getPos().x - view.getSize().x / 2, m_player.getPos().y - (view.getSize().y / 2) - 60);

	m_backgroundSprite.setPosition(view.getCenter().x - (view.getSize().x / 2), view.getCenter().y - (view.getSize().y / 2));

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
	if (gameLevel.getEnemiesRanged().empty() != true) 
	{
		for (int i = 0; i < gameLevel.getEnemiesRanged().size(); i++) 
		{

			//gameLevel.getEnemiesRanged().at(i)->Targeting(m_player.getPos(), m_player.getHeight());

			if (m_player.getPos().x < gameLevel.getEnemiesRanged().at(i)->getPos().x && m_player.getPos().x > gameLevel.getEnemiesRanged().at(i)->getPos().x - gameLevel.getEnemiesRanged().at(i)->getRange())//Left Side
			{
 				if (m_player.getPos().y < gameLevel.getEnemiesRanged().at(i)->getPos().y + gameLevel.getEnemiesRanged().at(i)->getHeight() && m_player.getPos().y + m_player.getHeight() > gameLevel.getEnemiesRanged().at(i)->getPos().y)
				{
					gameLevel.getEnemiesRanged().at(i)->FireProjectile(0);
				}
			}
			else if (m_player.getPos().x > gameLevel.getEnemiesRanged().at(i)->getPos().x && m_player.getPos().x < gameLevel.getEnemiesRanged().at(i)->getPos().x + gameLevel.getEnemiesRanged().at(i)->getRange())//Right Side
			{
				if (m_player.getPos().y < gameLevel.getEnemiesRanged().at(i)->getPos().y + gameLevel.getEnemiesRanged().at(i)->getHeight() && m_player.getPos().y + m_player.getHeight() > gameLevel.getEnemiesRanged().at(i)->getPos().y)
				{
					gameLevel.getEnemiesRanged().at(i)->FireProjectile(1);
				}
			}
			else//Not in Range
			{
				
			}
			gameLevel.getEnemiesRanged().at(i)->m_timeSinceFire = gameLevel.getEnemiesRanged().at(i)->m_timeSinceFire + 1;
			for (int i = 0; i < gameLevel.getEnemiesRanged().at(i)->getProjectiles().size(); i++)
			{
				gameLevel.getEnemiesRanged().at(i)->getProjectiles().at(i)->update();
			}
			// allows enemy to be hit again by attacks from the player
			if (gameLevel.getEnemiesRanged().at(i)->getTaggedByAttack() == true && m_player.getAttacking() == false) 
			{
				gameLevel.getEnemiesRanged().at(i)->setTaggedByAttack(false);
			}

			if (gameLevel.getEnemiesRanged().at(i)->getIsAlive() == false) 
			{
				gameLevel.getEnemiesRanged().erase(gameLevel.getEnemiesRanged().begin() + i);
			}

		}
	}

	detectCollisions(audioManager);
	changeGameState(currentGameState, view, window);
	keyPressTimer++;
}

void GameScreen::draw(sf::RenderWindow &window) {
	window.draw(m_backgroundSprite);
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

void GameScreen::detectCollisions(shared_ptr<AudioManager> audioManager) {
	if (m_collisionDetector.boundingBoxCollision(m_player.getPos().x, m_player.getPos().y, m_player.getWidth(), m_player.getHeight(),
		gameLevel.getExit()->getPosition().x, gameLevel.getExit()->getPosition().y, gameLevel.getExit()->getSize().x, gameLevel.getExit()->getSize().y))
	{
		m_player.setPos(sf::Vector2f(80, 300));
		gameLevel.changeLevel(gameLevel.getExit()->getNextLevel());
	}

	m_player.setCollides(false);

	for (int i = 0; i < gameLevel.getTiles().size(); i++) 
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// detects if player is standing on top of solid ground
		
		gameLevel.getTiles().at(i)->checkCollisionWithPlayer(m_player);
		
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		for (int e = 0; e < gameLevel.getEnemiesRanged().size(); e++)
		{
				for (int j = 0; j < gameLevel.getEnemiesRanged().at(e)->getProjectiles().size(); j++)
				{
					if (gameLevel.getEnemiesRanged().at(e)->getProjectiles().at(j)->checkAlive() == true)
					{
						if (m_collisionDetector.boundingBoxCollision(gameLevel.getEnemiesRanged().at(e)->getProjectiles().at(j)->getPos().x, gameLevel.getEnemiesRanged().at(e)->getProjectiles().at(j)->getPos().y, gameLevel.getEnemiesRanged().at(e)->getProjectiles().at(j)->getWidth(),
							gameLevel.getEnemiesRanged().at(e)->getProjectiles().at(j)->getHeight(), gameLevel.getTiles().at(i)->getPos().x, gameLevel.getTiles().at(i)->getPos().y, gameLevel.getTiles().at(i)->getWidth(), gameLevel.getTiles().at(i)->getHeight()) == true)
						{
							gameLevel.getEnemiesRanged().at(e)->getProjectiles().at(j)->setAlive(false);
						}
					}
				}
		}


		if (m_player.getProjectiles().empty() != true) 
		{
			for (int j = 0; j < m_player.getProjectiles().size(); j++) 
			{
				// if the bullet collides with the terrain
				if (m_collisionDetector.boundingBoxCollision(m_player.getProjectiles().at(j)->getPos().x, m_player.getProjectiles().at(j)->getPos().y, m_player.getProjectiles().at(j)->getWidth(),
					m_player.getProjectiles().at(j)->getHeight(), gameLevel.getTiles().at(i)->getPos().x, gameLevel.getTiles().at(i)->getPos().y, gameLevel.getTiles().at(i)->getWidth(), gameLevel.getTiles().at(i)->getHeight()) == true)
				{
					m_player.getProjectiles().at(j)->setAlive(false);
				}
			}
		}
	}

	m_player.setCollides(false);

	// player collides with score pickup
	if (gameLevel.getScorePickups().empty() != true) {
		for (int i = 0; i < gameLevel.getScorePickups().size(); i++) {
			if (m_collisionDetector.boundingBoxCollision(m_player.getPos().x, m_player.getPos().y, m_player.getWidth(), m_player.getHeight(),
				gameLevel.getScorePickups().at(i)->getPos().x, gameLevel.getScorePickups().at(i)->getPos().y, gameLevel.getScorePickups().at(i)->getWidth(), gameLevel.getScorePickups().at(i)->getHeight()) == true)
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

	// player collides with mana pickupd
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

	if (gameLevel.getEnemiesRanged().empty() != true) {
		for (int i = 0; i < gameLevel.getEnemiesRanged().size(); i++) {
			// if the player isn't invincible after taking damage
			if (m_player.getInvincibilityFrames() == 0) {
				if (m_player.getKnockback() == true) {
					m_player.setKnockback(false);
				}
				// player collides with enemy
				if (m_player.getAttacking() == false) {
					if (m_collisionDetector.boundingBoxCollision(m_player.getPos().x, m_player.getPos().y, m_player.getWidth(), m_player.getHeight(),
						gameLevel.getEnemiesRanged().at(i)->getPos().x, gameLevel.getEnemiesRanged().at(i)->getPos().y, gameLevel.getEnemiesRanged().at(i)->getWidth(), gameLevel.getEnemiesRanged().at(i)->getHeight()) == true)
					{
						m_player.setHealth(-gameLevel.getEnemiesRanged().at(i)->damageDealt());
						m_player.knockback();
					}
				}

				else {
					// checks if the player has collided with an enemy while attacking, and is facing left
					if (m_collisionDetector.boundingBoxCollision(m_player.getPos().x - 24, m_player.getPos().y, m_player.getWidth() + 18, m_player.getHeight(),
						gameLevel.getEnemiesRanged().at(i)->getPos().x, gameLevel.getEnemiesRanged().at(i)->getPos().y, gameLevel.getEnemiesRanged().at(i)->getWidth(), gameLevel.getEnemiesRanged().at(i)->getHeight()) == true
						&& m_player.getDirection() == m_player.LEFT)
					{
						// if the player hits an enemy on the right while facing left
						if (m_player.getPos().x - 24 < gameLevel.getEnemiesRanged().at(i)->getPos().x + gameLevel.getEnemiesRanged().at(i)->getWidth() && gameLevel.getEnemiesRanged().at(i)->getTaggedByAttack() == false) {
							gameLevel.getEnemiesRanged().at(i)->setHealth(-m_player.getDamageDealt());

							// if the enemy has no more health left
							if (gameLevel.getEnemiesRanged().at(i)->getHealth() <= 0) {
								m_player.setScore(gameLevel.getEnemiesRanged().at(i)->addScore());
								gameLevel.getEnemiesRanged().at(i)->setIsAlive(false);
							}

							// if the enemy is alive
							if (gameLevel.getEnemiesRanged().at(i)->getIsAlive() == true) {
								gameLevel.getEnemiesRanged().at(i)->setTaggedByAttack(true);
							}

							audioManager->playSound(AudioManager::SoundType::PUNCH);
						}
						else if (m_player.getPos().x - 24 < gameLevel.getEnemiesRanged().at(i)->getPos().x + gameLevel.getEnemiesRanged().at(i)->getWidth() && gameLevel.getEnemiesRanged().at(i)->getTaggedByAttack() == true) {
							// do nothing
						}
						else {
							m_player.setHealth(-gameLevel.getEnemiesRanged().at(i)->damageDealt());
							m_player.setAttacking(false);
							m_player.resetAttackDuration();
							m_player.knockback();
						}
					}

					// checks if the player has collided with an enemy while attacking, and is facing right
					else if (m_collisionDetector.boundingBoxCollision(m_player.getPos().x, m_player.getPos().y, m_player.getWidth() + 24, m_player.getHeight(),
						gameLevel.getEnemiesRanged().at(i)->getPos().x, gameLevel.getEnemiesRanged().at(i)->getPos().y, gameLevel.getEnemiesRanged().at(i)->getWidth(), gameLevel.getEnemiesRanged().at(i)->getHeight()) == true
						&& m_player.getDirection() == m_player.RIGHT)
					{
						// if the player hits an enemy on the left while facing right
						if (m_player.getPos().x + m_player.getWidth() + 24 > gameLevel.getEnemiesRanged().at(i)->getPos().x && gameLevel.getEnemiesRanged().at(i)->getTaggedByAttack() == false) {
							gameLevel.getEnemiesRanged().at(i)->setHealth(-m_player.getDamageDealt());
							gameLevel.getEnemiesRanged().at(i)->setTaggedByAttack(true);

							// if the enemy has no more health left
							if (gameLevel.getEnemiesRanged().at(i)->getHealth() <= 0) {
								m_player.setScore(gameLevel.getEnemiesRanged().at(i)->addScore());
								gameLevel.getEnemiesRanged().at(i)->setIsAlive(false);
							}

							// checks if the enemy is alive
							if (gameLevel.getEnemiesRanged().at(i)->getIsAlive() == true) {
								gameLevel.getEnemiesRanged().at(i)->setTaggedByAttack(true);
							}

							audioManager->playSound(AudioManager::SoundType::PUNCH);
						}
						else if (m_player.getPos().x + m_player.getWidth() + 24 > gameLevel.getEnemiesRanged().at(i)->getPos().x && gameLevel.getEnemiesRanged().at(i)->getTaggedByAttack() == true) {
							// do nothing
						}
						// if the player hits an enemy on the left while facing right
						else {
							m_player.setHealth(-gameLevel.getEnemiesRanged().at(i)->damageDealt());
							m_player.setAttacking(false);
							m_player.resetAttackDuration();
							m_player.knockback();
						}
					}
				}
			}

			// player projectile collides with enemy
			for (int j = 0; j < m_player.getProjectiles().size(); j++) {
				if (m_collisionDetector.boundingBoxCollision(m_player.getProjectiles().at(j)->getPos().x, m_player.getProjectiles().at(j)->getPos().y, m_player.getProjectiles().at(j)->getWidth(),
					m_player.getProjectiles().at(j)->getHeight(), gameLevel.getEnemiesRanged().at(i)->getPos().x, gameLevel.getEnemiesRanged().at(i)->getPos().y, gameLevel.getEnemiesRanged().at(i)->getWidth(), gameLevel.getEnemiesRanged().at(i)->getHeight()) == true)
				{
					m_player.setScore(gameLevel.getEnemiesRanged().at(i)->addScore());
					gameLevel.getEnemiesRanged().at(i)->setIsAlive(false);
					gameLevel.getEnemiesRanged().at(i)->setHealth(-m_player.getProjectiles().at(j)->getDamage());

					if (gameLevel.getEnemiesRanged().at(i)->getHealth() <= 0) {
						m_player.setScore(gameLevel.getEnemiesRanged().at(i)->addScore());
						gameLevel.getEnemiesRanged().at(i)->setIsAlive(false);
					}

					m_player.getProjectiles().at(j)->setAlive(false); // projectile is no longer alive on collision with enemy
				}
			}
		}
	}

	if (gameLevel.getSpikes().empty() != true) {
		for (int i = 0; i < gameLevel.getSpikes().size(); i++) {
			gameLevel.getSpikes().at(i)->checkCollisionWithPlayer(m_player);
		}
	}

	m_player.setCollides(false);
}