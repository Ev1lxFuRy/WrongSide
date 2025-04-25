#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>

class Map
{
	sf::Texture textureMap;

	int const static SIZE = 10;
	sf::Sprite spriteMap[SIZE];

	int oneTileX = 16;
	int oneTileY = 16;

public:

	Map(float &mapScaleX, float &mapScaleY)
	{

		if (textureMap.loadFromFile("../../../Assets/map/DungeonTileset.png"))
		{
			std::cout << "Текстура карты загружена!!!" << std::endl;

			int countTileX = textureMap.getSize().x / oneTileX;
			int countTileY = textureMap.getSize().y / oneTileY;

			for (size_t i = 0; i < SIZE; i++)
			{ 
				spriteMap[i].setTexture(textureMap);
				spriteMap[i].setScale(mapScaleX, mapScaleY);
				spriteMap[i].setTextureRect(sf::IntRect(i * oneTileX, 0 * oneTileY, oneTileX, oneTileY));
				spriteMap[i].setPosition(sf::Vector2f(100 + i * oneTileX, 100 ));
			}
		}
	}

	void draw(sf::RenderWindow &window)
	{
		for (size_t i = 0; i < SIZE; i++)
		{
			window.draw(spriteMap[i]);
		}
	}
};

