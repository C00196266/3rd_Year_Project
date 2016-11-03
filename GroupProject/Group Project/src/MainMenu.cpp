
#include "MainMenu.h"


MainMenu::MainMenu()
{

}


MainMenu::MainMenu(sf::Font &thefont):Menu()
{
	buttonsVector.push_back(std::shared_ptr<Button>(new Button(sf::Vector2f(500, 100), std::string("Play Game"), thefont, "assets/button.png")));
	buttonsVector.push_back(std::shared_ptr<Button>(new Button(sf::Vector2f(500, 200), std::string("Options"), thefont, "assets/button.png")));
	buttonsVector.push_back(std::shared_ptr<Button>(new Button(sf::Vector2f(500, 300), std::string("Exit"), thefont, "assets/button.png")));
	buttonsVector.at(0)->setSelected(true);
}


void MainMenu::update(GameStates &currentGameState)
{
	if (keyPressTimer > minKeyPressTime)
	{
		changeSelected();
		changeGameState(currentGameState);
	}
	keyPressTimer++;
}

void MainMenu::changeGameState(GameStates &currentGameState)
{
		if (m_input.keypressReturn || m_input.pressedA)
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
				currentGameState = GameStates::Exit;
				keyPressTimer = 0;
			}
		}
}
