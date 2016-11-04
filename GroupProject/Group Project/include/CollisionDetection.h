#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include "stdafx.h"

class CollisionDetection {
public:
	CollisionDetection();

	//bool pixelDetection();
	bool boundingBoxCollision(float object1X, float object1Y, float object1Width, float object1Height, float object2X, float object2Y, float object2Width, float object2Height);
	bool boundingBoxCollision(sf::Vector2f object1pos, sf::Vector2f object1size, sf::Vector2f object2pos, sf::Vector2f object2size);
	bool boundingBoxCollision(sf::Vector2f object1pos, float object1Width, float object1Height, sf::Vector2f object2pos, float object2Width, float object2Height);

private:
};

#endif
