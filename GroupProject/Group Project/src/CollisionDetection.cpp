#include "CollisionDetection.h"

CollisionDetection::CollisionDetection() {

}

bool CollisionDetection::boundingBoxCollision(float object1X, float object1Y, float object1Width, float object1Height, float object2X, float object2Y, float object2Width, float object2Height) {
	if (object1X + object1Width <= object2X || object1X >= object2X + object2Width ||
		object1Y + object1Height <= object2Y || object1Y >= object2Y + object2Height) {
		return false;
	}
	else {
		return true;
	}
}

bool CollisionDetection::boundingBoxCollision(sf::Vector2f object1pos, sf::Vector2f object1size, sf::Vector2f object2pos, sf::Vector2f object2size) {
	if (object1pos.x + object1size.x <= object2pos.x || object1pos.x >= object2pos.x + object2size.x ||
		object1pos.y + object1size.y <= object2pos.y || object1pos.y >= object2pos.y + object2size.y) 
	{
		return false;
	}
	else {
		return true;
	}
}

bool CollisionDetection::boundingBoxCollision(sf::Vector2f object1pos, float object1Width, float object1Height, sf::Vector2f object2pos, float object2Width, float object2Height) {
	if (object1pos.x + object1Width <= object2pos.x || object1pos.x >= object2pos.x + object2Width ||
		object1pos.y + object1Height <= object2pos.y || object1pos.y >= object2pos.y + object2Height)
	{
		return false;
	}
	else {
		return true;
	}
}

//bool CollisionDetection::pixelDetection() {
//	return m_collision;
//}