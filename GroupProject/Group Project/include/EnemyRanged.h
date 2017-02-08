#pragma once
#include "Projectile.h"
#include "Enemy.h"

class EnemyRanged : public Enemy
{
public:
	EnemyRanged();
	EnemyRanged(sf::Vector2f newPos);
	~EnemyRanged();
	void FireProjectile(int direction);
	void Targeting(sf::Vector2f playerPos, float playerHeight);
	float getRange();
	void Update(sf::Vector2f playerPos, float playerHeight);
	void setRange(float newRange);
	float m_timeSinceFire;
	void draw(sf::RenderWindow &window);
	vector<shared_ptr<Projectile>> getProjectiles();
private:
	float m_range;
	const float FIRERATE = 40.0f;
	vector<shared_ptr<Projectile>> m_projectiles;
	const int LEFT = 0;
	const int RIGHT = 1;
};

