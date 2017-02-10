#ifndef ENEMY_H
#define ENEMY_H

#include "stdafx.h"
#include "Player.h"

class Enemy {
public:
	Enemy();

	Enemy(sf::Vector2f newPos);

	void draw(sf::RenderWindow &window);

	sf::Vector2f getPos();

	float getWidth();

	float getHeight();

	bool getIsAlive();

	void setIsAlive(bool alive);

	int damageDealt();

	int addScore();

	int getHealth();

	void setHealth(int value);

	bool getTaggedByAttack();

	void setTaggedByAttack(bool tag);

protected:
	sf::Vector2f m_pos;

	float m_width;

	float m_height;

	sf::Vector2f m_centre;

	bool m_isAlive;

	// damage dealt to the players when colliding with the enemy
	int m_damage;

	// score rewarded to the player for killing an enemy
	int m_scoreValue;

	int m_health;

	// boolean to stop player from hitting the same enemy more than once per attack
	bool m_taggedByAttack;

	sf::Image m_image;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};

#endif
