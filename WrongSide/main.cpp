#include<SFML/Graphics.hpp>
#include<fstream>
#include<iostream>

#include "NPC.h"
#include "Bullet.h"
#include "RenderFPS.h"

using namespace std;
using namespace sf;  

// проверить как работают статик поля в классах

int main()
{
	setlocale(LC_ALL, "Russian");
	/*---------------------------------------  HeroParameters  --------------------------------------------------*/

	int health = 100;
	double speed = 0.1;

	int sizeX = 192;
	int sizeY = 205;

	float scaleX = 0.65;
	float scaleY = 0.65;

	float shiftModifier = 1.2;

	int PositionX_player1 = 400;
	int PositionY_player2 = 600;

	int PositionX_player2 = 800;
	int PositionY_player1 = 600;

	int frame = 0; //reloading animation

	/*---------------------------------------  BulletParameters  --------------------------------------------------*/

	bool leftMouse = 0;
	bool rightMouse = 1;

	int damageBullet = 5;
	float speedBullet = 0.2;
	
	int sizeXbullet = 1030;
	int sizeYbullet = 320;

	float scaleXbullet = 0.017;
	float scaleYbullet = 0.017;

	Clock fireRateClock; 
	float fireCooldown = 0.2;

	bool isBulletFromLeft = 1;

	/*---------------------------------------------  Logic  --------------------------------------------------*/

	bool IsRightDir = 1;

	Clock clockFPS;
	float frameRate = 0;
	int fps;

	Clock clock;
	float currentFrame = 0;
	bool gameOver = 0;
	bool isDead = 0;
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

	RenderFPS rFps;

	/*------------------------------------------  GameLoop  -----------------------------------------------------*/

	while (window.isOpen() && !gameOver)
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time /= 500;

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

		frameRate = clockFPS.restart().asSeconds();
		fps = int( 1 / frameRate );
		rFps.loadText(to_string(fps));

		/*--------------------------------------------  Dead  -----------------------------------------------------------*/

		if (player.getHealth() <= 0)
		{
			isDead = 1;

			currentFrame += 0.005 * time;

			if (currentFrame > 4)
			{
				currentFrame -= 4;
				gameOver = 1;
			}

			if (IsRightDir)
			{
				player.setRectRight(sizeX, sizeY, currentFrame,8);
			}
			else if (!IsRightDir)
			{
				player.setRectLeft(sizeX, sizeY, currentFrame,8);
			}

			gameOver = 1;
		}
		if (player1.getHealth() <= 0 )
		{
			isDead = 1 ;

			currentFrame += 0.005 * time;

			if (currentFrame > 4)
			{
				currentFrame -= 4;
				gameOver = 1;
			}

			if (IsRightDir)
			{
				player1.setRectRight(sizeX, sizeY, currentFrame,8);
			}
			else if (!IsRightDir)
			{
				player1.setRectLeft(sizeX, sizeY, currentFrame,8);
			}
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
				player.setRectRight(sizeX, sizeY, currentFrame,2);
			}
			else if (!IsRightDir)
			{
				player.setRectLeft(sizeX, sizeY, currentFrame,2);
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
				player.setRectRight(sizeX, sizeY, currentFrame,2);
			}
			else if (!IsRightDir)
			{
				player.setRectLeft(sizeX, sizeY, currentFrame,2);
			}
		}

		/*--------------------------------------------  Move  -----------------------------------------------------------*/

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

			player.setRectRight(sizeX, sizeY, currentFrame,1);
		
			
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

			player.setRectLeft(sizeX, sizeY, currentFrame,1);
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
	
		/*--------------------------------------------  Reload  -----------------------------------------------------------*/

		else if (player.getAmmo() <= 0 || Keyboard::isKeyPressed(Keyboard::R))
		{
			currentFrame += 0.0005 * time;

			if (currentFrame > 8)
			{
				currentFrame -= 8;
			}

			if (IsRightDir)
			{
				player.setRectRight(sizeX, sizeY, currentFrame,5);
				frame++;
			}
			else if (!IsRightDir)
			{
				player.setRectLeft(sizeX, sizeY, currentFrame,5);
				frame++;
			}

			if (frame >= 8)
			{
			    player.setAmmo(30);
				frame -= 8;
			}
		}

		/*--------------------------------------------  Shoot  -----------------------------------------------------------*/

		if (Mouse::isButtonPressed(Mouse::Left) )
		{

			if (fireRateClock.getElapsedTime().asSeconds() >= fireCooldown)
			{
				if (player.getPosition().x < player1.getPosition().x)
				{
					isBulletFromLeft = 1;
				}
				else
				{
					isBulletFromLeft = 0;
				}

				bullet.push_back(Bullet(damageBullet, speedBullet, sizeXbullet, sizeYbullet, scaleXbullet, scaleYbullet, player, leftMouse, isBulletFromLeft, IsRightDir));

				player.setAmmo(player.getAmmo() - 1);
				fireRateClock.restart();
			}

			if (currentFrame > 4)
			{
				currentFrame -= 4;
			}

			if (IsRightDir)
			{
				player.setRectRight(sizeX, sizeY, currentFrame, 3);
			}
			else if (!IsRightDir)
			{
				player.setRectLeft(sizeX, sizeY, currentFrame, 3);
			}
		}
        if (Mouse::isButtonPressed(Mouse::Right))
		{
			if (fireRateClock.getElapsedTime().asSeconds() >= fireCooldown)
			{
				if (player.getPosition().x < player1.getPosition().x)
				{
					isBulletFromLeft = 1;
				}
				else
				{
					isBulletFromLeft = 0;
				}

				bullet.push_back(Bullet(damageBullet, speedBullet, sizeXbullet, sizeYbullet, scaleXbullet, scaleYbullet, player, rightMouse, isBulletFromLeft, IsRightDir));
				player.setAmmo(player.getAmmo() - 1);
				fireRateClock.restart();
			}

			currentFrame += 0.005 * time;

			if (currentFrame > 4)
			{
				currentFrame -= 4;
			}

			if (IsRightDir)
			{
				player.setRectRight(sizeX, sizeY, currentFrame, 4);
			}
			else if (!IsRightDir)
			{
				player.setRectLeft(sizeX, sizeY, currentFrame, 4);
			}
		}

		/*--------------------------------------------  Melee  -----------------------------------------------------------*/

		if (Keyboard::isKeyPressed(Keyboard::V))
		{
			currentFrame += 0.005 * time;

			if (currentFrame > 3)
			{
				currentFrame -= 3;
			}

			if (IsRightDir)
			{
				player.setRectRight(sizeX, sizeY, currentFrame, 6);
			}
			else if (!IsRightDir)
			{
				player.setRectLeft(sizeX, sizeY, currentFrame, 6);
			}
		}

		/*--------------------------------------------  Healing  -----------------------------------------------------------*/

		else if (Keyboard::isKeyPressed(Keyboard::F) && !isDead)
		{
			if (player1.getHealth() <= 100 && player1.getSyringe() > 0 )
			{
				currentFrame += 0.005 * time;

				if (currentFrame > 5)
				{
					currentFrame -= 5;

					player1.setHealth(player.getHealth() + 20);
					player1.setSyringe(player.getSyringe() - 1);
				}

				if (IsRightDir)
				{
					player1.setRectRight(sizeX, sizeY, currentFrame, 11);
				}
				else if (!IsRightDir)
				{
					player1.setRectLeft(sizeX, sizeY, currentFrame, 11);
				}
			}

		}

		/*--------------------------------------------  Roll  -----------------------------------------------------------*/

		else if (Keyboard::isKeyPressed(Keyboard::E) && !isDead)
		{
			currentFrame += 0.00000005 * time;

			if (currentFrame > 6)
			{
				currentFrame -= 6;
			}

			if (IsRightDir)
			{
				player.setRectRight(sizeX, sizeY, currentFrame,10);
			}
			else if (!IsRightDir)
			{
				player.setRectLeft(sizeX, sizeY, currentFrame,10);
			}
		} 

		/*--------------------------------------------  moveBullets  -----------------------------------------------------------*/

		for (size_t i = 0; i < bullet.size(); i++)
		{
			if (bullet[i].getBulletMoveDir() == 1)
			{
				bullet[i].moveRight(time);
			}

			else if(bullet[i].getBulletMoveDir() == 0)
			{
				bullet[i].changeImageDir(scaleXbullet, scaleYbullet);
				bullet[i].moveLeft(time);
			}
		}

		/*--------------------------------------------  GotHurt  -----------------------------------------------------------*/


		/*currentFrame += 0.005 * time;*/

		if (currentFrame > 3)
		{
			currentFrame -= 3;
		}

		for (int i = bullet.size() - 1; i >= 0; --i)
		{
			FloatRect playerBounder = player1.getGlobalBoundsRectangle();
			FloatRect bulletBounder = bullet[i].getGlobalBounds();

			if ( bullet[i].getBulletDir() == 1 && bulletBounder.left + bulletBounder.width > playerBounder.left &&
				playerBounder.left + playerBounder.width > bulletBounder.left)
			{
				player1.setRectLeft(sizeX, sizeY, currentFrame, 7);

				player1.setHealth(player1.getHealth() - bullet[i].getDamage());
				bullet.erase(bullet.begin() + i);
				i--;
			}
			else if(bullet[i].getBulletDir() == 0 && bulletBounder.left < playerBounder.left + playerBounder.width && 
				bulletBounder.left + bulletBounder.width > playerBounder.left)
			{
				player1.setRectRight(sizeX, sizeY, currentFrame, 7);

				player1.setHealth(player1.getHealth() - bullet[i].getDamage());
				bullet.erase(bullet.begin() + i);
				i--;
			}
		}

		/*--------------------------------------------  HitWall  -----------------------------------------------------------*/
			
		for (int i = bullet.size() - 1; i >= 0; i--)
		{
			FloatRect bulletBounds = bullet[i].getGlobalBounds();

			if (bulletBounds.left + bulletBounds.width < 0 ||
				bulletBounds.left > width ||
				bulletBounds.top + bulletBounds.height < 0 ||
				bulletBounds.top > height)
			{
				bullet.erase(bullet.begin() + i);
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

		rFps.draw(window);

		window.display();
	}
}