#include "Projectile.h"

Projectile::Projectile() {
	if (!m_image.loadFromFile("assets/projectile.png")) {
		// give error
	}

	if (m_texture.loadFromImage(m_image)) {
		// give error
	}
	m_width = m_texture.getSize().x;
	m_height = m_texture.getSize().y;

	m_sprite.setTexture(m_texture);

	m_pos = sf::Vector2f(-10.0f, -10.0f);

	m_velocity = sf::Vector2f(0.0f, 0.0f);

	m_isAlive = true;

	m_sprite.setPosition(m_pos);

	m_direction = LEFT;

	m_fireCost = 10;

	m_damage = 10;

	fire();
}

Projectile::Projectile(int direction, sf::Vector2f playerCentre) {
	if (!m_image.loadFromFile("assets/projectile.png")) {
		// give error
	}

	if (m_texture.loadFromImage(m_image)) {
		// give error
	}
	m_sprite.setTexture(m_texture);

	m_width = m_texture.getSize().x;
	m_height = m_texture.getSize().y;

	m_center = playerCentre;
	m_pos = sf::Vector2f(m_center.x - (m_width / 2), m_center.y - (m_height / 2));

	m_velocity = sf::Vector2f(0.0f, 0.0f);

	m_isAlive = true;

	m_sprite.setPosition(m_pos);

	m_direction = direction;

	m_fireCost = 10;

	m_damage = 10;

	fire();
}

void Projectile::update() {
	if (m_isAlive == true) {
		m_pos += m_velocity;
	}
	if (ttl <= 0) {
		m_isAlive = false;
	}
	ttl--;

	m_sprite.setPosition(m_pos);
}

void Projectile::draw(sf::RenderWindow &window) {
	window.draw(m_sprite);
}

sf::Vector2f Projectile::getPos() {
	return m_pos;
}

float Projectile::getWidth() {
	return m_width;
}

float Projectile::getHeight() {
	return m_height;
}

bool Projectile::checkAlive() {
	return m_isAlive;
}

void Projectile::setAlive(bool state) {
	m_isAlive = state;
}

int Projectile::getFireCost() {
	return m_fireCost;
}

void Projectile::fire() {
	if (m_direction == LEFT) {
		m_velocity.x = -10.0f;
	}
	else {
		m_velocity.x = 10.0f;
	}
	ttl = 100;
}

int Projectile::getDamage() {
	return m_damage;
}

