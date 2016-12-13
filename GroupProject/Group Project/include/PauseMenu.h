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
	void update(GameStates &currentGameState, shared_ptr<AudioManager> audioManager);
	void changeGameState(GameStates &currentGameState, shared_ptr<AudioManager> audioManager);
};
