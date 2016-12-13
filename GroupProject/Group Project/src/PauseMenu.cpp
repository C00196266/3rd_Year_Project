#include "PauseMenu.h"


PauseMenu::PauseMenu()
{

}


PauseMenu::PauseMenu(sf::Font &thefont) :Menu()
{
	buttonsVector.push_back(std::shared_ptr<Button>(new Button(sf::Vector2f(600, 225), std::string("Resume Game"), thefont, "assets/button.png")));
	buttonsVector.push_back(std::shared_ptr<Button>(new Button(sf::Vector2f(600, 325), std::string("Options"), thefont, "assets/button.png")));
	buttonsVector.push_back(std::shared_ptr<Button>(new Button(sf::Vector2f(600, 425), std::string("Return to Main Menu"), thefont, "assets/button.png")));
	buttonsVector.at(0)->setSelected(true);
}


void PauseMenu::update(GameStates &currentGameState, shared_ptr<AudioManager> audioManager)
{
	if (keyPressTimer > minKeyPressTime)
	{
		changeSelected(audioManager);
		changeGameState(currentGameState, audioManager);
	}
	keyPressTimer++;
}

void PauseMenu::changeGameState(GameStates &currentGameState, shared_ptr<AudioManager> audioManager)
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
			audioManager->playMusic(AudioManager::CurrentMusic::MENU);
		}
		audioManager->playSound(AudioManager::SoundType::SELECT);
	}
}