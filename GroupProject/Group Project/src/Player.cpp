#include "Player.h"

Player::Player() {	
	if (!m_image.loadFromFile("assets/tempPlayer.png")) {
		// give error
	}

	if (m_texture.loadFromImage(m_image)) {
		// give error
	}

	m_playerSprite.setTexture(m_texture);	

	init();
}

void Player::init() {
	m_pos = sf::Vector2f(600, 300);

	m_playerSprite.setPosition(m_pos);

	m_width = m_texture.getSize().x;
	m_height = m_texture.getSize().y;

	m_centre = sf::Vector2f(m_pos.x + (m_width / 2), m_pos.y + (m_height / 2));

	m_inAir = true;

	isJumping = false;

	direction = RIGHT;

	m_health = 100;
	m_mana = 100;
	m_score = 0;

	m_isAlive = true;

	m_velocity = sf::Vector2f(0, 0);

	m_acceleration = sf::Vector2f(0, -gravity);

	m_fireCost = 10;

	m_invincibilityFrames = 60;

	// resets time between updates
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	clock.restart();
}

void Player::resumeGame()
{
	timeSinceLastUpdate = sf::Time::Zero;
	clock.restart();
}

void Player::update() {
	timeSinceLastUpdate += clock.restart();
	if (timeSinceLastUpdate > timePerFrame)
	{
		checkInput();

		if (m_inAir == true) {
			m_velocity.y += gravity * timeSinceLastUpdate.asSeconds();
		}
		else {
			m_velocity.y = 0;
			isJumping = false;
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

		if (m_mana < 100) {
			m_mana++;
		}
		m_inAir = true;
	}
}

void Player::draw(sf::RenderWindow &window) {
	for (int i = 0; i < m_projectiles.size(); i++) {
		m_projectiles.at(i)->draw(window);
	}
	window.draw(m_playerSprite);
}

void Player::checkInput() {
	m_input.getButtonPressed();

	// player moves right
	if (m_input.moveRight && m_velocity.x < m_maxSpeed) {
		m_velocity.x += 12.0f * timeSinceLastUpdate.asSeconds();
		direction = RIGHT;
	}
	// player moves left
	else if (m_input.moveLeft && m_velocity.x > -m_maxSpeed) {
		m_velocity.x -= 13.0f * timeSinceLastUpdate.asSeconds();
		direction = LEFT;
	}
	// player is not moving
	else {
		if (direction == LEFT) {
			m_velocity.x += 17.5f * timeSinceLastUpdate.asSeconds();

			if (m_velocity.x >= 0) {
				m_velocity.x = 0;
			}
		}
		if (direction == RIGHT) {
			m_velocity.x -= 17.5f * timeSinceLastUpdate.asSeconds();

			if (m_velocity.x <= 0) {
				m_velocity.x = 0;
			}
		}
	}
	if (isJumping == false) {
		// player jumps
		if (m_input.moveUp || m_input.pressedA) {
			m_velocity.y -= 10.0f;
			isJumping = true;
			m_inAir = true;
		}
	}

	// if the player fires with enough available mana
	if (m_input.pressedRB == true && m_mana - m_fireCost >= 0) {
		m_projectiles.push_back(shared_ptr<Projectile>(new Projectile(direction, m_centre)));
		m_mana -= m_fireCost;
	}

	// if the player is invincible after taking damage
	if (m_invincibilityFrames > 0) {
		m_invincibilityFrames--;
	}
}

int Player::getHealth() {
	return m_health;
}

void Player::setHealth(int healthVal) {
	if (m_health + healthVal > 100) {
		m_health = 100;
	}
	else if (m_health + healthVal < 0) {
		m_health = 0;
	}
	else {
		m_health += healthVal;
	}

	// if the player loses health
	if (healthVal < 0) {
		m_invincibilityFrames = 60;
	}
}

int Player::getMana() {
	return m_mana;
}

void Player::setMana(int manaVal) {
	if (m_mana + manaVal > 100) {
		m_mana = 100;
	}
	else if (m_mana + manaVal < 0) {
		m_mana = 0;
	}
	else {
		m_mana += manaVal;
	}
}

void Player::setScore(int scoreVal) {
	m_score += scoreVal;
}

sf::Vector2f Player::getPos() {
	return m_pos;
}

sf::Vector2f Player::getVel() {
	return m_velocity;
}

void Player::setVel(sf::Vector2f newVel) {
	m_velocity = newVel;
}

void Player::setPos(float x, float y) {
	m_pos.x = x;
	m_pos.y = y;
}

void Player::setPos(sf::Vector2f newPos) {
	m_pos = newPos;
}

void Player::setXPos(float x) {
	m_pos.x = x;
}

void Player::setYPos(float y) {
	m_pos.y = y;
}

float Player::getWidth() {
	return m_width;
}

float Player::getHeight() {
	return m_height;
}

bool Player::getInAir() {
	return m_inAir;
}

void Player::setInAir(bool inAir) {
	m_inAir = inAir;
}

vector<shared_ptr<Projectile>> Player::getProjectiles() {
	return m_projectiles;
}

int Player::getInvincibilityFrames() {
	return m_invincibilityFrames;
}