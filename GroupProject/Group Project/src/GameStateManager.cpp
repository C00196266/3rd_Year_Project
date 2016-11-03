#include "GameStateManager.h"

GameStateManager::GameStateManager(sf::Font & thefont):m_mainMenu(thefont),m_optionsMenu(thefont)
{
	currentState = GameStates::MainMenu;
}
bool GameStateManager::gameLoop(sf::RenderWindow &window)
{
	if(currentState == GameStates::MainMenu)
	{
		m_mainMenu.update(currentState);
		m_mainMenu.draw(window);
		std::cout << "Main Menu Running" << std::endl;
	}
	else if(currentState == GameStates::OptionsMenu)
	{
		m_optionsMenu.update(currentState);
		m_optionsMenu.draw(window);
		std::cout << "Options Menu Running" << std::endl;
	}
	else if (currentState == GameStates::Game)
	{
		theGameScreen.update(currentState);
		theGameScreen.draw(window);
		std::cout << "Game Running" << std::endl;
	}
	else if (currentState == GameStates::PauseMenu)
	{
		std::cout << "Pause Running" << std::endl;
	}
	else if (currentState == GameStates::EndGameScreen)
	{
		std::cout << "End Game Screen Running" << std::endl;
	}
	else
	{
		return false;
	}
	return true;
}