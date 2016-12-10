#pragma once
#include "stdafx.h"
#include "Button.h"
#include "PlayerInput.h"
#include "AudioManager.h"

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
	void changeSelected(shared_ptr<AudioManager> audioManager);
	void update(shared_ptr<AudioManager> audioManager);
	void draw(sf::RenderWindow &window);
};
