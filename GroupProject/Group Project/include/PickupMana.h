#ifndef PICKUPMANA_H
#define PICKUPMANA_H

#include "Pickup.h"

class PickupMana : public Pickup {
public:
	int getMana();
	PickupMana(sf::Vector2f newPos);
private:
	int m_manaValue;
};

#endif
