#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "stdafx.h"

class Projectile {
public:
	Projectile();
	Projectile(int direction, sf::Vector2f centre);
	Projectile(sf::Vector2f velocity, sf::Vector2f centre);

	void draw(sf::RenderWindow &window);

	void update();

	sf::Vector2f getPos();

	float getWidth();

	float getHeight();

	bool checkAlive();

	void setAlive(bool state);

	int getFireCost();

	void fire();

	int getDamage();

	void setVelocity(sf::Vector2f newVelocity);

private:
	sf::Vector2f m_pos;

	bool m_isAlive;

	// time to live
	int ttl;

	sf::Vector2f m_velocity;

	int m_direction;

	float m_width;
	float m_height;

	int m_damage;

	// the amount of mana the player is required to have before shooting a projectile
	int m_fireCost;

	sf::Vector2f m_center;

	sf::Image m_image;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	const int LEFT = 0;
	const int RIGHT = 1;
};

#endif