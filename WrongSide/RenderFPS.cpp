#include<SFML/Graphics.hpp>
#include "RenderFPS.h"
#include <Windows.h>

RenderFPS::RenderFPS()
{
	font.loadFromFile("../../../Assets/fonts/Italianno-Regular.ttf");
	text.setFont(font);
	text.setPosition(sf::Vector2f(0, 0));
}

void RenderFPS::loadText(const std::string &str)
{
	if (updateClock.getElapsedTime().asSeconds() >= 0.25)
	{
		text.setString("FPS: " + str);
		updateClock.restart();
	}
}

void RenderFPS::draw(sf::RenderWindow& window)
{

	window.draw(text);
}