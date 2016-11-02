#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML\Graphics.hpp>
#include <string>
#include <memory>

////////////////////////////////////////////////////////////
/// \brief A class that deals with drawing the buttons 
///        and the text of the buttons.
///
////////////////////////////////////////////////////////////
class Button
{
private:
	void init();//initializes Button
	sf::Vector2f m_pos;//position of the Button
	sf::Sprite m_sprite;//sprite of the Button
	std::string m_str;//string for the Buttons text
	sf::Text m_text;//text for the Button
	sf::Texture m_texture;//texture of the Button
	sf::Font m_font;//font for the Buttons text
	bool m_isSelected;//if the button is selected or not
public:
	Button();
	Button(sf::Vector2f pos, sf::String btnString, sf::Font &font,sf::String textureDir);
	void draw(sf::RenderWindow &window);
	void update();
	void setSelected(bool isSelected);
	void setString(std::string newStr);
};

