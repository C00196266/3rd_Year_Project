

#include "GameStateManager.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "3rdYearProject");
	window.setFramerateLimit(60);
	sf::Font thefont;
	if (!thefont.loadFromFile("arial.ttf"))
	{
		std::cout << "Font failed to Load" << std::endl;
	}
	GameStateManager gameManger(thefont);
	bool exit = false;
	while (exit == false)
	{
		window.clear();
		exit = gameManger.gameLoop(window);
		window.display();
	}
}