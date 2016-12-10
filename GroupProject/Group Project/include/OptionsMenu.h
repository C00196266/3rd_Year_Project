#pragma once
#include "Menu.h"
#include "GameState.h"
#include <iostream>

class OptionsMenu : public Menu
{
public:
	OptionsMenu();
	OptionsMenu(sf::Font &thefont);
	void update(GameStates &currentGameState,GameStates &previousGameState, shared_ptr<AudioManager> audioManager);
	void changeGameState(GameStates &currentGameState,GameStates &previousGameState, shared_ptr<AudioManager> audioManager);
	void setButtonStrings(GameStates &previousGameState);
};