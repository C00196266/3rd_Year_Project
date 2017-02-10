#pragma once
#include "Projectile.h"
#include "Enemy.h"

class EnemyRanged : public Enemy
{
public:
	EnemyRanged();
	EnemyRanged(sf::Vector2f newPos);
	~EnemyRanged();

	void update(Player &player);

	//float getRange();

	//void setRange(float newRange);

	//void FireProjectile(int direction);
	//void Targeting(sf::Vector2f playerPos, float playerHeight);

	void draw(sf::RenderWindow &window);
	vector<shared_ptr<Projectile>> getProjectiles();
private:
	float m_range;
	float m_timeBetweenShots;
	bool m_allowFire;
	sf::Vector2f m_fireVel;
	vector<shared_ptr<Projectile>> m_projectiles;
	//const int LEFT = 0;
	//const int RIGHT = 1;
};

