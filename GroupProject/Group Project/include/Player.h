#ifndef PLAYER_H
#define PLAYER_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PlayerInput.h"
#include "Projectile.h"

////////////////////////////////////////////////////////////
///	\brief Class Creates player.
///
////////////////////////////////////////////////////////////

class Player {
public:
	Player();

	void init();

	void draw(sf::RenderWindow &window);

	void update();
	
	void checkInput();

	sf::Vector2f getPos();

	void setPos(float x, float y);

	void setPos(sf::Vector2f newPos);

	void setXPos(float x);

	void setYPos(float y);

	sf::Vector2f getVel();

	void setVel(sf::Vector2f newVel);

	float getWidth();

	float getHeight();

	void setHealth(int healthVal);

	int getHealth();

	void setMana(int manaVal);

	void setScore(int scoreVal);

	int getMana();

	bool getInAir();

	void setInAir(bool inAir);

	int getInvincibilityFrames();

	void resumeGame();

	int getDirection();

	vector<shared_ptr<Projectile>> getProjectiles();

private:
	PlayerInput m_input;

	int m_score;

	int m_health;
	int m_mana;

	// when the player takes damage, they have a grace period where they can't take damage again
	int m_invincibilityFrames;

	bool m_isAlive;

	float m_width;
	float m_height;

	sf::Vector2f m_pos;

	sf::Vector2f m_centre;

	sf::Vector2f m_velocity;

	const float m_maxSpeed = 7.5f;

	sf::Vector2f m_acceleration;

	const float gravity = 9.81f;

	bool isJumping;

	bool m_inAir;

	// the amount of mana the player is required to have before shooting a projectile
	int m_fireCost;

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

	sf::Text m_textHealth;
	sf::Text m_textMana;
	sf::Text m_textScore;

	sf::Font m_font;
	
	const float FIRERATE = 0.4f;
	float m_timeSinceFire;
};

#endif