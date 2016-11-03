#pragma once
#include "Menu.h"
#include "GameState.h"
#include <iostream>

class MainMenu: public Menu
{

private:

public:
	MainMenu();
	MainMenu(sf::Font &thefont);
	void update(GameStates &currentGameState);
	void changeGameState(GameStates &currentGameState);
};
