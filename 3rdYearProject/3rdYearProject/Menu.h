#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <memory>
#include "Button.h"

class Menu
{
private:
	std::vector<std::shared_ptr<Button>> buttonsVector;
	int selectedIndex;
	int keyPressTimer;
	const int minKeyPressTime = 10;
public:
	Menu();
	Menu(sf::Font &thefont);
	void changeSelected();
	void update();
	void draw(sf::RenderWindow &window);
};
