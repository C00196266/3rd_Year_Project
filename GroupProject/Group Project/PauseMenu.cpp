#include "PauseMenu.h"


PauseMenu::PauseMenu()
{

}


PauseMenu::PauseMenu(sf::Font &thefont) :Menu()
{
	buttonsVector.push_back(std::shared_ptr<Button>(new Button(sf::Vector2f(500, 100), std::string("Resume Game"), thefont, "button.png")));
	buttonsVector.push_back(std::shared_ptr<Button>(new Button(sf::Vector2f(500, 200), std::string("Options"), thefont, "button.png")));
	buttonsVector.push_back(std::shared_ptr<Button>(new Button(sf::Vector2f(500, 300), std::string("Return to Main Menu"), thefont, "button.png")));
	buttonsVector.at(0)->setSelected(true);
}


void PauseMenu::update(GameStates &currentGameState)
{
	if (keyPressTimer > minKeyPressTime)
	{
		changeSelected();
		changeGameState(currentGameState);
	}
	keyPressTimer++;
}

void PauseMenu::changeGameState(GameStates &currentGameState)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		if (selectedIndex == 0)
		{
			//Change Game State to Play Game
			currentGameState = GameStates::Game;
			keyPressTimer = 0;
		}
		else if (selectedIndex == 1)
		{
			//Change Game State to Options
			currentGameState = GameStates::OptionsMenu;
			keyPressTimer = 0;
		}
		else
		{
			//Change Game State to Exit
			currentGameState = GameStates::MainMenu;
			keyPressTimer = 0;
		}
	}
}