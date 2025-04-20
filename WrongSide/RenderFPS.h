#pragma once

class RenderFPS
{
	sf::Font font;
	sf::Text text;
	sf::Clock updateClock;

public:

	RenderFPS();

	void loadText(const std::string& str);

	void draw(sf::RenderWindow& window);
};

