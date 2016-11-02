#ifndef PLAYER_H
#define PLAYER_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include "PlayerInput.h"
#include "Projectile.h"

////////////////////////////////////////////////////////////
///	\brief Class Creates player.
///
////////////////////////////////////////////////////////////

class Player {
public:
	Player();

	//~Player(){};

	void draw(sf::RenderWindow &window);

	void update();

	int getHealth();

	int getMana();

	void checkInput();

private:
	PlayerInput m_input;

	int m_health;
	int m_mana;

	bool m_isAlive;

	float m_width;
	float m_height;

	sf::Vector2f m_pos;

	sf::Vector2f m_centre;

	sf::Vector2f m_velocity;

	sf::Vector2f m_acceleration;

	const float gravity = 9.81f;

	int direction;

	sf::Image m_image;
	sf::Texture m_texture;
	sf::Sprite m_playerSprite;

	vector<shared_ptr<Projectile>> m_projectiles;

	const int LEFT = 0;
	const int RIGHT = 1;

	// used to apply gravity to the player
	sf::Clock clock;
	const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f); // updates 60 times a second
	sf::Time timeSinceLastUpdate; // time between updates
};

#endif