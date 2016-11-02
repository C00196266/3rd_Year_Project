#include "Player.h"

Player::Player() {	
	if (!m_image.loadFromFile("assets/tempPlayer.png")) {
		// give error
	}

	if (m_texture.loadFromImage(m_image)) {
		// give error
	}

	m_playerSprite.setTexture(m_texture);	
	
	m_pos = sf::Vector2f(600, 350);	
	
	m_playerSprite.setPosition(m_pos);

	m_width = m_texture.getSize().x;
	m_height = m_texture.getSize().y;

	m_centre = sf::Vector2f(m_pos.x + (m_width / 2), m_pos.y + (m_height /2));

	direction = RIGHT;

	m_health = 100;
	m_mana = 100;

	m_isAlive = true;

	m_velocity = sf::Vector2f(0, 0);

	m_acceleration = sf::Vector2f(0, -gravity);

	// resets time between updates
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	clock.restart();
}

void Player::update() {
	checkInput();

	timeSinceLastUpdate += clock.restart();
	if (timeSinceLastUpdate > timePerFrame)
	{
		if (m_pos.y <= 350) {
			m_velocity.y += gravity * timeSinceLastUpdate.asSeconds();
		}
		else {
			m_velocity.y = 0;
			m_pos.y = 350;
		}

		m_pos.x += m_velocity.x;
		m_pos.y += m_velocity.y;

		m_centre.x = m_pos.x + (m_width / 2);
		m_centre.y = m_pos.y + (m_height / 2);

		if (m_projectiles.empty() != true) {
			for (int i = 0; i < m_projectiles.size(); i++) {
				if (m_projectiles.at(i)->checkAlive() == false) {
					m_projectiles.erase(m_projectiles.begin() + i);
				}
				else {
					m_projectiles.at(i)->update();
				}
			}
		}
		timeSinceLastUpdate = sf::Time::Zero;
		m_playerSprite.setPosition(m_pos);
	}
}

void Player::draw(sf::RenderWindow &window) {
	for (int i = 0; i < m_projectiles.size(); i++) {
		m_projectiles.at(i)->draw(window);
	}
	window.draw(m_playerSprite);
}

int Player::getHealth() {
	return m_health;
}

int Player::getMana() {
	return m_mana;
}

void Player::checkInput() {
	m_input.getButtonPressed();

	// player moves right
	if (m_input.moveRight && m_velocity.x < 15) {
		m_velocity.x += 3.0f;
		direction = RIGHT;
	}
	// player moves left
	if (m_input.moveLeft) {
		m_velocity.x -= 3.0f;
		direction = LEFT;
	}
	//else {
	//	if (direction == LEFT) {
	//		m_velocity.x += 0.5f;

	//		if (m_velocity.x >= 0) {
	//			m_velocity.x = 0;
	//		}
	//	}
	//	if (direction == RIGHT) {
	//		m_velocity.x -= 0.5f;

	//		if (m_velocity.x <= 0) {
	//			m_velocity.x = 0;
	//		}
	//	}
	//}

	// player moves up
	if (m_input.moveUp || m_input.pressedA) {
		m_velocity.y -= 15.0f;
	}

	if (m_input.pressedRB == true) {
		m_projectiles.push_back(shared_ptr<Projectile>(new Projectile(direction, m_centre)));
	}
}