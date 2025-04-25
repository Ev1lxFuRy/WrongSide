#include "NPC.h"

NPC::NPC(std::string &skinNumber, int& health, double& speed, int &PosiotinX, int &PositionY, int& sizeX, int& sizeY, float& scaleX, float& scaleY) : health(health), speed(speed), skinNumber(skinNumber)
{
	heroTexture.loadFromFile("../../../Assets/charecters/soldier/animation" + skinNumber + "/soldier" + skinNumber + ".png" );
    heroSprite.setTexture(heroTexture);

    heroSprite.setTextureRect(sf::IntRect(0, 0, sizeX, sizeY));
    heroSprite.setOrigin(sizeX / 2, sizeY / 2);
    heroSprite.setScale(sf::Vector2f(scaleX, scaleY));
    heroSprite.setPosition(sf::Vector2f( PosiotinX, PositionY));

    float colliderWidth = sizeX * scaleX;
    float colliderHeight = sizeY * scaleY;

	rec.setSize(sf::Vector2f(colliderWidth , colliderHeight));
	rec.setOrigin((colliderWidth / 2), (colliderHeight / 2));
	rec.setPosition(heroSprite.getPosition());
	rec.setFillColor(sf::Color::Transparent);

    rec.setOutlineThickness(5);
    rec.setOutlineColor(sf::Color::Red);
}

void NPC::drawSprite(sf::RenderWindow& window)
{
	window.draw(rec);
	window.draw(heroSprite);
}

void NPC::setRectRight(int x, int y, float &currentFrame, int animation)
{
	heroSprite.setTextureRect(sf::IntRect(x*int(currentFrame), 0 + y * animation, x, y));
}

void NPC::setRectLeft(int x, int y, float& currentFrame, int animation)
{
	heroSprite.setTextureRect(sf::IntRect(x * int(currentFrame)+x, 0 + y * animation, -x, y));
}

void NPC::moveUp(float &time, float shiftModifier)
{
	heroSprite.move(sf::Vector2f(0, -speed*shiftModifier*time));
}

void NPC::moveDown(float& time, float shiftModifier)
{
	heroSprite.move(sf::Vector2f(0, speed*shiftModifier*time));
}

void NPC::moveRight(float& time, float shiftModifier)
{
	heroSprite.move(sf::Vector2f(speed*shiftModifier*time, 0));
}

void NPC::moveLeft(float& time, float shiftModifier)
{
	heroSprite.move(sf::Vector2f(-speed*shiftModifier*time, 0));
}

int NPC::getHealth()
{
	return health;
}

void NPC::setHealth(int health)
{
	this->health = health;
}

int NPC::getAmmo()
{
	return ammo;
}

void NPC::setAmmo(int ammo)
{
	this->ammo = ammo;
}

int NPC::getSyringe()
{
	return syringe;
}

void NPC::setSyringe(int syringe)
{
	this->syringe = syringe;
}

void NPC::newColliderPosition()
{
	rec.setPosition(heroSprite.getPosition());
}

sf::Vector2f NPC::getPosition()
{
	return heroSprite.getPosition();
}

sf::FloatRect NPC::getGlobalBounds()
{
	return heroSprite.getGlobalBounds();
}

sf::FloatRect NPC::getGlobalBoundsRectangle()
{
	return rec.getGlobalBounds();
}

std::string NPC::getSkinNumber()
{
	return skinNumber;
}