#ifndef PLAYERINPUT_H
#define PLAYERINPUT_H

#include "stdafx.h"

class PlayerInput
{
private:
	// x, y values for the position of the joystick
	float joyX;
	float joyY;

	// x, y values for the position of the d-pad
	float dPadX;
	float dPadY;

	// check how many buttons joystick has
	unsigned int buttonCount;

	// check if joystick has a Z axis
	bool hasZ;

	// timer used to have a very short delay between button presses
	int timer;

public:
	////////////////////////////////////////////////////////////
	///	\brief Enum used to differentiate the buttons on the
	/// controller.
	///
	////////////////////////////////////////////////////////////
	enum ButtonPress { A, B, X, Y, LB, RB, BACK, START };

	//enum KeyPress {W, Up, A, Left, S, Down, D, Right, Spacebar, Return, Backspace};

	////////////////////////////////////////////////////////////
	///	\brief Default constructor.
	///
	////////////////////////////////////////////////////////////
	PlayerInput();

	////////////////////////////////////////////////////////////
	///	\brief Method to check which button is pressed.
	///
	////////////////////////////////////////////////////////////
	void getButtonPressed();

	////////////////////////////////////////////////////////////
	///	\brief Checks if button is pressed.
	///
	////////////////////////////////////////////////////////////
	bool pressedA, pressedB, pressedY, pressedX, pressedLB, pressedRB, pressedBack, pressedStart;
	bool keypressA, keypressW, keypressD, keypressS, keypressLeft, keypressRight, keypressUp, keypressDown,keypressSpace, keypressReturn, keypressBackSpace;
	bool moveDown, moveUp, moveLeft, moveRight;

	////////////////////////////////////////////////////////////
	///	\brief Checks if a button has already been pressed.
	///
	////////////////////////////////////////////////////////////
	bool allowButtonPress;
};
#endif
