#include<SFML/Graphics.hpp>
#include<fstream>
#include<vector>
#include<iostream>

#include "NPC.h"
#include "Bullet.h"

using namespace std;
using namespace sf;  

// проверить как работают статик поля в классах

int main()
{

	/*---------------------------------------  HeroParameters  --------------------------------------------------*/

	int health = 100;
	double speed = 0.1;

	int sizeX = 192;
	int sizeY = 225;

	float scaleX = 0.65;
	float scaleY = 0.65;

	float shiftModifier = 1.2;

	int PositionX_player1 = 400;
	int PositionY_player2 = 600;

	int PositionX_player2 = 800;
	int PositionY_player1 = 600;

	/*---------------------------------------  BulletParameters  --------------------------------------------------*/

	int damageBullet = 50;
	float speedBullet = 0.2;
	
	int sizeXbullet = 1030;
	int sizeYbullet = 320;

	float scaleXbullet = 0.020;
	float scaleYbullet = 0.020;

	/*---------------------------------------------  Logic  --------------------------------------------------*/

	Clock clock;
	float currentFrame = 0;

	Clock fireRateClock; 
	float fireCooldown = 0.3f;

	bool gameOver = 0;
	bool isDead = 0;
	bool IsRightDir = 1;
	bool IsMoving = 0;

	/*-----------------------------------------  WindowSettings  --------------------------------------------------*/

	ContextSettings settings;

	int width = 1200;
	int height = 800;
	settings.antialiasingLevel = 8;

	RenderWindow window(VideoMode(width,height), "Hello world", Style::Default, settings);

	/*------------------------------------------  LoadObjects  --------------------------------------------------*/

	NPC player(health, speed, PositionX_player1, PositionY_player1, sizeX, sizeY, scaleX, scaleY);
	NPC player1(health, speed, PositionX_player2, PositionY_player2, sizeX, sizeY, scaleX, scaleY);

	vector<Bullet> bullet;

	/*------------------------------------------  GameLoop  -----------------------------------------------------*/

	while (window.isOpen() && !gameOver)
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time /= 300;

		IsMoving = 0;

		player.newColliderPosition();

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}

		/*--------------------------------------------  Dead  -----------------------------------------------------------*/

		if (player.getHealth() <= 0)
		{
			isDead = 1;

			currentFrame += 0.005 * time;

			if (currentFrame > 4)
			{
				currentFrame -= 4;
			}

			if (IsRightDir)
			{
				player.setRectRight(sizeX, sizeY, currentFrame);
			}
			else if (!IsRightDir)
			{
				player.setRectLeft(sizeX, sizeY, currentFrame);
			}

			gameOver = 1;
		}

		/*--------------------------------------------  Run  -----------------------------------------------------------*/

		else if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::LShift) && !isDead)
		{
			player.moveRight(time, shiftModifier);


			currentFrame += 0.005 * time;

			if (currentFrame > 8)
			{
				currentFrame -= 8;
			}

			if (IsRightDir)
			{
				player.setRectRight(sizeX, sizeY, currentFrame);
			}
			else if (!IsRightDir)
			{
				player.setRectLeft(sizeX, sizeY, currentFrame);
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::LShift) && !isDead)
		{
			player.moveLeft(time, shiftModifier);

			currentFrame += 0.005 * time;

			if (currentFrame > 8)
			{
				currentFrame -= 8;
			}

			if (IsRightDir)
			{
				player.setRectRight(sizeX, sizeY, currentFrame);
			}
			else if (!IsRightDir)
			{
				player.setRectLeft(sizeX, sizeY, currentFrame);
			}
		}

		/*------------------------------------------  CalmMove  -----------------------------------------------------------*/

		else if (Keyboard::isKeyPressed(Keyboard::D) && !isDead)
		{
			IsRightDir = 1;
			IsMoving = 1;

			player.moveRight(time);

			currentFrame += 0.005 * time;
			if (currentFrame > 7)
			{
				currentFrame -= 7;
			}

			if (IsRightDir)
			{
				player.setRectRight(sizeX, sizeY, currentFrame);
			}
			else if (!IsRightDir)
			{
				player.setRectLeft(sizeX, sizeY, currentFrame);
			}
		}
        else if (Keyboard::isKeyPressed(Keyboard::A) && !isDead)
		{
			IsMoving = 1;
			IsRightDir = 0;

			player.moveLeft(time);

			currentFrame += 0.005 * time;
			if (currentFrame > 7)
			{
				currentFrame -= 7;
			}

			if (IsRightDir)
			{
				player.setRectRight(sizeX, sizeY, currentFrame);
			}
			else if (!IsRightDir)
			{
				player.setRectLeft(sizeX, sizeY, currentFrame);
			}
		}

		/*-----------------------------------------  DontMoving  -----------------------------------------------------------*/

		else if (!IsMoving && !isDead)
		{
			currentFrame += 0.005 * time;
			if (currentFrame > 7)
			{
				currentFrame -= 7;
			}

			if (IsRightDir)
			{
				player.setRectRight(sizeX, sizeY, currentFrame);
			}
			else if (!IsRightDir)
			{
				player.setRectLeft(sizeX, sizeY, currentFrame);
			}
		}
		
		/*--------------------------------------------  Shoot  -----------------------------------------------------------*/

		else if (Mouse::isButtonPressed(Mouse::Left))
		{
			currentFrame += 0.005 * time;

			if (currentFrame > 4)
			{
				currentFrame -= 4;
			}

			if (IsRightDir)
			{
				player.setRectRight(sizeX, sizeY, currentFrame);
			}
			else if (!IsRightDir)
			{
				player.setRectLeft(sizeX, sizeY, currentFrame);
			}
		}
        else if (Mouse::isButtonPressed(Mouse::Right))
		{
			currentFrame += 0.005 * time;

			if (currentFrame > 4)
			{
				currentFrame -= 4;
			}

			if (IsRightDir)
			{
				player.setRectRight(sizeX, sizeY, currentFrame);
			}
			else if (!IsRightDir)
			{
				player.setRectLeft(sizeX, sizeY, currentFrame);
			}
		}

		/*--------------------------------------------  Reload  -----------------------------------------------------------*/

		if (player.getAmmo() <= 0 || Keyboard::isKeyPressed(Keyboard::R))
		{
			currentFrame += 0.005 * time;

			if (currentFrame > 8)
			{
				currentFrame -= 8;
			}

			if (IsRightDir)
			{
				player.setRectRight(sizeX, sizeY, currentFrame);
			}
			else if (!IsRightDir)
			{
				player.setRectLeft(sizeX, sizeY, currentFrame);
			}

			player.setAmmo(30);
		}

		/*--------------------------------------------  Healing  -----------------------------------------------------------*/

		if (Keyboard::isKeyPressed(Keyboard::F) && !isDead)
		{
			currentFrame += 0.005 * time;

			if (currentFrame > 5)
			{
				currentFrame -= 5;
			}

			if (IsRightDir)
			{
				player.setRectRight(sizeX, sizeY, currentFrame);
			}
			else if (!IsRightDir)
			{
				player.setRectLeft(sizeX, sizeY, currentFrame);
			}

			if (player.getHealth() <= 100 && player.getSyringe() > 0 )
			{
				player.setHealth(player.getHealth() + 50);
				player.setSyringe(player.getSyringe() - 1);
			}

		}

		/*--------------------------------------------  Melee  -----------------------------------------------------------*/

		else if (Keyboard::isKeyPressed(Keyboard::V) && !isDead)
		{
			currentFrame += 0.005 * time;

			if (currentFrame > 3)
			{
				currentFrame -= 3;
			}

			if (IsRightDir)
			{
				player.setRectRight(sizeX, sizeY, currentFrame);
			}
			else if (!IsRightDir)
			{
				player.setRectLeft(sizeX, sizeY, currentFrame);
			}
		}

		/*--------------------------------------------  Sit  -----------------------------------------------------------*/

		else if (Keyboard::isKeyPressed(Keyboard::LControl) && !isDead)
		{
			currentFrame += 0.005 * time;

			if (currentFrame > 3)
			{
				currentFrame -= 3;
			}

			if (IsRightDir)
			{
				player.setRectRight(sizeX, sizeY, currentFrame);
			}
			else if (!IsRightDir)
			{
				player.setRectLeft(sizeX, sizeY, currentFrame);
			}
		}

	    /*----------------------------------------  Siting shoot  -----------------------------------------------------------*/

		else if (Keyboard::isKeyPressed(Keyboard::LControl) && Mouse::isButtonPressed(Mouse::Right) && !isDead )
		{
			currentFrame += 0.005 * time;

			if (currentFrame > 3)
			{
				currentFrame -= 3;
			}

			if (IsRightDir)
			{
				player.setRectRight(sizeX, sizeY, currentFrame);
			}
			else if (!IsRightDir)
			{
				player.setRectLeft(sizeX, sizeY, currentFrame);
			}
		}

		/*--------------------------------------------  Roll  -----------------------------------------------------------*/

		else if (Keyboard::isKeyPressed(Keyboard::Space) && !isDead)
		{
			currentFrame += 0.005 * time;

			if (currentFrame > 6)
			{
				currentFrame -= 6;
			}

			if (IsRightDir)
			{
				player.setRectRight(sizeX, sizeY, currentFrame);
			}
			else if (!IsRightDir)
			{
				player.setRectLeft(sizeX, sizeY, currentFrame);
			}
		} 

		/*--------------------------------------------  shoot  -----------------------------------------------------------*/

		if (Mouse::isButtonPressed(Mouse::Left) && fireRateClock.getElapsedTime().asSeconds() >= fireCooldown)
		{
			bullet.push_back(Bullet(damageBullet, speedBullet, sizeXbullet, sizeYbullet, scaleXbullet, scaleYbullet, player, IsRightDir));

			fireRateClock.restart();
		}

		/*--------------------------------------------  moveBullets  -----------------------------------------------------------*/

		for (size_t i = 0; i < bullet.size(); i++)
		{
			if (bullet[i].getBulletDir() == 1)
			{
				bullet[i].moveRight(time);
			}
			else if(bullet[i].getBulletDir() == 0)
			{
				bullet[i].changeImageDir(scaleXbullet, scaleYbullet);
				bullet[i].moveLeft(time);
			}
		}

		/*--------------------------------------------  shotCollision  -----------------------------------------------------------*/

		for (size_t i = 0; i < bullet.size(); i++)
		{
			FloatRect bulletBounds = bullet[i].getGlobalBounds();

			if (bulletBounds.intersects(player1.getGlobalBounds()))
			{
				player.setHealth(player1.getHealth() - bullet[i].getDamage());
				bullet.erase(bullet.begin() + i);
				i--; 
			}
		}
			
		/*--------------------------------------------  Draw  -----------------------------------------------------------*/

		window.clear(Color::Black);
		
		
		for (size_t i = 0; i < bullet.size(); i++)
		{
			bullet[i].Draw(window);
		}

		player.drawSprite(window);
		player1.drawSprite(window);

		window.display();
	}
}