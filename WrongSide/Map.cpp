#include "Map.h"

Map::Map(sf::Vector2f& mapScaleXY)
{
	if (textureMap.loadFromFile("../../../Assets/map/DungeonTileset.png"))
	{
		std::cout << "Текстура карты загружена!!!" << std::endl;

		totalTilesX = textureMap.getSize().x / oneTileX;
		totalTilesY = textureMap.getSize().y / oneTileY;

		totalTiles = totalTilesX * totalTilesY;

		tiles = new Tiles[totalTiles];

		for (size_t y = 0; y < totalTilesY; y++)
		{
			for (size_t x = 0; x < totalTilesX; x++)
			{
				int i = x + y * totalTilesX;

				tiles[i].id = i;
				tiles[i].position = sf::Vector2i(x * oneTileX, y * oneTileY); 
			}
		}
	}

	for (size_t y = 0; y < 2; y++)
	{
		for (size_t x = 0; x < 3; x++)
		{
			int i = x + y * 3;

			int index = mapNumbers[i];

			mapSprites[i].setTexture(textureMap);
			mapSprites[i].setTextureRect(sf::IntRect(tiles[index].position.x, tiles[index].position.y, oneTileX, oneTileY));
			mapSprites[i].setPosition(sf::Vector2f(x * oneTileX * mapScaleXY.x, y * oneTileY * mapScaleXY.y));
			mapSprites[i].setScale(mapScaleXY);
		}
	}

	delete []tiles;
}

void Map::draw(sf::RenderWindow& window)
{
	for (size_t i = 0; i < 6; i++)
	{
		window.draw(mapSprites[i]);
	}
}