#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "stdafx.h"

class AnimatedSprite {
private:
	sf::Image m_image;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	vector<sf::IntRect> m_frames;

	int m_currentFrame;

	int timeSinceLastFrame;
	int maxTimeSinceLastFrame;

public:
	AnimatedSprite();
	AnimatedSprite(string imageLocation);

	void addFrame(sf::IntRect frame);

	// updates current frame
	void update();

	// draws current frame
	void draw(sf::RenderWindow &window);
};

#endif
