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
	if (gameLevel.getEnemies().empty() != true) {
		for (int i = 0; i < gameLevel.getEnemies().size(); i++) {
			// allows enemy to be hit again by attacks from the player
			if (gameLevel.getEnemies().at(i)->getTaggedByAttack() == true && m_player.getAttacking() == false) {
				gameLevel.getEnemies().at(i)->setTaggedByAttack(false);
			}

			if (gameLevel.getEnemies().at(i)->getIsAlive() == false) {
				gameLevel.getEnemies().erase(gameLevel.getEnemies().begin() + i);
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

	for (int i = 0; i < gameLevel.getTiles().size(); i++) {
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// detects if player is standing on top of solid ground
		
		gameLevel.getTiles().at(i)->checkCollisionWithPlayer(m_player);
		
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

	if (gameLevel.getEnemies().empty() != true) {
		for (int i = 0; i < gameLevel.getEnemies().size(); i++) {
			// if the player isn't invincible after taking damage
			if (m_player.getInvincibilityFrames() == 0) {
				if (m_player.getKnockback() == true) {
					m_player.setKnockback(false);
				}
				// player collides with enemy
				if (m_player.getAttacking() == false) {
					if (m_collisionDetector.boundingBoxCollision(m_player.getPos().x, m_player.getPos().y, m_player.getWidth(), m_player.getHeight(),
						gameLevel.getEnemies().at(i)->getPos().x, gameLevel.getEnemies().at(i)->getPos().y, gameLevel.getEnemies().at(i)->getWidth(), gameLevel.getEnemies().at(i)->getHeight()) == true)
					{
						m_player.setHealth(-gameLevel.getEnemies().at(i)->damageDealt());
						m_player.knockback();
					}
				}

				else {
					// checks if the player has collided with an enemy while attacking, and is facing left
					if (m_collisionDetector.boundingBoxCollision(m_player.getPos().x - 24, m_player.getPos().y, m_player.getWidth() + 18, m_player.getHeight(),
						gameLevel.getEnemies().at(i)->getPos().x, gameLevel.getEnemies().at(i)->getPos().y, gameLevel.getEnemies().at(i)->getWidth(), gameLevel.getEnemies().at(i)->getHeight()) == true
						&& m_player.getDirection() == m_player.LEFT)
					{
						// if the player hits an enemy on the right while facing left
						if (m_player.getPos().x - 24 < gameLevel.getEnemies().at(i)->getPos().x + gameLevel.getEnemies().at(i)->getWidth() && gameLevel.getEnemies().at(i)->getTaggedByAttack() == false) {
							gameLevel.getEnemies().at(i)->setHealth(-m_player.getDamageDealt());

							// if the enemy has no more health left
							if (gameLevel.getEnemies().at(i)->getHealth() <= 0) {
								m_player.setScore(gameLevel.getEnemies().at(i)->addScore());
								gameLevel.getEnemies().at(i)->setIsAlive(false);
							}

							// if the enemy is alive
							if (gameLevel.getEnemies().at(i)->getIsAlive() == true) {
								gameLevel.getEnemies().at(i)->setTaggedByAttack(true);
							}

							audioManager->playSound(AudioManager::SoundType::PUNCH);
						}
						else if (m_player.getPos().x - 24 < gameLevel.getEnemies().at(i)->getPos().x + gameLevel.getEnemies().at(i)->getWidth() && gameLevel.getEnemies().at(i)->getTaggedByAttack() == true) {
							// do nothing
						}
						else {
							m_player.setHealth(-gameLevel.getEnemies().at(i)->damageDealt());
							m_player.setAttacking(false);
							m_player.resetAttackDuration();
							m_player.knockback();
						}
					}

					// checks if the player has collided with an enemy while attacking, and is facing right
					else if (m_collisionDetector.boundingBoxCollision(m_player.getPos().x, m_player.getPos().y, m_player.getWidth() + 24, m_player.getHeight(),
						gameLevel.getEnemies().at(i)->getPos().x, gameLevel.getEnemies().at(i)->getPos().y, gameLevel.getEnemies().at(i)->getWidth(), gameLevel.getEnemies().at(i)->getHeight()) == true
						&& m_player.getDirection() == m_player.RIGHT)
					{
						// if the player hits an enemy on the left while facing right
						if (m_player.getPos().x + m_player.getWidth() + 24 > gameLevel.getEnemies().at(i)->getPos().x && gameLevel.getEnemies().at(i)->getTaggedByAttack() == false) {
							gameLevel.getEnemies().at(i)->setHealth(-m_player.getDamageDealt());
							gameLevel.getEnemies().at(i)->setTaggedByAttack(true);

							// if the enemy has no more health left
							if (gameLevel.getEnemies().at(i)->getHealth() <= 0) {
								m_player.setScore(gameLevel.getEnemies().at(i)->addScore());
								gameLevel.getEnemies().at(i)->setIsAlive(false);
							}

							// checks if the enemy is alive
							if (gameLevel.getEnemies().at(i)->getIsAlive() == true) {
								gameLevel.getEnemies().at(i)->setTaggedByAttack(true);
							}

							audioManager->playSound(AudioManager::SoundType::PUNCH);
						}
						else if (m_player.getPos().x + m_player.getWidth() + 24 > gameLevel.getEnemies().at(i)->getPos().x && gameLevel.getEnemies().at(i)->getTaggedByAttack() == true) {
							// do nothing
						}
						// if the player hits an enemy on the left while facing right
						else {
							m_player.setHealth(-gameLevel.getEnemies().at(i)->damageDealt());
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
					m_player.getProjectiles().at(j)->getHeight(), gameLevel.getEnemies().at(i)->getPos().x, gameLevel.getEnemies().at(i)->getPos().y, gameLevel.getEnemies().at(i)->getWidth(), gameLevel.getEnemies().at(i)->getHeight()) == true)
				{
					m_player.setScore(gameLevel.getEnemies().at(i)->addScore());
					gameLevel.getEnemies().at(i)->setIsAlive(false);
					gameLevel.getEnemies().at(i)->setHealth(-m_player.getProjectiles().at(j)->getDamage());

					if (gameLevel.getEnemies().at(i)->getHealth() <= 0) {
						m_player.setScore(gameLevel.getEnemies().at(i)->addScore());
						gameLevel.getEnemies().at(i)->setIsAlive(false);
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