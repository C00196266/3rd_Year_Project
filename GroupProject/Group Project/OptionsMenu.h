#pragma once
#include "Menu.h"
#include "GameState.h"
#include <iostream>

class OptionsMenu : public Menu
{

private:
	bool isMusicOn;
public:
	OptionsMenu();
	OptionsMenu(sf::Font &thefont);
	void update(GameStates &currentGameState);
	void changeGameState(GameStates &currentGameState);
};