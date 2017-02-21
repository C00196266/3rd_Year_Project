#include "EnemyRanged.h"

EnemyRanged::EnemyRanged() : Enemy()
{

}

EnemyRanged::EnemyRanged(sf::Vector2f newPos) : Enemy(newPos)
{
	if (!m_image.loadFromFile("assets/Wizard_SpriteSheet.png")) {
		// give error
	}

	if (!m_texture.loadFromImage(m_image)) {
		// give error
	}

	m_sprite.setTexture(m_texture);

	m_range = 250;
	m_direction = LEFT;
	m_pos.x -= 20;
	m_sprite.setPosition(m_pos);
	m_timeBetweenShots = 60;
	m_allowFire = false;
	m_fireVel = sf::Vector2f(-3, 0);
	m_casting = false;
	m_castingTime = 20;

	setupAnimations();
}

//void EnemyRanged::FireProjectile(int direction)
//{
//	if (m_timeSinceFire > FIRERATE)
//	{
//		sf::Vector2f m_centre = sf::Vector2f(getPos().x + (getWidth() / 2), getPos().y + (getHeight() / 2));
// 		m_projectiles.push_back(std::shared_ptr<Projectile>(new Projectile(sf::Vector2f(-2, 0), m_centre)));
//		//if (direction == 0)
//		//{
//		//	m_projectiles.at(m_projectiles.size() - 1)->setVelocity(sf::Vector2f(-2, 0));
//		//}
//		//else
//		//{
//		//	m_projectiles.at(m_projectiles.size() - 1)->setVelocity(sf::Vector2f(2, 0));
//		//}
//		m_timeSinceFire = 0;
//	}
//}

//void EnemyRanged::Targeting(sf::Vector2f playerPos,float playerHeight)
//{
//
//}

void EnemyRanged::update(Player &player)
{
	timeSinceLastUpdate += clock.restart();

	if (timeSinceLastUpdate > timePerFrame) {
		m_animator.update(sf::seconds(timeSinceLastUpdate.asSeconds()));
		m_animator.animate(m_sprite);

		// range is only horizontal - need to implement for vertical
		if (player.getRight() < m_centre.x && player.getRight() > m_centre.x - m_range) {
			if (m_direction != LEFT) {
				m_direction = LEFT;

				m_pos.x -= 20;
				m_sprite.setPosition(m_pos);
			}

			if (m_fireVel.x > 0) {
				m_fireVel.x = -3;
			}
			if (m_allowFire == false) {
				m_allowFire = true;
			}
		}
		else if (player.getPos().x >= m_centre.x && player.getPos().x < m_centre.x + m_range) {
			if (m_direction != RIGHT) {
				m_direction = RIGHT;
				m_pos.x += 20;
				m_sprite.setPosition(m_pos);
			}

			if (m_fireVel.x < 0) {
				m_fireVel.x = 3;
			}

			if (m_allowFire == false) {
				m_allowFire = true;
			}
		}
		else {
			if (m_allowFire == true) {
				m_allowFire = false;
			}
			if (m_casting == true) {
				m_casting = false;
			}
		}

		if (m_castingTime > 0) {
			m_castingTime--;
		}
		else {
			if (m_casting == true) {
				m_casting = false;
			}
		}

		if (m_timeBetweenShots > 0) {
			m_timeBetweenShots--;
		}
		else {
			if (m_allowFire == true) {
				m_projectiles.push_back(std::shared_ptr<Projectile>(new Projectile(m_fireVel, m_centre)));
				m_castingTime = 20;
				m_timeBetweenShots = 75;
				m_casting = true;
			}
		}

		if (m_projectiles.empty() != true) {
			for (int i = 0; i < m_projectiles.size(); i++) {
				if (m_projectiles.at(i)->checkAlive() == false) {
					m_projectiles.erase(m_projectiles.begin() + i);
				}
				else {
					m_projectiles.at(i)->update();
				}
			}
		}
		timeSinceLastUpdate = sf::Time::Zero;

		changeAnimation();
	}
}

void EnemyRanged::draw(sf::RenderWindow &window) {
	window.draw(m_sprite);
	for (int i = 0; i < m_projectiles.size(); i++)
	{
		if (m_projectiles.at(i)->checkAlive() == true)
		{
			m_projectiles.at(i)->draw(window);
		}
	}
}

EnemyRanged::~EnemyRanged()
{

}

vector<shared_ptr<Projectile>> EnemyRanged::getProjectiles()
{
	return m_projectiles;
}

void EnemyRanged::setupAnimations() {
	m_idleLeft.addFrame(1, sf::Rect<int>(0, 0, 28 * 2, 25 * 2));

	m_idleRight.addFrame(1, sf::Rect<int>(0, 25 * 2, 16 * 2, 25 * 2));

	m_castingLeft.addFrame(1, sf::Rect<int>(0, 55 * 2, 28 * 2, 25 * 2));
	m_castingLeft.addFrame(2, sf::Rect<int>(30 * 2, 55 * 2, 28 * 2, 25 * 2));
	m_castingLeft.addFrame(10, sf::Rect<int>(59 * 2, 55 * 2, 28 * 2, 25 * 2));

	m_castingRight.addFrame(1, sf::Rect<int>(0, 85 * 2, 26 * 2, 25 * 2));
	m_castingRight.addFrame(1, sf::Rect<int>(28 * 2, 85 * 2, 26 * 2, 25 * 2));
	m_castingRight.addFrame(1, sf::Rect<int>(64 * 2, 85 * 2, 26 * 2, 25 * 2));

	m_animator.addAnimation("ranged_idle_left", m_idleLeft, sf::seconds(1));
	m_animator.addAnimation("ranged_idle_right", m_idleRight, sf::seconds(1));
	m_animator.addAnimation("ranged_cast_right", m_castingRight, sf::seconds(1));
	m_animator.addAnimation("ranged_cast_left", m_castingLeft, sf::seconds(1));

	m_animator.playAnimation("ranged_idle_right", true);
}

void EnemyRanged::changeAnimation() {
	if (m_casting == true) {
		if (m_direction == LEFT) {
			if (m_animator.getPlayingAnimation() != "ranged_cast_left") {
				m_animator.playAnimation("ranged_cast_left", true);
			}
		}
		else {
			if (m_animator.getPlayingAnimation() != "ranged_cast_right") {
				m_animator.playAnimation("ranged_cast_right", true);
			}
		}
	}

	else {
		if (m_direction == LEFT) {
			if (m_animator.getPlayingAnimation() != "ranged_idle_left") {
				m_animator.playAnimation("ranged_idle_left", true);
			}
		}

		else {
			if (m_animator.getPlayingAnimation() != "ranged_idle_right") {
				m_animator.playAnimation("ranged_idle_right", true);
			}
		}
	}
}