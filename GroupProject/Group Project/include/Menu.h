#pragma once
#include "stdafx.h"
#include "Button.h"
#include "PlayerInput.h"

class Menu
{
private:

protected:
	std::vector<std::shared_ptr<Button>> buttonsVector;
	int selectedIndex;
	int keyPressTimer;
	const int minKeyPressTime = 10;
	PlayerInput m_input;
public:
	Menu();
	void changeSelected();
	void update();
	void draw(sf::RenderWindow &window);
};
