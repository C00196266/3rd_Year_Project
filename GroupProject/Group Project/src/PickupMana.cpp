#include "PickupMana.h"

PickupMana::PickupMana(sf::Vector2f newPos) : Pickup(newPos) {
	if (!m_image.loadFromFile("assets/tempManaPickup.png")) {
		// give error
	}

	if (m_texture.loadFromImage(m_image)) {
		// give error
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_pos);

	m_manaValue = 10;
}

int PickupMana::getMana() {
	return m_manaValue;
}