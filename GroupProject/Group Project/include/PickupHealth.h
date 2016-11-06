#ifndef PICKUPHEALTH_H
#define PICKUPHEALTH_H

#include "Pickup.h"

class PickupHealth : public Pickup {
public:
	int getHealth();
	PickupHealth(sf::Vector2f newPos);
private:
	int m_healValue;
};

#endif
