#pragma once

#include<SFML/Graphics.hpp>

class NPC
{
	sf::Texture heroTexture;
	sf::Sprite heroSprite;

	double speed = 0.1;
	int health = 100;

	int ammo = 30;
	int syringe = 3;


	// collider

	sf::RectangleShape rec;

public:
	NPC(int& health, double& speed, int& PosiotinX, int& PositionY, int& sizeX, int& sizeY, float& scaleX, float& scaleY);

	void drawSprite(sf::RenderWindow& window);

	void setRectRight(int x, int y, float &currentFrame, int animation = 0);
	void setRectLeft(int x, int y, float& currentFrame, int animation = 0);

	void moveUp(float& time, float shiftModifier = 1);
	void moveDown(float& time, float shiftModifier = 1);
	void moveRight(float& time, float shiftModifier = 1);
	void moveLeft(float& time, float shiftModifier = 1);

	int getHealth();
	void setHealth(int health);

	int getAmmo();
	void setAmmo(int ammo);

	int getSyringe();
	void setSyringe(int syringe);

	void newColliderPosition();
	
	sf::Vector2f getPosition();

	sf::FloatRect getGlobalBounds();

	sf::FloatRect getGlobalBoundsRectangle();
};

