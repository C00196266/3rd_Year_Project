#include "GameScreen.h"

GameScreen::GameScreen() {
	m_tiles.push_back(shared_ptr<Tile>(new Tile(sf::Vector2f(900, 330))));

	for (int i = 0; i < 34; i++) {
		m_tiles.push_back(shared_ptr<Tile>(new Tile(sf::Vector2f(i * 40, 370))));
	}
	
	m_scorePickups.push_back(shared_ptr<PickupScore>(new PickupScore(sf::Vector2f(200, 350))));

	m_healthPickups.push_back(shared_ptr<PickupHealth>(new PickupHealth(sf::Vector2f(275, 350))));

	m_manaPickups.push_back(shared_ptr<PickupMana>(new PickupMana(sf::Vector2f(350, 350))));

	m_enemies.push_back(shared_ptr<Enemy>(new Enemy(sf::Vector2f(750, 350))));
}

void GameScreen::update(GameStates &currentGameState) {
	m_player.update();

	// removes any score pickups that are no longer alive
	if (m_scorePickups.empty() != true) {
		for (int i = 0; i < m_scorePickups.size(); i++) {
			if (m_scorePickups.at(i)->getIsAlive() == false) {
				m_scorePickups.erase(m_scorePickups.begin() + i);
			}
		}
	}

	// removes any health pickups that are no longer alive
	if (m_healthPickups.empty() != true) {
		for (int i = 0; i < m_healthPickups.size(); i++) {
			if (m_healthPickups.at(i)->getIsAlive() == false) {
				m_healthPickups.erase(m_healthPickups.begin() + i);
			}
		}
	}

	// removes any mana pickups that are no longer alive
	if (m_manaPickups.empty() != true) {
		for (int i = 0; i < m_manaPickups.size(); i++) {
			if (m_manaPickups.at(i)->getIsAlive() == false) {
				m_manaPickups.erase(m_manaPickups.begin() + i);
			}
		}
	}

	// removes any enemies that are no longer alive
	if (m_enemies.empty() != true) {
		for (int i = 0; i < m_enemies.size(); i++) {
			if (m_enemies.at(i)->getIsAlive() == false) {
				m_enemies.erase(m_enemies.begin() + i);
			}
		}
	}

	detectCollisions();
}

void GameScreen::draw(sf::RenderWindow &window) {
	m_player.draw(window);

	// draws tiles
	for (int i = 0; i < m_tiles.size(); i++) {
		m_tiles.at(i)->draw(window);
	}

	// draws score pick ups
	if (m_scorePickups.empty() != true) {
		for (int i = 0; i < m_scorePickups.size(); i++) {
			m_scorePickups.at(i)->draw(window);
		}
	}

	// draws health pick ups
	if (m_healthPickups.empty() != true) {
		for (int i = 0; i < m_healthPickups.size(); i++) {
			m_healthPickups.at(i)->draw(window);
		}
	}

	// draws mana pick ups
	if (m_manaPickups.empty() != true) {
		for (int i = 0; i < m_manaPickups.size(); i++) {
			m_manaPickups.at(i)->draw(window);
		}
	}

	// draws enemies
	if (m_enemies.empty() != true) {
		for (int i = 0; i < m_enemies.size(); i++) {
			m_enemies.at(i)->draw(window);
		}
	}
}

void GameScreen::detectCollisions() {
	for (int i = 0; i < m_tiles.size(); i++) {
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// detects if player is standing on top of solid ground
		if (m_collisionDetector.boundingBoxCollisionTop(m_player.getPos().x, m_player.getPos().y, m_player.getWidth(), m_player.getHeight(), 
			m_tiles.at(i)->getPos().x, m_tiles.at(i)->getPos().y, m_tiles.at(i)->getWidth()) == true) 
		{
			m_player.setInAir(false);
			m_player.setYPos(m_tiles.at(i)->getPos().y - m_player.getHeight());
			break;
		}
		else {
			m_player.setInAir(true);
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (m_player.getProjectiles().empty() != true) {
			for (int j = 0; j < m_player.getProjectiles().size(); j++) {
				// if the bullet collides with the terrain
				if (m_collisionDetector.boundingBoxCollision(m_player.getProjectiles().at(j)->getPos().x, m_player.getProjectiles().at(j)->getPos().y, m_player.getProjectiles().at(j)->getWidth(),
					m_player.getProjectiles().at(j)->getHeight(), m_tiles.at(i)->getPos().x, m_tiles.at(i)->getPos().y, m_tiles.at(i)->getWidth(), m_tiles.at(i)->getHeight()) == true)
				{
					m_player.getProjectiles().at(j)->setAlive(false);
				}
			}
		}
	}

	// player collides with score pickup
	if (m_scorePickups.empty() != true) {
		for (int i = 0; i < m_scorePickups.size(); i++) {
			if (m_collisionDetector.boundingBoxCollision(m_player.getPos().x, m_player.getPos().y, m_player.getWidth(), m_player.getHeight(), 
				m_scorePickups.at(i)->getPos().x, m_scorePickups.at(i)->getPos().y, m_scorePickups.at(i)->getWidth(), m_scorePickups.at(i)->getHeight()) ==true)
			{
				m_player.setScore(m_scorePickups.at(i)->getScore());
				m_scorePickups.at(i)->setIsAlive(false);
			}
		}
	}

	// player collides with health pickup
	if (m_healthPickups.empty() != true) {
		for (int i = 0; i < m_healthPickups.size(); i++) {
			if (m_collisionDetector.boundingBoxCollision(m_player.getPos().x, m_player.getPos().y, m_player.getWidth(), m_player.getHeight(),
				m_healthPickups.at(i)->getPos().x, m_healthPickups.at(i)->getPos().y, m_healthPickups.at(i)->getWidth(), m_healthPickups.at(i)->getHeight()) == true)
			{
				m_player.setHealth(m_healthPickups.at(i)->getHealth());
				m_healthPickups.at(i)->setIsAlive(false);
			}
		}
	}

	// player collides with mana pickup
	if (m_manaPickups.empty() != true) {
		for (int i = 0; i < m_manaPickups.size(); i++) {
			if (m_collisionDetector.boundingBoxCollision(m_player.getPos().x, m_player.getPos().y, m_player.getWidth(), m_player.getHeight(),
				m_manaPickups.at(i)->getPos().x, m_manaPickups.at(i)->getPos().y, m_manaPickups.at(i)->getWidth(), m_manaPickups.at(i)->getHeight()) == true)
			{
				m_player.setMana(m_manaPickups.at(i)->getMana());
				m_manaPickups.at(i)->setIsAlive(false);
			}
		}
	}

	if (m_enemies.empty() != true) {
		for (int i = 0; i < m_enemies.size(); i++) {
			// player collides with enemy
			if (m_collisionDetector.boundingBoxCollision(m_player.getPos().x, m_player.getPos().y, m_player.getWidth(), m_player.getHeight(),
				m_enemies.at(i)->getPos().x, m_enemies.at(i)->getPos().y, m_enemies.at(i)->getWidth(), m_enemies.at(i)->getHeight()) == true)
			{
				m_player.setHealth(-m_enemies.at(i)->damageDealt());
			}

			// player projectile collides with enemy
			for (int j = 0; j < m_player.getProjectiles().size(); j++) {
				if (m_collisionDetector.boundingBoxCollision(m_player.getProjectiles().at(j)->getPos().x, m_player.getProjectiles().at(j)->getPos().y, m_player.getProjectiles().at(j)->getWidth(),
					m_player.getProjectiles().at(j)->getHeight(), m_enemies.at(i)->getPos().x, m_enemies.at(i)->getPos().y, m_enemies.at(i)->getWidth(), m_enemies.at(i)->getHeight()) == true)
				{
					m_player.setScore(m_enemies.at(i)->addScore());
					m_enemies.at(i)->setIsAlive(false);
					m_player.getProjectiles().at(j)->setAlive(false); // projectile is no longer alive on collision with enemy
				}
			}
		}
	}
}