#include "Button.h"

Button::Button()
{
	
}

Button::Button(sf::Vector2f pos,sf::String btnString, sf::Font &font,sf::String textureDir)
{
	//Sets Position,String and Font
	m_pos = pos;
	m_str = btnString;
	m_font = font;
	m_texture.loadFromFile(textureDir);
	init();
}


void Button::init()
{
	//Initialize Sprite
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(sf::Vector2f(1.2, 1.2));
	m_sprite.setPosition(m_pos);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);

	//Initialize Text
	m_text.setString(m_str);
	m_text.setFont(m_font);
	m_text.setCharacterSize(20);
	m_text.setPosition(m_pos); 
	m_text.setOrigin(
		(m_sprite.getGlobalBounds().width / 2),
		(m_sprite.getGlobalBounds().height / 2)-(m_text.getGlobalBounds().height / 2)
		);
	m_text.setFillColor(sf::Color::Green);
	setSelected(false);
}

void Button::update()
{

}

void Button::draw(sf::RenderWindow &window)
{
	window.draw(m_sprite);
	window.draw(m_text);
}

void Button::setSelected(bool isSelected)
{
	m_isSelected = isSelected;
	if (m_isSelected == false)
	{
		m_sprite.setColor(sf::Color(128, 128, 128, 170));
		m_text.setFillColor(sf::Color(255, 255, 255, 170));
	}
	else
	{
		m_sprite.setColor(sf::Color(255, 255, 255, 200));
		m_text.setFillColor(sf::Color(255, 255, 255, 255));
	}
}

void Button::setString(std::string newStr)
{
	m_str = newStr;
	m_text.setString(m_str);
}
