
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "Menu.h"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "3rdYearProject");
	window.setFramerateLimit(60);
	sf::Font thefont;
	if (!thefont.loadFromFile("arial.ttf"))
	{
		std::cout << "WHY WONT THIS WORK" << std::endl;
	}

	Menu testMenu(thefont);
	bool exit = false;
	while (exit == false)
	{
		testMenu.update();
		testMenu.draw(window);
		window.display();
		std::cout << "Running" << std::endl;
	}
}