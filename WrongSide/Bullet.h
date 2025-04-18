#pragma once

#include<SFML/Graphics.hpp>
#include "NPC.h"

class Bullet
{
	static sf::Texture bulletTexture;
	sf::Sprite bulletSprite;

	float speed;
	int damage;
	bool bulletDir = 1;

public:

	Bullet(int &damage, float &speed, int& sizeX, int &sizeY, float &scaleX, float &scaleY, NPC &player, bool &direction);

	void Draw(sf::RenderWindow& window);

	void moveRight(float& time);

	void moveLeft(float& time);
	
	int getDamage();

	sf::FloatRect getGlobalBounds();

	bool getBulletDir();

	void changeImageDir(float &scaleX, float &scaleY);
};

