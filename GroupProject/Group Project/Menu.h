#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <memory>
#include "Button.h"

class Menu
{
private:

protected:
	std::vector<std::shared_ptr<Button>> buttonsVector;
	int selectedIndex;
	int keyPressTimer;
	const int minKeyPressTime = 10;
public:
	Menu();
	void changeSelected();
	void update();
	void draw(sf::RenderWindow &window);
};
