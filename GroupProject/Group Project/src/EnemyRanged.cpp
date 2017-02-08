#include "EnemyRanged.h"

EnemyRanged::EnemyRanged() : Enemy()
{
	m_timeSinceFire = 0;
	m_range = 400;
	m_projectiles = vector<shared_ptr<Projectile>>();
}

EnemyRanged::EnemyRanged(sf::Vector2f newPos) : Enemy(newPos)
{
	m_range = 400;
	m_timeSinceFire = 0;
	m_projectiles = vector<shared_ptr<Projectile>>();
}

void EnemyRanged::FireProjectile(int direction)
{
	if (m_timeSinceFire > FIRERATE)
	{
		sf::Vector2f m_centre = sf::Vector2f(getPos().x + (getWidth() / 2), getPos().y + (getHeight() / 2));
 		m_projectiles.push_back(std::shared_ptr<Projectile>(new Projectile(direction, m_centre)));
		m_timeSinceFire = 0;
	}
}

void EnemyRanged::Targeting(sf::Vector2f playerPos,float playerHeight)
{


}

void EnemyRanged::Update(sf::Vector2f playerPos, float playerHeight)
{
	Targeting(playerPos, playerHeight);
}

void EnemyRanged::draw(sf::RenderWindow &window) {
	window.draw(m_sprite);
	for (int i = 0; i < m_projectiles.size(); i++)
	{
		m_projectiles.at(i)->draw(window);
	}
}

EnemyRanged::~EnemyRanged()
{

}

vector<shared_ptr<Projectile>> EnemyRanged::getProjectiles()
{
	return m_projectiles;
}

float EnemyRanged::getRange()
{
	return m_range;
}

void EnemyRanged::setRange(float newRange)
{
	m_range = newRange;
}