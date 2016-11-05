#pragma once
#include "Menu.h"
#include "GameState.h"
#include <iostream>

class PauseMenu : public Menu
{

private:

public:
	PauseMenu();
	PauseMenu(sf::Font &thefont);
	void update(GameStates &currentGameState);
	void changeGameState(GameStates &currentGameState);
};
