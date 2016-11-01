#include "Menu.h"

Menu::Menu()
{

}

Menu::Menu(sf::Font &thefont)
{
	//Test Menu
	buttonsVector.push_back(std::shared_ptr<Button>(new Button(sf::Vector2f(500, 100), std::string("Test Button"), thefont, "button.png")));
	buttonsVector.push_back(std::shared_ptr<Button>(new Button(sf::Vector2f(500, 200), std::string("Test Button 2"), thefont, "button.png")));
	buttonsVector.at(0)->setSelected(true);
	selectedIndex = 0;
	keyPressTimer = 0;
}

void Menu::changeSelected()
{
	if (keyPressTimer > minKeyPressTime)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
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
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
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
	keyPressTimer++;
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
	changeSelected();
}