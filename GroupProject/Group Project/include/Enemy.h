#ifndef ENEMY_H
#define ENEMY_H

#include "stdafx.h"

class Enemy {
public:
	Enemy();

	Enemy(sf::Vector2f newPos);

	void draw(sf::RenderWindow &window);

	//void update();

	sf::Vector2f getPos();

	float getWidth();

	float getHeight();

	bool getIsAlive();

	void setIsAlive(bool alive);

	int damageDealt();

	int addScore();

private:
	sf::Vector2f m_pos;

	float m_width;

	float m_height;

	bool m_isAlive;

	// damage dealt to the players when colliding with the enemy
	int m_damage;

	// score rewarded to the player for killing an enemy
	int m_scoreValue;

	sf::Image m_image;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};

#endif
