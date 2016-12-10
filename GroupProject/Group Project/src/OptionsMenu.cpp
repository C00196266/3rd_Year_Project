#include "OptionsMenu.h"


OptionsMenu::OptionsMenu()
{

}

OptionsMenu::OptionsMenu(sf::Font &thefont) :Menu()
{
	buttonsVector.push_back(std::shared_ptr<Button>(new Button(sf::Vector2f(600, 150), std::string("Music: On"), thefont, "assets/button.png")));
	buttonsVector.push_back(std::shared_ptr<Button>(new Button(sf::Vector2f(600, 250), std::string("Music Volume: 50"), thefont, "assets/button.png")));
	buttonsVector.push_back(std::shared_ptr<Button>(new Button(sf::Vector2f(600, 350), std::string("Sound: On"), thefont, "assets/button.png")));
	buttonsVector.push_back(std::shared_ptr<Button>(new Button(sf::Vector2f(600, 450), std::string("Sound Volume: 50"), thefont, "assets/button.png")));
	buttonsVector.push_back(std::shared_ptr<Button>(new Button(sf::Vector2f(600, 550), std::string("Return to Main Menu"), thefont, "assets/button.png")));
	buttonsVector.at(0)->setSelected(true);
}

void OptionsMenu::setButtonStrings(GameStates &previousGameState)
{
	if (previousGameState == GameStates::PauseMenu)
	{
		buttonsVector.at(4)->setString("Return to Pause Menu");
	}
	if (previousGameState == GameStates::MainMenu)
	{
		buttonsVector.at(4)->setString("Return to Main Menu");
	}
}


void OptionsMenu::update(GameStates &currentGameState, GameStates &previousGameState, shared_ptr<AudioManager> audioManager)
{
	if (keyPressTimer > minKeyPressTime)
	{
		changeSelected(audioManager);
		changeGameState(currentGameState,previousGameState, audioManager);
	}
	keyPressTimer++;
}

void OptionsMenu::changeGameState(GameStates &currentGameState, GameStates &previousGameState, shared_ptr<AudioManager> audioManager)
{
	if (m_input.keypressReturn || m_input.pressedA)
	{
		if (selectedIndex == 0)
		{
			audioManager->toggleMusic();

			if (audioManager->getMusicToggle() == true) {
				buttonsVector.at(selectedIndex)->setString("Music: On");
			}
			else {
				buttonsVector.at(selectedIndex)->setString("Music: Off");
			}

			keyPressTimer = 0;
			audioManager->playSound(AudioManager::SoundType::SELECT);
		}

		else if(selectedIndex == 2) {
			audioManager->toggleSound();

			if (audioManager->getSoundToggle() == true) {
				buttonsVector.at(selectedIndex)->setString("Sound: On");
			}
			else {
				buttonsVector.at(selectedIndex)->setString("Sound: Off");
			}
			keyPressTimer = 0;
			audioManager->playSound(AudioManager::SoundType::SELECT);
		}

		else if (selectedIndex == 4)
		{
			if (previousGameState == GameStates::MainMenu)//Change Game State to Main Menu
			{
				currentGameState = GameStates::MainMenu;
			}
			else
			{
				currentGameState = GameStates::PauseMenu;
			}
			keyPressTimer = 0;
			audioManager->playSound(AudioManager::SoundType::RETURN);
		}
	}

	if (m_input.keypressLeft || m_input.moveLeft) {
		if (selectedIndex == 1) {
			audioManager->changeMusicVolume(-5.0f);
			buttonsVector.at(selectedIndex)->setString(audioManager->showMusicVolume());
			audioManager->playSound(AudioManager::SoundType::SELECT);
		}
		if (selectedIndex == 3) {
			audioManager->changeSoundVolume(-5.0f);
			buttonsVector.at(selectedIndex)->setString(audioManager->showSoundVolume());
			audioManager->playSound(AudioManager::SoundType::SELECT);
		}
	}

	if (m_input.keypressRight || m_input.moveRight) {
		if (selectedIndex == 1) {
			audioManager->changeMusicVolume(5.0f);
			buttonsVector.at(selectedIndex)->setString(audioManager->showMusicVolume());
			audioManager->playSound(AudioManager::SoundType::SELECT);
		}
		if (selectedIndex == 3) {
			audioManager->changeSoundVolume(5.0f);
			buttonsVector.at(selectedIndex)->setString(audioManager->showSoundVolume());
			audioManager->playSound(AudioManager::SoundType::SELECT);
		}
	}
}
