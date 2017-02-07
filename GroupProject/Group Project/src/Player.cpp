#include "Player.h"

Player::Player() {
	if (!m_image.loadFromFile("assets/Player_SpriteSheet.png")) {
		// give error
	}

	if (!m_texture.loadFromImage(m_image)) {
		// give error
	}

	//if (!m_texture.loadFromImage(m_image, sf::Rect<int>(0, 0, 14 * 2, 27 * 2))) {
	//	// give error
	//}

	m_spriteSheet.setTexture(m_texture);

	setupAnimations();

	init();
}

void Player::init() {
	m_pos = sf::Vector2f(80, 300);
	m_initialPos = m_pos;
	m_nextPos = m_pos;

	m_collides = false;

	m_spriteSheet.setPosition(m_pos);
	m_width = 28;
	m_height = 54;

	m_centre = sf::Vector2f(m_pos.x + (m_width / 2), m_pos.y + (m_height / 2));

	m_inAir = true;

	isJumping = false;

	m_attacking = false;
	m_attackDuration = 0;

	m_gettingKnockedback = false;

	direction = RIGHT;

	m_health = 100;
	m_mana = 100;
	m_score = 0;

	m_damageDealt = 10;

	m_timeSinceFire = 0;

	m_isAlive = true;

	m_velocity = sf::Vector2f(0, 0);

	m_acceleration = sf::Vector2f(0, -gravity);

	m_fireCost = 10;

	m_invincibilityFrames = 30;

	// resets time between updates
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	clock.restart();

	if (!m_font.loadFromFile("assets/arial.ttf"))
	{
		std::cout << "Font failed to Load" << std::endl;
	}

	m_textHealth.setString("Health: " + std::to_string(m_health));
	m_textHealth.setFont(m_font);
	m_textHealth.setCharacterSize(16);
	m_textHealth.setPosition(10, 10);
	m_textHealth.setFillColor(sf::Color::White);

	m_healthBar.setPosition(10, 10);
	m_healthBar.setFillColor(sf::Color::Red);
	m_healthBar.setSize(sf::Vector2f(200, 20));

	m_healthBarOutline.setPosition(8, 8);
	m_healthBarOutline.setFillColor(sf::Color::Black);
	m_healthBarOutline.setSize(sf::Vector2f(204, 24));

	m_textMana.setString("Mana: " + std::to_string((int)m_mana));
	m_textMana.setFont(m_font);
	m_textMana.setCharacterSize(16);
	m_textMana.setPosition(10, 40);
	m_textMana.setFillColor(sf::Color::White);

	m_manaBar.setPosition(10, 40);
	m_manaBar.setFillColor(sf::Color::Blue);
	m_manaBar.setSize(sf::Vector2f(200, 20));

	m_manaBarOutline.setPosition(8, 38);
	m_manaBarOutline.setFillColor(sf::Color::Black);
	m_manaBarOutline.setSize(sf::Vector2f(204, 24));

	m_textScore.setString("Score: " + std::to_string(m_score));
	m_textScore.setFont(m_font);
	m_textScore.setCharacterSize(24);
	m_textScore.setPosition(40, 70);
	m_textScore.setFillColor(sf::Color::White);

	m_castingSpell = false;
	m_castingDuration = 0;
}

void Player::resumeGame()
{
	timeSinceLastUpdate = sf::Time::Zero;
	clock.restart();
}

void Player::update(shared_ptr<AudioManager> audioManager) {
	timeSinceLastUpdate += clock.restart();

	if (timeSinceLastUpdate > timePerFrame)
	{
		checkInput(audioManager);

		m_animator.update(sf::seconds(timeSinceLastUpdate.asSeconds()));
		m_animator.animate(m_spriteSheet);

		m_pos = m_nextPos;

		if (m_inAir == true) {
			m_velocity.y += gravity * timeSinceLastUpdate.asSeconds();
		}
		else {
			m_velocity.y = 0;
			isJumping = false;
		}

		// player is attacking
		if (m_attacking == true) {
			//if (m_castingSpell == true) {
			//	m_castingSpell = false;
			//	m_castingDuration = 90;
			//}

			m_attackDuration--;

			if (m_attackDuration <= 0) {
				m_attacking = false;
			}
		}

		if (m_castingSpell == true) {
			m_castingDuration--;
			m_attackDuration = 0;

			if (m_castingDuration <= 0) {
				m_castingSpell = false;
			}
		}

		m_centre.x = m_pos.x + (m_width / 2);
		m_centre.y = m_pos.y + (m_height / 2);

		if (m_projectiles.empty() != true) {
			for (int i = 0; i < m_projectiles.size(); i++) {
				if (m_projectiles.at(i)->checkAlive() == false) {
					m_projectiles.erase(m_projectiles.begin() + i);
				}
				else {
					m_projectiles.at(i)->update();
				}
			}
		}

		m_textHealth.setPosition(m_pos.x - 530, m_pos.y - 378);
		m_healthBar.setPosition(m_pos.x - 588, m_pos.y - 378);
		m_healthBarOutline.setPosition(m_pos.x - 590, m_pos.y - 380);

		m_textMana.setPosition(m_pos.x - 525, m_pos.y - 348);
		m_manaBar.setPosition(m_pos.x - 588, m_pos.y - 348);
		m_manaBarOutline.setPosition(m_pos.x - 590, m_pos.y - 350);

		m_textScore.setPosition(m_pos.x + 450, m_pos.y - 380);

		m_timeSinceFire = m_timeSinceFire + timeSinceLastUpdate.asSeconds();
		timeSinceLastUpdate = sf::Time::Zero;
		m_spriteSheet.setPosition(m_pos);

		if (m_mana < 100) {
			m_mana+= 0.1f;
			m_textMana.setString("Mana: " + std::to_string((int)m_mana));
			m_manaBar.setSize(sf::Vector2f(2 * (int)m_mana, 20));
		}

		m_inAir = true;

		m_nextPos += m_velocity;
	}
	// if the player is invincible after taking damage
	if (m_invincibilityFrames > 0) {
		m_invincibilityFrames--;
	}

	changeAnimation();
}

void Player::draw(sf::RenderWindow &window) {
	for (int i = 0; i < m_projectiles.size(); i++) {
		m_projectiles.at(i)->draw(window);
	}

	window.draw(m_healthBarOutline);
	window.draw(m_healthBar);
	window.draw(m_textHealth);

	window.draw(m_manaBarOutline);
	window.draw(m_manaBar);
	window.draw(m_textMana);

	window.draw(m_textScore);

	window.draw(m_spriteSheet);
}

void Player::checkInput(shared_ptr<AudioManager> audioManager) {
	m_input.getButtonPressed();

	// player moves right
	if (m_input.moveRight && m_velocity.x < m_maxSpeed) {
		if (isJumping == false) {
			m_velocity.x += 40.0f * timeSinceLastUpdate.asSeconds();//12
			//changeAnimation(AnimationStates::WALKING);
		}
		else {
			m_velocity.x += 12.0f * timeSinceLastUpdate.asSeconds();
		}
		direction = RIGHT;
	}
	// player moves left
	else if (m_input.moveLeft && m_velocity.x > -m_maxSpeed) {
		if (isJumping == false) {
			m_velocity.x -= 40.0f * timeSinceLastUpdate.asSeconds();//13
			//changeAnimation(AnimationStates::JUMPING);
		}
		else {
			m_velocity.x -= 12.0f * timeSinceLastUpdate.asSeconds();
			//changeAnimation(AnimationStates::WALKING);
		}
		direction = LEFT;
	}
	// player is not moving
	else {
		if (direction == LEFT) {
			// if player is not getting knocked back by enemy
			if (m_gettingKnockedback == false) {
				m_velocity.x += 37.5f * timeSinceLastUpdate.asSeconds();

				if (m_velocity.x > 0) {
					m_velocity.x = 0;
				}
			}
			else {
				m_velocity.x -= 37.5f * timeSinceLastUpdate.asSeconds();

				if (m_velocity.x < 0) {
					m_velocity.x = 0;
				}
			}
		}
		if (direction == RIGHT) {
			// if player is not getting knocked back by enemy
			if (m_gettingKnockedback == false) {
				m_velocity.x -= 27.5f * timeSinceLastUpdate.asSeconds();

				if (m_velocity.x < 0) {
					m_velocity.x = 0;
				}
			}
			else {
				m_velocity.x += 27.5f * timeSinceLastUpdate.asSeconds();

				if (m_velocity.x > 0) {
					m_velocity.x = 0;
				}
			}
		}
	}
	if (isJumping == false) {
		// player jumps
		if (m_input.moveUp || m_input.pressedA) {
			m_velocity.y -= 7.5f;
			isJumping = true;
			m_inAir = true;
			audioManager->playSound(AudioManager::SoundType::JUMP);
		}
	}

	// if the player fires with enough available mana
	if ((m_input.pressedRB == true || m_input.keypressF == true || m_input.mouseRight == true) && m_mana - m_fireCost >= 0 && m_timeSinceFire > FIRERATE) {
		m_projectiles.push_back(shared_ptr<Projectile>(new Projectile(direction, m_centre)));
		m_mana -= m_fireCost;
		m_timeSinceFire = 0;
		m_castingSpell = true;
		m_castingDuration = 12;
	}

	// if the player tries to attack
	if ((m_input.pressedB == true || m_input.keypressE == true || m_input.mouseLeft == true) && m_attacking == false) {
		m_attacking = true;
		m_attackDuration = 18;
	}
}

int Player::getHealth() {
	return m_health;
}

void Player::setHealth(int healthVal) {
	if (m_health + healthVal > 100) {
		m_health = 100;
	}
	else if (m_health + healthVal < 0) {
		m_health = 0;
	}
	else {
		m_health += healthVal;
	}

	// if the player loses health
	if (healthVal < 0) {
		m_invincibilityFrames = 30;
	}

	m_textHealth.setString("Health: " + std::to_string(m_health));
	m_healthBar.setSize(sf::Vector2f(2 * m_health, 20));
}

int Player::getMana() {
	return m_mana;
}

void Player::setMana(int manaVal) {
	if (m_mana + manaVal > 100) {
		m_mana = 100;
	}
	else if (m_mana + manaVal < 0) {
		m_mana = 0;
	}
	else {
		m_mana += manaVal;
	}

	m_textMana.setString("Mana: " + std::to_string((int)m_mana));
	m_manaBar.setSize(sf::Vector2f(2 * m_mana, 20));
}

void Player::setScore(int scoreVal) {
	m_score += scoreVal;
	m_textScore.setString("Score: " + std::to_string(m_score));
}

sf::Vector2f Player::getPos() {
	return m_pos;
}

sf::Vector2f Player::getVel() {
	return m_velocity;
}

void Player::setVel(sf::Vector2f newVel) {
	m_velocity = newVel;
}

void Player::setPos(float x, float y) {
	m_pos.x = x;
	m_pos.y = y;
}

void Player::setPos(sf::Vector2f newPos) {
	m_pos = newPos;
}

void Player::setXPos(float x) {
	m_pos.x = x;
}

void Player::setYPos(float y) {
	m_pos.y = y;
}

float Player::getWidth() {
	return m_width;
}

float Player::getHeight() {
	return m_height;
}

bool Player::getInAir() {
	return m_inAir;
}

void Player::setInAir(bool inAir) {
	m_inAir = inAir;
}

vector<shared_ptr<Projectile>> Player::getProjectiles() {
	return m_projectiles;
}

int Player::getInvincibilityFrames() {
	return m_invincibilityFrames;
}

int Player::getDirection()
{
	return direction;
}

bool Player::getAttacking() {
	return m_attacking;
}

void Player::setAttacking(bool attacking) {
	m_attacking = attacking;
}

int Player::getDamageDealt() {
	return m_damageDealt;
}

void Player::resetAttackDuration() {
	m_attackDuration = 0;
}

void Player::knockback() {
	if (direction == LEFT) {
		m_velocity.x = 8;
	}
	else {
		m_velocity.x = -8;
	}
	m_gettingKnockedback = true;
}

bool Player::getKnockback() {
	return m_gettingKnockedback;
}

void Player::setKnockback(bool knockback) {
	m_gettingKnockedback = knockback;
}

void Player::setNextPos(sf::Vector2f newPos) {
	m_nextPos = newPos;
}

void Player::setNextPos(float x, float y) {
	m_nextPos = sf::Vector2f(x, y);
}

void Player::setNextXPos(float x) {
	m_nextPos.x = x;
}

void Player::setNextYPos(float y) {
	m_nextPos.y = y;
}

sf::Vector2f Player::getNextPos() {
	return m_nextPos;
}

float Player::getBottom() {
	return m_pos.y + m_height;
}

float Player::getNextBottom() {
	return m_nextPos.y + m_height;
}

float Player::getRight() {
	return m_pos.x + m_width;
}

float Player::getNextRight() {
	return m_nextPos.x + m_width;
}

bool Player::getCollides() {
	return m_collides;
}

void Player::setCollides(bool collision) {
	m_collides = collision;
}

void Player::reset() {
	m_pos = m_initialPos;
	m_nextPos = m_pos;

	m_textHealth.setPosition(m_pos.x - 530, m_pos.y - 378);
	m_healthBar.setPosition(m_pos.x - 588, m_pos.y - 378);
	m_healthBarOutline.setPosition(m_pos.x - 590, m_pos.y - 380);

	m_textMana.setPosition(m_pos.x - 525, m_pos.y - 348);
	m_manaBar.setPosition(m_pos.x - 588, m_pos.y - 348);
	m_manaBarOutline.setPosition(m_pos.x - 590, m_pos.y - 350);

	m_textScore.setPosition(m_pos.x + 450, m_pos.y - 380);

	setHealth(100);
	setMana(100);
	//score = 0;

	m_spriteSheet.setPosition(m_pos);
}

void Player::setInitialPos(sf::Vector2f newInitial) {
	m_initialPos = newInitial;
}

void Player::setupAnimations() {
	m_idleRight.addFrame(1, sf::Rect<int>(0, 0, 28, 54));
	
	m_idleLeft.addFrame(1, sf::Rect<int>(0, 56, 28, 54));

	m_walkingRight.addFrame(1, sf::Rect<int>(0, 112, 30, 54));
	m_walkingRight.addFrame(1, sf::Rect<int>(32, 112, 30, 54));
	m_walkingRight.addFrame(1, sf::Rect<int>(64, 112, 30, 54));
	m_walkingRight.addFrame(1, sf::Rect<int>(96, 112, 30, 54));
	m_walkingRight.addFrame(1, sf::Rect<int>(128, 112, 30, 54));
	m_walkingRight.addFrame(1, sf::Rect<int>(160, 112, 30, 54));

	m_walkingLeft.addFrame(1, sf::Rect<int>(0, 168, 30, 54));
	m_walkingLeft.addFrame(1, sf::Rect<int>(32, 168, 30, 54));
	m_walkingLeft.addFrame(1, sf::Rect<int>(64, 168, 30, 54));
	m_walkingLeft.addFrame(1, sf::Rect<int>(96, 168, 30, 54));
	m_walkingLeft.addFrame(1, sf::Rect<int>(128, 168, 30, 54));
	m_walkingLeft.addFrame(1, sf::Rect<int>(160, 168, 30, 54));

	m_jumpingRight.addFrame(1, sf::Rect<int>(4, 232, 28, 54));
	m_jumpingRight.addFrame(2, sf::Rect<int>(36, 224, 28, 62));
	m_jumpingRight.addFrame(4, sf::Rect<int>(66, 224, 28, 56));
	m_jumpingRight.addFrame(6, sf::Rect<int>(98, 226, 28, 54));

	m_fallingRight.addFrame(1, sf::Rect<int>(0, 294, 30, 52));

	m_jumpingLeft.addFrame(1, sf::Rect<int>(0, 360, 28, 54));
	m_jumpingLeft.addFrame(2, sf::Rect<int>(32, 352, 28, 62));
	m_jumpingLeft.addFrame(4, sf::Rect<int>(66, 352, 28, 56));
	m_jumpingLeft.addFrame(6, sf::Rect<int>(98, 354, 28, 54));

	m_fallingLeft.addFrame(1, sf::Rect<int>(64, 294, 30, 52));

	m_attackingRight.addFrame(2, sf::Rect<int>(0, 512, 54, 54));
	m_attackingRight.addFrame(2, sf::Rect<int>(96, 512, 66, 54));
	m_attackingRight.addFrame(2, sf::Rect<int>(192, 518, 66, 54));
	m_attackingRight.addFrame(3, sf::Rect<int>(288, 518, 66, 64));

	m_attackingLeft.addFrame(2, sf::Rect<int>(38, 416, 54, 54));
	m_attackingLeft.addFrame(2, sf::Rect<int>(122, 416, 66, 54));
	m_attackingLeft.addFrame(2, sf::Rect<int>(218, 422, 66, 54));
	m_attackingLeft.addFrame(3, sf::Rect<int>(320, 422, 60, 64));

	m_castingRight.addFrame(1, sf::Rect<int>(0, 584, 28, 54));
	m_castingRight.addFrame(2, sf::Rect<int>(30, 584, 32, 54));
	m_castingRight.addFrame(2, sf::Rect<int>(64, 584, 30, 54));
	m_castingRight.addFrame(3, sf::Rect<int>(96, 584, 30, 54));

	m_castingLeft.addFrame(1, sf::Rect<int>(0, 642, 28, 54));
	m_castingLeft.addFrame(2, sf::Rect<int>(30, 642, 32, 54));
	m_castingLeft.addFrame(2, sf::Rect<int>(64, 642, 30, 54));
	m_castingLeft.addFrame(3, sf::Rect<int>(96, 642, 30, 54));

	m_animator.addAnimation("idle_left", m_idleLeft, sf::seconds(1));
	m_animator.addAnimation("idle_right", m_idleRight, sf::seconds(1));
	m_animator.addAnimation("walk_right", m_walkingRight, sf::seconds(1));
	m_animator.addAnimation("walk_left", m_walkingLeft, sf::seconds(1));
	m_animator.addAnimation("jump_right", m_jumpingRight, sf::seconds(2));
	m_animator.addAnimation("jump_left", m_jumpingLeft, sf::seconds(2));
	m_animator.addAnimation("fall_right", m_fallingRight, sf::seconds(1));
	m_animator.addAnimation("fall_left", m_fallingLeft, sf::seconds(1));
	m_animator.addAnimation("attack_right", m_attackingRight, sf::seconds(.6f));
	m_animator.addAnimation("attack_left", m_attackingLeft, sf::seconds(.6f));
	m_animator.addAnimation("cast_right", m_castingRight, sf::seconds(.7f));
	m_animator.addAnimation("cast_left", m_castingLeft, sf::seconds(.7f));

	m_animator.playAnimation("idle_right", true);
}

void Player::changeAnimation() {
	if (m_castingSpell == false) {
		if (m_attacking == false) {
			if (m_inAir == false) {
				if (isJumping == false) {
					if (m_velocity.x > 0) {
						if (m_animator.getPlayingAnimation() != "walk_right") {
							m_animator.playAnimation("walk_right", true);
						}
					}
					else if (m_velocity.x < 0) {
						if (m_animator.getPlayingAnimation() != "walk_left") {
							m_animator.playAnimation("walk_left", true);
						}
					}
					else {
						if (direction == LEFT) {
							if (m_animator.getPlayingAnimation() != "idle_left") {
								m_animator.playAnimation("idle_left", true);
							}
						}
						else {
							if (m_animator.getPlayingAnimation() != "idle_right") {
								m_animator.playAnimation("idle_right", true);
							}
						}
					}
				}
			}
			else {
				if (m_velocity.y > 0.4f) {
					if (m_velocity.x > 0) {
						if (m_animator.getPlayingAnimation() != "fall_right") {
							m_animator.playAnimation("fall_right", true);
						}
					}
					else if (m_velocity.x < 0) {
						if (m_animator.getPlayingAnimation() != "fall_left") {
							m_animator.playAnimation("fall_left", true);
						}
					}
				}
				else if (m_velocity.y < -0.1f) {
					if (m_velocity.x > 0) {
						if (m_animator.getPlayingAnimation() != "jump_right") {
							m_animator.playAnimation("jump_right", true);
						}
					}
					else if (m_velocity.x < 0) {
						if (m_animator.getPlayingAnimation() != "jump_left") {
							m_animator.playAnimation("jump_left", true);
						}
					}
					else {
						if (direction == LEFT) {
							if (m_animator.getPlayingAnimation() != "jump_left") {
								m_animator.playAnimation("jump_left", true);
							}
						}
						else {
							if (m_animator.getPlayingAnimation() != "jump_right") {
								m_animator.playAnimation("jump_right", true);
							}
						}
					}
				}
			}
		}
		else {
			if (direction == LEFT) {
				if (m_animator.getPlayingAnimation() != "attack_left") {
					m_animator.playAnimation("attack_left", true);
				}
			}
			else {
				if (m_animator.getPlayingAnimation() != "attack_right") {
					m_animator.playAnimation("attack_right", true);
				}
			}
		}
	}
	else {
		if (direction == LEFT) {
			if (m_animator.getPlayingAnimation() != "cast_left") {
				m_animator.playAnimation("cast_left", true);
			}
		}
		else {
			if (m_animator.getPlayingAnimation() != "cast_right") {
				m_animator.playAnimation("cast_right", true);
			}
		}
	}
}