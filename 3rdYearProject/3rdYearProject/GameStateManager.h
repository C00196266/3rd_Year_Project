#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "GameState.h"
#include "MainMenu.h"
#include "OptionsMenu.h"
#include <iostream>

class GameStateManager
{

private:
	MainMenu m_mainMenu;
	OptionsMenu m_optionsMenu;
	GameStates currentState;
public:
	GameStateManager(sf::Font & thefont);
	bool gameLoop(sf::RenderWindow &window);

};

