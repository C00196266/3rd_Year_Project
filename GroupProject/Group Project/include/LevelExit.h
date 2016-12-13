#pragma once
#include "stdafx.h"

class LevelExit
{
public:
	LevelExit();
	LevelExit(sf::Vector2f pos,int nextLevel);
	void draw(sf::RenderWindow & window);
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	int getNextLevel();

private:
	sf::Vector2f m_pos;
	sf::Vector2f m_size;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Image m_image;
	int m_nextLevel;
};
