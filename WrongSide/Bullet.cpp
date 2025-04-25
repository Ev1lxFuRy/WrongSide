#include "bullet.h"
#include<iostream>

sf::Texture Bullet::bulletTexture;

Bullet::Bullet(int &damage, float &speed, int &sizeX, int &sizeY, float &scaleX,
	float &scaleY, NPC &player,bool &MouseButton, bool &bulletDir, bool bulletMoveDir) : damage(damage), speed(speed), bulletDir(bulletDir), bulletMoveDir(bulletMoveDir)
{
	if(bulletTexture.loadFromFile("../../../Assets/bullets/bullet.png"))
	{
	     std::cout << "“екстура загружена" << std::endl;
	}
	bulletSprite.setTexture(bulletTexture);

	bulletSprite.setTextureRect(sf::IntRect(0, 0, sizeX, sizeY));
	bulletSprite.setOrigin(sizeX / 2, sizeY / 2);
	bulletSprite.setScale(sf::Vector2f(scaleX, scaleY));

	// смещение пули в зависимости от режимов стрельбы и персонажа
	if (player.getSkinNumber() == "1")
	{
		if (MouseButton == 1)
		{
			bulletSprite.setPosition(player.getPosition());
		}
		else
		{
			bulletSprite.setPosition(sf::Vector2f(player.getPosition().x, player.getPosition().y + 18));
		}
	}

	if (player.getSkinNumber() == "2")
	{
		if (MouseButton == 1)
		{
			bulletSprite.setPosition(sf::Vector2f(player.getPosition().x, player.getPosition().y + 23));
		}
		else
		{
			bulletSprite.setPosition(sf::Vector2f(player.getPosition().x, player.getPosition().y + 8));
		}
	}

	if (player.getSkinNumber() == "3")
	{
		if (MouseButton == 1)
		{
			bulletSprite.setPosition(sf::Vector2f(player.getPosition().x, player.getPosition().y + 13 ));
		}
		else
		{
			bulletSprite.setPosition(sf::Vector2f(player.getPosition().x, player.getPosition().y - 2));
		}
	}
	
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(bulletSprite);
}

void Bullet::moveRight(float &time)
{
	bulletSprite.move(speed*time, 0);
}

void Bullet::moveLeft(float &time)
{
	bulletSprite.move(-speed*time, 0);
}

int Bullet::getDamage()
{
	return damage;
}

sf::FloatRect Bullet::getGlobalBounds()
{
	return bulletSprite.getGlobalBounds();
}

bool Bullet::getBulletDir()
{
	return bulletDir;
}

bool Bullet::getBulletMoveDir()
{
	return bulletMoveDir; 
}

void Bullet::changeImageDir(float& scaleX, float& scaleY)
{
	bulletSprite.setScale(-scaleX, scaleY);
}
