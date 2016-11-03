#include "Menu.h"

Menu::Menu()
{
	selectedIndex = 0;
	keyPressTimer = 0;
}

/*
Menu::Menu(sf::Font &thefont)
{
	//Test Menu

}
*/
void Menu::changeSelected()
{
	m_input.getButtonPressed();

	if (m_input.keypressUp|| m_input.moveUp)
	{
		if (selectedIndex > 0)
		{
			buttonsVector.at(selectedIndex)->setSelected(false);
			selectedIndex--;
			buttonsVector.at(selectedIndex)->setSelected(true);
		}
		else
		{
			buttonsVector.at(selectedIndex)->setSelected(false);
			selectedIndex = buttonsVector.size() - 1;
			buttonsVector.at(selectedIndex)->setSelected(true);
		}
		keyPressTimer = 0;
	}
	else if (m_input.keypressDown || m_input.moveDown)
	{
		if ((selectedIndex + 1) < buttonsVector.size())
		{
			buttonsVector.at(selectedIndex)->setSelected(false);
			selectedIndex++;
			buttonsVector.at(selectedIndex)->setSelected(true);
		}
		else
		{
			buttonsVector.at(selectedIndex)->setSelected(false);
			selectedIndex = 0;
			buttonsVector.at(selectedIndex)->setSelected(true);
		}
		keyPressTimer = 0;
	}			
}

void Menu::draw(sf::RenderWindow &window)
{
		for (int i = 0; i < buttonsVector.size(); i++)
		{
			buttonsVector.at(i)->draw(window);
		}
}

void Menu::update()
{
	if (keyPressTimer > minKeyPressTime)
	{
		changeSelected();
	}
	keyPressTimer++;
}