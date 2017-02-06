#ifndef SPIKE_H
#define SPIKE_H

#include "stdafx.h"
#include "Player.h"

class Spike{
public:
	Spike();
	Spike(sf::Vector2f setPos);

	void draw(sf::RenderWindow &window);

	sf::Vector2f getPos();
	float getWidth();
	float getHeight();

	void checkCollisionWithPlayer(Player &player);

private:
	sf::Vector2f m_pos;

	sf::Image m_image;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	float m_width;
	float m_height;
};

#endif