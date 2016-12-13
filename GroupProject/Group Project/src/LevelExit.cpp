#include "LevelExit.h"


LevelExit::LevelExit()
{
	if (!m_image.loadFromFile("assets/tileBase.png")) {
		// give error
	}
	if (m_texture.loadFromImage(m_image)) {
		// give error
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_pos);
	m_size.x = m_texture.getSize().x;
	m_size.y = m_texture.getSize().y;
}

LevelExit::LevelExit(sf::Vector2f pos, int nextLevel)
{
	m_pos = pos;
	if (!m_image.loadFromFile("assets/tileBase.png")) {
		// give error
	}
	if (m_texture.loadFromImage(m_image)) {
		// give error
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_pos);
	m_size.x = m_texture.getSize().x;
	m_size.y = m_texture.getSize().y;
	m_nextLevel = nextLevel;
}

void LevelExit::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

sf::Vector2f LevelExit::getPosition()
{
	return m_pos;
}

sf::Vector2f LevelExit::getSize()
{
	return m_size;
}

int LevelExit::getNextLevel()
{
	return m_nextLevel;
}

