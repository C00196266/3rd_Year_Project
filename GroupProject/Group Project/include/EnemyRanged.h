#pragma once
#include "Projectile.h"
#include "Enemy.h"

class EnemyRanged : public Enemy
{
public:
	EnemyRanged();
	EnemyRanged(sf::Vector2f newPos);
	EnemyRanged(sf::Vector2f newPos,bool hasDirectionalFire);
	~EnemyRanged();

	void update(Player &player);

	//float getRange();

	//void setRange(float newRange);

	//void FireProjectile(int direction);
	//void Targeting(sf::Vector2f playerPos, float playerHeight);

	void draw(sf::RenderWindow &window);
	vector<shared_ptr<Projectile>> getProjectiles();

	void setupAnimations();

	void changeAnimation();

private:
	sf::Clock clock;
	const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f); // updates 60 times a second
	sf::Time timeSinceLastUpdate; // time between updates

	float m_range;
	float m_timeBetweenShots;
	float m_castingTime;
	bool m_allowFire;
	sf::Vector2f m_fireVel;
	vector<shared_ptr<Projectile>> m_projectiles;

	thor::Animator<sf::Sprite, std::string> m_animator;

	thor::FrameAnimation m_idleLeft;
	thor::FrameAnimation m_idleRight;
	thor::FrameAnimation m_castingLeft;
	thor::FrameAnimation m_castingRight;

	const int LEFT = 0;
	const int RIGHT = 1;

	bool m_casting;

	int m_direction;

	bool m_directionalFire;
};

