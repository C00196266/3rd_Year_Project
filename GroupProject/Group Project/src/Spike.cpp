#include "Spike.h"

Spike::Spike() {
	m_pos = sf::Vector2f(100.0f, 100.0f);

	if (!m_image.loadFromFile("assets/Spike.png")) {
		// give error
	}

	if (m_texture.loadFromImage(m_image)) {
		// give error
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_pos);

	m_width = m_texture.getSize().x;
	m_height = m_texture.getSize().y;
}

Spike::Spike(sf::Vector2f setPos) {
	m_pos = setPos;

	if (!m_image.loadFromFile("assets/Spike.png")) {
		// give error
	}

	if (m_texture.loadFromImage(m_image)) {
		// give error
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_pos);

	m_width = m_texture.getSize().x;
	m_height = m_texture.getSize().y;
}

void Spike::draw(sf::RenderWindow &window) {
	window.draw(m_sprite);
}

sf::Vector2f Spike::getPos() {
	return m_pos;
}

float Spike::getWidth() {
	return m_width;
}

float Spike::getHeight() {
	return m_height;
}

void Spike::checkCollisionWithPlayer(Player &player) {
	if (player.getCollides() == false) {
		if (player.getPos().x < m_pos.x + m_width && player.getRight() > m_pos.x) {
			if (player.getBottom() <= m_pos.y && player.getNextBottom() > m_pos.y && player.getPos().y < m_pos.y) {
				player.setInAir(false);
				player.setVel(sf::Vector2f(0, 0));
				player.setCollides(true);
				player.reset();
			}

			else if (player.getBottom() <= m_pos.y && player.getNextBottom() < m_pos.y && player.getPos().y < m_pos.y) {
				player.setInAir(true);
			}

			if (player.getPos().y >= m_pos.y + m_height && player.getNextPos().y < m_pos.y + m_height && player.getPos().y > m_pos.y + m_height) {
				player.setNextYPos(m_pos.y + m_height);
				player.setVel(sf::Vector2f(player.getVel().x, 0));
			}
		}
	}

	if (player.getPos().y < m_pos.y + m_height && player.getBottom() > m_pos.y) {
		if (player.getPos().x >= m_pos.x + m_width && player.getNextPos().x <= m_pos.x + m_width && player.getRight() > m_pos.x + m_width) {
			player.setNextXPos(m_pos.x + m_width);
			player.setVel(sf::Vector2f(0, player.getVel().y));
		}

		if (player.getRight() <= m_pos.x && player.getNextRight() >= m_pos.x && player.getPos().x < m_pos.x) {
			player.setNextXPos(m_pos.x - player.getWidth());
			player.setVel(sf::Vector2f(0, player.getVel().y));
		}
	}
}