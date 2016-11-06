#include "Pickup.h"

Pickup::Pickup() {
	m_pos = sf::Vector2f(100.0f, 100.0f);

	if (!m_image.loadFromFile("assets/tempPickup.png")) {
		// give error
	}

	if (m_texture.loadFromImage(m_image)) {
		// give error
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_pos);

	m_width = m_texture.getSize().x;
	m_height = m_texture.getSize().y;

	m_isAlive = true;
}

Pickup::Pickup(sf::Vector2f setPos) {
	m_pos = setPos;

	if (!m_image.loadFromFile("assets/tempPickup.png")) {
		// give error
	}

	if (m_texture.loadFromImage(m_image)) {
		// give error
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_pos);

	m_width = m_texture.getSize().x;
	m_height = m_texture.getSize().y;

	m_isAlive = true;
}

void Pickup::draw(sf::RenderWindow &window) {
	window.draw(m_sprite);
}

sf::Vector2f Pickup::getPos() {
	return m_pos;
}

float Pickup::getWidth() {
	return m_width;
}

float Pickup::getHeight() {
	return m_height;
}

bool Pickup::getIsAlive() {
	return m_isAlive;
}

void Pickup::setIsAlive(bool alive) {
	m_isAlive = alive;
}