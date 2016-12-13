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
	void update(GameStates &currentGameState, shared_ptr<AudioManager> audioManager);
	void changeGameState(GameStates &currentGameState, shared_ptr<AudioManager> audioManager);
};
