#include "Tile.h"

Tile::Tile() {
	m_pos = sf::Vector2f(100.0f, 100.0f);

	if (!m_image.loadFromFile("assets/tileGrass.png")) {
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

Tile::Tile(sf::Vector2f setPos,string imageLocation) {
	m_pos = setPos;

	if (!m_image.loadFromFile(imageLocation)) {
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

void Tile::draw(sf::RenderWindow &window) {
	window.draw(m_sprite);
}

sf::Vector2f Tile::getPos() {
	return m_pos;
}

float Tile::getWidth() {
	return m_width;
}

float Tile::getHeight() {
	return m_height;
}