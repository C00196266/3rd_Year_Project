#include "GameEntryPoint.h"

int main() {
	bool running = true;

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Group Project");

	GameScreen theGameScreen;

	// The main loop - ends as soon as the window is closed
	while (running == true) {
		while (window.isOpen()) {
			// Event processing
			sf::Event event;
			while (window.pollEvent(event))
			{
				// Request for closing the window
				if (event.type == sf::Event::Closed) {
					window.close();
				}
			}
			window.clear(sf::Color::White);

			theGameScreen.update();
			theGameScreen.draw(window);

			// Displays contents of current frame in the window
			window.display();
		}
	}
}