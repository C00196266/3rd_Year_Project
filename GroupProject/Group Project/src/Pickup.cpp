#include "Pickup.h"

Pickup::Pickup() {
	m_pos = sf::Vector2f(100.0f, 100.0f);

	m_initialPos = m_pos;

	m_pos.y += (int)thor::random(0, 3);

	if (!m_image.loadFromFile("assets/scorePickup.png")) {
		// give error
	}

	if (m_texture.loadFromImage(m_image)) {
		// give error
	}

	if (!m_particleImg.loadFromFile("assets/scoreParticle.png")) {
		// give error
	}

	if (!m_particleTexture.loadFromImage(m_particleImg)) {
		// give error
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_pos);

	m_system.setTexture(m_particleTexture);

	m_width = m_texture.getSize().x;
	m_height = m_texture.getSize().y;

	m_isAlive = true;

	m_emitter.setEmissionRate(2);
	m_emitter.setParticleLifetime(thor::Distributions::uniform(sf::seconds(.5f), sf::seconds(1.75f)));
	m_emitter.setParticlePosition(thor::Distributions::circle(sf::Vector2f(m_pos.x + (m_width / 2), m_pos.y + (m_height / 2)), 2));   // Emit particles in given circle
	m_emitter.setParticleVelocity(thor::Distributions::deflect(sf::Vector2f(0, 0), 45.0f));
	m_emitter.setParticleRotation(thor::Distributions::uniform(0.f, 360.f));

	m_system.addEmitter(m_emitter);
	m_system.addAffector(m_gravityAffector);

	m_moveRate = (int)thor::random(1, 5);
	m_moveRate /= 100;
	m_move = 1;
}

Pickup::Pickup(sf::Vector2f setPos) {
	m_pos = setPos;

	m_pos.y += (int)thor::random(0, 3);

	m_initialPos = m_pos;

	if (!m_image.loadFromFile("assets/scorePickup.png")) {
		// give error
	}

	if (m_texture.loadFromImage(m_image)) {
		// give error
	}

	if (!m_particleImg.loadFromFile("assets/scoreParticle.png")) {
		// give error
	}

	if (!m_particleTexture.loadFromImage(m_particleImg)) {
		// give error
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_pos);

	m_system.setTexture(m_particleTexture);


	m_width = m_texture.getSize().x;
	m_height = m_texture.getSize().y;

	m_isAlive = true;

	m_emitter.setEmissionRate(2);
	m_emitter.setParticleLifetime(thor::Distributions::uniform(sf::seconds(.5f), sf::seconds(1.75f)));
	m_emitter.setParticlePosition(thor::Distributions::circle(sf::Vector2f(m_pos.x + (m_width / 2), m_pos.y + (m_height / 2)), 2));   // Emit particles in given circle
	m_emitter.setParticleVelocity(thor::Distributions::deflect(sf::Vector2f(0, 0), 45.0f));
	m_emitter.setParticleRotation(thor::Distributions::uniform(0.f, 360.f));

	m_system.addEmitter(m_emitter);
	m_system.addAffector(m_gravityAffector);

	m_moveRate = thor::random(1, 3);
	m_move = 0.5f;
}

void Pickup::draw(sf::RenderWindow &window) {
	window.draw(m_sprite);
	window.draw(m_system);
}

void Pickup::update(sf::Time timer) {
	m_system.update(timer);

	if (m_currentTimeForUpdate > MAX_TIME_FOR_UPDATE) {
		m_currentTimeForUpdate = 0;
		m_pos.y += m_move;
	}
	else {
		m_currentTimeForUpdate += m_moveRate;
	}

	if (m_pos.y > m_initialPos.y + 2.5f) {
		m_move = -0.5f;
	}
	else if (m_pos.y < m_initialPos.y) {
		m_move = 0.5f;
	}

	m_sprite.setPosition(m_pos);
}

sf::Vector2f Pickup::getPos() {
	return m_pos;
}

float Pickup::getWidth() {
	return m_width;
}

float Pickup::getHeight() {
	return m_height;
}

bool Pickup::getIsAlive() {
	return m_isAlive;
}

void Pickup::setIsAlive(bool alive) {
	m_isAlive = alive;
}