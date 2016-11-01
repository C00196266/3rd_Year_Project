#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <memory>

class Button
{
	//Set Texture,Set Position,Set Text,Set Character Size ,Set Origins
private:
	void init();
	sf::Vector2f m_pos;
	sf::Sprite m_sprite;
	std::string m_str;
	sf::Text m_text;
	sf::Texture m_texture;
	sf::Font m_font;
	bool m_isSelected;
public:
	Button();
	Button(sf::Vector2f pos, sf::String btnString, sf::Font &font,sf::String textureDir);
	void draw(sf::RenderWindow &window);
	void update();
	void setSelected(bool isSelected);
};

