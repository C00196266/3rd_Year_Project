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