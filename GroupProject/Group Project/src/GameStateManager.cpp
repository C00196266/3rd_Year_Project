#include "GameStateManager.h"

GameStateManager::GameStateManager(sf::Font & thefont):m_mainMenu(thefont),m_optionsMenu(thefont),m_pauseMenu(thefont)
{
	currentState = GameStates::MainMenu; 
	previousState = GameStates::MainMenu;
	m_audioManager = shared_ptr<AudioManager>(new AudioManager);
}
bool GameStateManager::gameLoop(sf::RenderWindow &window,sf::View &view)
{
	if(currentState == GameStates::MainMenu)
	{
		m_mainMenu.update(currentState, m_audioManager);
		m_mainMenu.draw(window);
		if (currentState == GameStates::OptionsMenu)
		{
			previousState = GameStates::MainMenu;
			m_optionsMenu.setButtonStrings(previousState);
		}
	}
	else if(currentState == GameStates::OptionsMenu)
	{
		m_optionsMenu.update(currentState,previousState, m_audioManager);
		m_optionsMenu.draw(window);
	}
	else if (currentState == GameStates::Game)
	{
		view.reset(sf::FloatRect(view.getViewport().left, view.getViewport().top, 1280, 720));
		m_gameScreen.update(currentState,view,window, m_audioManager);
		window.setView(view);
		m_gameScreen.draw(window);
	}
	else if (currentState == GameStates::PauseMenu)
	{
		m_pauseMenu.update(currentState, m_audioManager);
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
	}
	else if (currentState == GameStates::Transition) {
		m_transition.changeText(m_gameScreen.getLevel(), m_gameScreen.getPlayer().getScore());
		view.reset(sf::FloatRect(view.getViewport().left, view.getViewport().top, 1280, 720));
		window.setView(view);
		m_transition.update(currentState);
		m_transition.draw(window);
	}

	else if (currentState == GameStates::EndGameScreen)
	{
		m_endScreen.changeScore(m_gameScreen.getPlayer().getFinalScore());
		view.reset(sf::FloatRect(view.getViewport().left, view.getViewport().top, 1280, 720));
		window.setView(view);
		m_endScreen.update(currentState);
		m_endScreen.draw(window);
	}
	else
	{
		return false;
	}
	return true;
}