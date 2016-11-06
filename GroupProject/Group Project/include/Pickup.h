#ifndef PICKUP_H
#define PICKUP_H

#include "stdafx.h"

class Pickup {
public:
	Pickup();

	Pickup(sf::Vector2f setPos);

	void draw(sf::RenderWindow &window);

	//void update();

	sf::Vector2f getPos();

	float getWidth();

	float getHeight();

	bool getIsAlive();

	void setIsAlive(bool alive);

protected:
	sf::Vector2f m_pos;

	float m_width;

	float m_height;

	bool m_isAlive;

	sf::Image m_image;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

private:

};

#endif
