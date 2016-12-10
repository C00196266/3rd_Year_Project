#include "GameStateManager.h"

GameStateManager::GameStateManager(sf::Font & thefont):m_mainMenu(thefont),m_optionsMenu(thefont),m_pauseMenu(thefont)
{
	currentState = GameStates::MainMenu; 
	previousState = GameStates::MainMenu;
}
bool GameStateManager::gameLoop(sf::RenderWindow &window,sf::View &view)
{
	if(currentState == GameStates::MainMenu)
	{
		m_mainMenu.update(currentState);
		m_mainMenu.draw(window);
		if (currentState == GameStates::OptionsMenu)
		{
			previousState = GameStates::MainMenu;
			m_optionsMenu.setButtonStrings(previousState);
		}
		//std::cout << "Main Menu Running" << std::endl;
	}
	else if(currentState == GameStates::OptionsMenu)
	{
		m_optionsMenu.update(currentState,previousState);
		m_optionsMenu.draw(window);
		//std::cout << "Options Menu Running" << std::endl;
	}
	else if (currentState == GameStates::Game)
	{
		view.reset(sf::FloatRect(view.getViewport().left, view.getViewport().top, 1280, 720));
		m_gameScreen.update(currentState,view,window);
		window.setView(view);
		m_gameScreen.draw(window);
		//std::cout << "Game Running" << std::endl;
	}
	else if (currentState == GameStates::PauseMenu)
	{
		m_pauseMenu.update(currentState);
		m_pauseMenu.draw(window);
		if (currentState == GameStates::Game)
		{
			m_gameScreen.resumeGame();
		}
		if (currentState == GameStates::OptionsMenu)
		{
			previousState = GameStates::PauseMenu;
			m_optionsMenu.setButtonStrings(previousState);
		}
		//std::cout << "Pause Running" << std::endl;
	}
	else if (currentState == GameStates::EndGameScreen)
	{
		//std::cout << "End Game Screen Running" << std::endl;
	}
	else
	{
		return false;
	}
	return true;
}