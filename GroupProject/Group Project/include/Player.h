#ifndef PLAYER_H
#define PLAYER_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PlayerInput.h"
#include "Projectile.h"
#include "AudioManager.h"

////////////////////////////////////////////////////////////
///	\brief Class Creates player.
///
////////////////////////////////////////////////////////////

class Player {
public:
	Player();

	void init();

	void draw(sf::RenderWindow &window);

	void update(shared_ptr<AudioManager> audioManager);

	void checkInput(shared_ptr<AudioManager> audioManager);

	sf::Vector2f getPos();

	sf::Vector2f getNextPos();

	void setPos(float x, float y);

	void setPos(sf::Vector2f newPos);

	void setNextPos(sf::Vector2f newPos);

	void setNextPos(float x, float y);

	void Player::setNextPos(int x, int y);

	void setXPos(float x);

	void setNextXPos(float x);

	void setYPos(float y);

	void setNextYPos(float y);

	float getBottom();

	float getNextBottom();

	float getRight();

	float getNextRight();

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

	bool getAttacking();

	void setAttacking(bool attacking);

	int getDamageDealt();

	void resetAttackDuration();

	void knockback();

	bool getKnockback();

	void setKnockback(bool knockback);

	bool getCollidesWithTile();
	bool getCollidesWithSpike();

	void setCollidesWithTile(bool collision);
	void setCollidesWithSpike(bool collision);

	void setInitialPos(sf::Vector2f newInitial);

	const int LEFT = 0;
	const int RIGHT = 1;

	void reset();

	void setupAnimations();

	enum AnimationStates { IDLE, WALKING, JUMPING, FALLING, ATTACKING, CASTING_SPELL };

	void changeAnimation();

private:
	PlayerInput m_input;

	int m_score;

	int m_health;
	float m_mana;

	// when the player takes damage, they have a grace period where they can't take damage again
	int m_invincibilityFrames;

	bool m_isAlive;

	float m_width;
	float m_height;

	sf::Vector2f m_pos;
	sf::Vector2f m_nextPos;
	sf::Vector2f m_initialPos;

	sf::Vector2f m_centre;

	sf::Vector2f m_velocity;

	const float m_maxSpeed = 7.5f;

	sf::Vector2f m_acceleration;

	const float gravity = 9.81f;

	bool isJumping;

	bool m_attacking;
	int m_attackDuration;

	bool m_gettingKnockedback;

	bool m_inAir;

	int m_damageDealt;

	// the amount of mana the player is required to have before shooting a projectile
	int m_fireCost;

	int direction;

	sf::Image m_image;
	sf::Texture m_texture;
	sf::Sprite m_spriteSheet;

	vector<shared_ptr<Projectile>> m_projectiles;

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

	sf::RectangleShape m_healthBar;
	sf::RectangleShape m_healthBarOutline;

	sf::RectangleShape m_manaBar;
	sf::RectangleShape m_manaBarOutline;

	bool m_collidesWithTile;	
	bool m_collidesWithSpike;

	bool m_castingSpell;
	int m_castingDuration;

	thor::Animator<sf::Sprite, std::string> m_animator;

	thor::FrameAnimation m_idleLeft;
	thor::FrameAnimation m_idleRight;
	thor::FrameAnimation m_walkingLeft;
	thor::FrameAnimation m_walkingRight;
	thor::FrameAnimation m_jumpingLeft;
	thor::FrameAnimation m_jumpingRight;
	thor::FrameAnimation m_fallingLeft;
	thor::FrameAnimation m_fallingRight;
	thor::FrameAnimation m_attackingLeft;
	thor::FrameAnimation m_attackingRight;
	thor::FrameAnimation m_castingLeft;
	thor::FrameAnimation m_castingRight;
};

#endif