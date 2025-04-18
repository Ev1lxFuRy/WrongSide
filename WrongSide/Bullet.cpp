#include "bullet.h"
#include<iostream>

sf::Texture Bullet::bulletTexture;

Bullet::Bullet(int &damage, float &speed, int &sizeX, int &sizeY, float &scaleX, float &scaleY, NPC &player, bool& direction)
	: damage(damage), speed(speed), bulletDir(direction)
{
	if (bulletTexture.loadFromFile("../Assets/bullet_rgba.png"))
	{
		std::cout<<"file opened"<<std::endl;
	}

	bulletSprite.setTexture(bulletTexture);

	bulletSprite.setTextureRect(sf::IntRect(0, 0, sizeX, sizeY));
	bulletSprite.setOrigin(sizeX / 2, sizeY / 2);
	bulletSprite.setScale(sf::Vector2f(scaleX, scaleY));
	bulletSprite.setPosition(player.getPosition());
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

void Bullet::changeImageDir(float& scaleX, float& scaleY)
{
	bulletSprite.setScale(-scaleX, scaleY);
}
