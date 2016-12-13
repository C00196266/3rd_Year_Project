#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "GameState.h"
#include "MainMenu.h"
#include "OptionsMenu.h"
#include "GameScreen.h"
#include "PauseMenu.h"
#include "AudioManager.h"
#include <iostream>

class GameStateManager
{

private:
	MainMenu m_mainMenu;
	OptionsMenu m_optionsMenu;
	GameStates currentState;
	GameScreen m_gameScreen;
	PauseMenu m_pauseMenu;
	GameStates previousState;
	shared_ptr<AudioManager> m_audioManager;
public:
	GameStateManager(sf::Font & thefont);
	bool gameLoop(sf::RenderWindow &window , sf::View &view);

};

