#include "PickupScore.h"

PickupScore::PickupScore(sf::Vector2f newPos) : Pickup(newPos) {
	m_scoreValue = 100;
}

int PickupScore::getScore() {
	return m_scoreValue;
}