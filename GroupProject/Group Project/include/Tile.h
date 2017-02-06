#ifndef TILE_H
#define TILE_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Player.h"

////////////////////////////////////////////////////////////
///	\brief Class Manages what is on the game screen and draws
/// it.
///
////////////////////////////////////////////////////////////

class Tile {
public:
	Tile();
	Tile(sf::Vector2f setPos, string imageLocation);

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