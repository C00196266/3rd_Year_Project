#include "playerInput.h"

PlayerInput::PlayerInput()
{
	if (!sf::Joystick::isConnected(0)) {
		// joystick number 0 is connected
	}

	buttonCount = sf::Joystick::getButtonCount(0);

	hasZ = sf::Joystick::hasAxis(0, sf::Joystick::Z);

	pressedA = false;
	pressedB = false;
	pressedY = false;
	pressedX = false;
	pressedLB = false;
	pressedRB = false;
	pressedBack = false;
	pressedStart = false;
	moveDown = false;
	moveUp = false;
	moveLeft = false;
	moveRight = false;
	allowButtonPress = true;

	timer = 0;
}

void PlayerInput::getButtonPressed() {
	// sets up the joystick
	joyX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
	joyY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

	// sets up the d-pad
	dPadX = sf::Joystick::getAxisPosition(0, sf::Joystick::PovX);
	dPadY = sf::Joystick::getAxisPosition(0, sf::Joystick::PovY);

	if (allowButtonPress == true) {
		// A is pressed
		if (sf::Joystick::isButtonPressed(0, A)) {
			pressedA = true;
			allowButtonPress = false;
		}

		// B is pressed
		if (sf::Joystick::isButtonPressed(0, B)) {
			pressedB = true;
			allowButtonPress = false;
		}

		// Y is pressed
		if (sf::Joystick::isButtonPressed(0, Y)) {
			pressedY = true;
			allowButtonPress = false;
		}

		// X is pressed
		if (sf::Joystick::isButtonPressed(0, X)) {
			pressedX = true;
			allowButtonPress = false;
		}

		// LB is pressed
		if (sf::Joystick::isButtonPressed(0, LB)) {
			pressedLB = true;
			allowButtonPress = false;
		}

		// RB is pressed
		if (sf::Joystick::isButtonPressed(0, RB)) {
			pressedRB = true;
			allowButtonPress = false;
		}


		// Back is pressed
		if (sf::Joystick::isButtonPressed(0, BACK)) {
			pressedBack = true;
			allowButtonPress = false;
		}

		// Start is pressed
		if (sf::Joystick::isButtonPressed(0, START)) {
			pressedStart = true;
		}	
	}

	else {
		if (pressedA == true) {
			pressedA = false;
		}

		if (pressedB == true) {
			pressedB = false;
		}

		if (pressedY == true) {
			pressedY = false;
		}

		if (pressedX == true) {
			pressedX = false;
		}

		if (pressedLB == true) {
			pressedLB = false;
		}

		if (pressedRB == true) {
			pressedRB = false;
		}

		if (pressedBack == true) {
			pressedBack = false;
		}

		if (pressedStart == true) {
			pressedStart = false;
		}

		// timer used for the delay between button presses, to prevent the game from reading in multiple button presses at the same time
		timer++;
		if (timer > 2) {
			timer = 0;
			allowButtonPress = true;
		}
	}

	// joystick is moved up or up on the D-pad is pressed
	if (joyY < -60 || dPadY > 99.9) {
		moveUp = true;
	}
	else {
		moveUp = false;
	}

	// joystick is moved down or down on the D-pad is pressed
	if (joyY > 60 || dPadY < -99.9) {
		moveDown = true;
	}
	else {
		moveDown = false;
	}

	// joystick is moved left or left on the D-pad is pressed
	if (joyX < -60 || dPadX < -99.9) {
		moveLeft = true;
	}
	else {
		moveLeft = false;
	}

	// joystick is moved right or right on the D-pad is pressed
	if (joyX > 60 || dPadX > 99.9) {
		moveRight = true;
	}
	else {
		moveRight = false;
	}
}