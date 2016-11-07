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
	void update(GameStates &currentGameState,GameStates &previousGameState);
	void changeGameState(GameStates &currentGameState,GameStates &previousGameState);
	void setButtonStrings(GameStates &previousGameState);
};