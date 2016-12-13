#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite() {
	if (!m_image.loadFromFile("assets/Player.png")) {
		// give error
	}

	if (m_texture.loadFromImage(m_image)) {
		// give error
	}
	m_sprite.setTexture(m_texture);

	m_currentFrame = 0;
}

AnimatedSprite::AnimatedSprite(string spriteSheet) {
	if (!m_image.loadFromFile(spriteSheet)) {
		// give error
	}

	m_currentFrame = 0;
}

void AnimatedSprite::addFrame(sf::IntRect frame) {
	m_frames.push_back(frame);
}

void AnimatedSprite::update() {
	if (1 > maxTimeSinceLastFrame) {
		m_currentFrame++;
		if (m_currentFrame < m_frames.size()) {
			m_currentFrame = 0;
		}
		//m_texture.
		//m_sprite.setTexture();
	}
}

void AnimatedSprite::draw(sf::RenderWindow &window) {
	window.draw(m_sprite);
}