#include "OptionsMenu.h"


OptionsMenu::OptionsMenu()
{

}

OptionsMenu::OptionsMenu(sf::Font &thefont) :Menu()
{
	buttonsVector.push_back(std::shared_ptr<Button>(new Button(sf::Vector2f(500, 200), std::string("Turn Music Off"), thefont, "assets/button.png")));
	buttonsVector.push_back(std::shared_ptr<Button>(new Button(sf::Vector2f(500, 300), std::string("Return to Main Menu"), thefont, "assets/button.png")));
	buttonsVector.at(0)->setSelected(true);
	isMusicOn = true;
}


void OptionsMenu::update(GameStates &currentGameState)
{
	if (keyPressTimer > minKeyPressTime)
	{
		changeSelected();
		changeGameState(currentGameState);
	}
	keyPressTimer++;
}

void OptionsMenu::changeGameState(GameStates &currentGameState)
{
	if (m_input.keypressReturn || m_input.pressedA)
	{
		if (selectedIndex == 0)
		{
			//Will Turn Music off
			//Music Not Yet Implemented
			if (isMusicOn == true)
			{
				isMusicOn = false;
				buttonsVector.at(selectedIndex)->setString("Turn Music On");
			}
			else
			{
				isMusicOn = true;
				buttonsVector.at(selectedIndex)->setString("Turn Music Off");
			}
			keyPressTimer = 0;
		}
		else
		{
			//Change Game State to Main Menu
			currentGameState = GameStates::MainMenu;
			keyPressTimer = 0;
		}
	}
}
