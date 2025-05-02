#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include "Tiles.h"

class Map
{
	sf::Texture textureMap;

	Tiles *tiles;

	int oneTileX = 16;
	int oneTileY = 16;

	int totalTilesX = 0;
	int totalTilesY = 0;

	int totalTiles;

	int mapNumbers[6]
	{
		120,121,122,
		144,145,146,
	};

	sf::Sprite mapSprites[6];

public:

	Map(sf::Vector2f& mapScaleXY);

	void draw(sf::RenderWindow& window);
};

