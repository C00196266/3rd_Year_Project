#include "Enemy.h"

Enemy::Enemy() {
	m_pos = sf::Vector2f(100.0f, 100.0f);

	if (!m_image.loadFromFile("assets/tempEnemy.png")) {
		// give error
	}

	if (m_texture.loadFromImage(m_image)) {
		// give error
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_pos);

	m_width = m_texture.getSize().x;
	m_height = m_texture.getSize().y;

	m_isAlive = true;

	m_scoreValue = 400;

	m_damage = 10;

	m_health = 20;

	m_taggedByAttack = false;
}

Enemy::Enemy(sf::Vector2f setPos) {
	m_pos = setPos;

	if (!m_image.loadFromFile("assets/tempEnemy.png")) {
		// give error
	}

	if (m_texture.loadFromImage(m_image)) {
		// give error
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_pos);

	m_width = m_texture.getSize().x;
	m_height = m_texture.getSize().y;

	m_isAlive = true;

	m_scoreValue = 400;

	m_damage = 10;

	m_health = 20;

	m_taggedByAttack = false;
}

void Enemy::draw(sf::RenderWindow &window) {
	window.draw(m_sprite);
}

sf::Vector2f Enemy::getPos() {
	return m_pos;
}

float Enemy::getWidth() {
	return m_width;
}

float Enemy::getHeight() {
	return m_height;
}

bool Enemy::getIsAlive() {
	return m_isAlive;
}

void Enemy::setIsAlive(bool alive) {
	m_isAlive = alive;
}

int Enemy::damageDealt() {
	return m_damage;
}

int Enemy::addScore() {
	return m_scoreValue;
}

int Enemy::getHealth() {
	return m_health;
}

void Enemy::setHealth(int value) {
	m_health += value;
}

bool Enemy::getTaggedByAttack() {
	return m_taggedByAttack;
}

void Enemy::setTaggedByAttack(bool tagged) {
	m_taggedByAttack = tagged;
}