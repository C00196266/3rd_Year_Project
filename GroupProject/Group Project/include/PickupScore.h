#ifndef PICKUPSCORE_H
#define PICKUPSCORE_H

#include "Pickup.h"

class PickupScore : public Pickup {
public:
	int getScore();
	PickupScore(sf::Vector2f newPos);
private:
	int m_scoreValue;
};

#endif
