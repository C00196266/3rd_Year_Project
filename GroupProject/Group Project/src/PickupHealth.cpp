#include "PickupHealth.h"

PickupHealth::PickupHealth(sf::Vector2f newPos) : Pickup(newPos) {
	if (!m_image.loadFromFile("assets/hpPickup.png")) {
		// give error
	}

	if (m_texture.loadFromImage(m_image)) {
		// give error
	}

	if (!m_particleImg.loadFromFile("assets/hpParticle.png")) {
		// give error
	}

	if (!m_particleTexture.loadFromImage(m_particleImg)) {
		// give error
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_pos);

	m_healValue = 20;
}

int PickupHealth::getHealth() {
	return m_healValue;
}