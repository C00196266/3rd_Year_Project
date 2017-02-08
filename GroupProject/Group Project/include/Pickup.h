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

	void update(sf::Time timer);

protected:
	sf::Vector2f m_pos;
	sf::Vector2f m_initialPos;

	float m_width;

	float m_height;

	bool m_isAlive;

	sf::Image m_image;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::Image m_particleImg;
	sf::Texture m_particleTexture;
	thor::ParticleSystem m_system;
	thor::UniversalEmitter m_emitter;
	thor::ForceAffector m_gravityAffector = thor::ForceAffector(sf::Vector2f(0, 9.81f));

	float m_move;
	float m_moveRate;
	float m_currentTimeForUpdate;
	float const MAX_TIME_FOR_UPDATE = 7;

private:

};

#endif
