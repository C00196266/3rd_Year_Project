
#include "MainMenu.h"


MainMenu::MainMenu()
{

}


MainMenu::MainMenu(sf::Font &thefont):Menu()
{
	buttonsVector.push_back(std::shared_ptr<Button>(new Button(sf::Vector2f(600, 225), std::string("Play Game"), thefont, "assets/button.png")));
	buttonsVector.push_back(std::shared_ptr<Button>(new Button(sf::Vector2f(600, 325), std::string("Options"), thefont, "assets/button.png")));
	buttonsVector.push_back(std::shared_ptr<Button>(new Button(sf::Vector2f(600, 425), std::string("Exit"), thefont, "assets/button.png")));
	buttonsVector.at(0)->setSelected(true);
}


void MainMenu::update(GameStates &currentGameState, shared_ptr<AudioManager> audioManager)
{
	if (keyPressTimer > minKeyPressTime)
	{
		changeSelected(audioManager);
		changeGameState(currentGameState, audioManager);
	}
	keyPressTimer++;
}

void MainMenu::changeGameState(GameStates &currentGameState, shared_ptr<AudioManager> audioManager)
{
	if (m_input.keypressReturn || m_input.pressedA)
	{
		if (selectedIndex == 0)
		{
			//Change Game State to Play Game
			currentGameState = GameStates::Transition;
			keyPressTimer = 0;
			audioManager->playMusic(AudioManager::CurrentMusic::LEVEL);
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
		audioManager->playSound(AudioManager::SoundType::SELECT);
	}
}
