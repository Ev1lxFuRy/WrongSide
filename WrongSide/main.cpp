#include<SFML/Graphics.hpp>
#include<fstream>
#include<iostream>

#include "NPC.h"
#include "Bullet.h"
#include "RenderFPS.h"
#include "Map.h"

using namespace std;
using namespace sf;  

// проверить как работают статик поля в классах

int main()
{
	setlocale(LC_ALL, "Russian");

	Vector2f mapScaleXY;
	mapScaleXY.x = 3.5;
	mapScaleXY.y = 3.5;

	/*---------------------------------------  HeroParameters  --------------------------------------------------*/

	int health = 100;
	double speed = 0.1;

	int sizeX = 192;
	int sizeY = 205;

	float scaleX = 0.65;
	float scaleY = 0.65;

	float shiftModifier = 1.5;
	float rollModifier = 2;

	int PositionX_player1 = 400;
	int PositionY_player1 = 600;

	int PositionY_player2 = 600;
    int PositionX_player2 = 800;

	int frame = 0; //reloading animation

	string skinName1 = "1";
	string skinName2 = "2";
	string skinName3 = "3";

	/*---------------------------------------  BulletParameters  --------------------------------------------------*/

	bool leftMouse = 0;
	bool rightMouse = 1;

	int damageBulletPrecition = 5;
	int damageBulletAccurate = 10;

	float speedBullet = 0.2;
	
	int sizeXbullet = 1030;
	int sizeYbullet = 320;

	float scaleXbullet = 0.015;
	float scaleYbullet = 0.015; //17

	Clock fireRateClock; 
	float fireCooldownPrecition = 0.15;
	float fireCooldownAccurate = 0.30;

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

	Clock clockReload;
	float reloadTimer = 0.50;

	float animationSpeed = 0.005;

	/*-----------------------------------------  WindowSettings  --------------------------------------------------*/

	ContextSettings settings;
	settings.antialiasingLevel = 8;

	VideoMode desktop = VideoMode::getDesktopMode();
	RenderWindow window(desktop, "Hello world", Style::Fullscreen, settings);

	/*------------------------------------------  LoadObjects  --------------------------------------------------*/

	Map map(mapScaleXY);
	NPC player(skinName2, health, speed, PositionX_player1, PositionY_player1, sizeX, sizeY, scaleX, scaleY);
	NPC player1(skinName2, health, speed, PositionX_player2, PositionY_player2, sizeX, sizeY, scaleX, scaleY);

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

			currentFrame += animationSpeed * time;

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

			currentFrame += animationSpeed * time;

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

		else if (Keyboard::isKeyPressed(Keyboard::LShift) && Keyboard::isKeyPressed(Keyboard::W) && !isDead && player.getGlobalBoundsRectangle().top >= 0)
		{
			player.moveUp(time, shiftModifier);

			currentFrame += animationSpeed * time;

			if (currentFrame > 8)
			{
				currentFrame -= 8;
			}

			if (IsRightDir)
			{
				player.setRectRight(sizeX, sizeY, currentFrame, 2);
			}
			else
			{
				player.setRectLeft(sizeX, sizeY, currentFrame, 2);
			}

		}
		else if (Keyboard::isKeyPressed(Keyboard::LShift) && Keyboard::isKeyPressed(Keyboard::S) && !isDead && player.getGlobalBoundsRectangle().top + player.getGlobalBoundsRectangle().height <= desktop.height)
		{
			player.moveDown(time, shiftModifier);

			currentFrame += animationSpeed * time;

			if (currentFrame > 8)
			{
				currentFrame -= 8;
			}

			if (IsRightDir)
			{
				player.setRectRight(sizeX, sizeY, currentFrame, 2);
			}
			else
			{
				player.setRectLeft(sizeX, sizeY, currentFrame, 2);
			}

		}
		else if (Keyboard::isKeyPressed(Keyboard::LShift) && Keyboard::isKeyPressed(Keyboard::D) && !isDead && player.getGlobalBoundsRectangle().left + player.getGlobalBoundsRectangle().width <= desktop.width)
		{
			player.moveRight(time, shiftModifier);

			currentFrame += animationSpeed * time;

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
		else if (Keyboard::isKeyPressed(Keyboard::LShift) && Keyboard::isKeyPressed(Keyboard::A) && !isDead && player.getGlobalBoundsRectangle().left >= 0)
		{
			player.moveLeft(time, shiftModifier);

			currentFrame += animationSpeed * time;

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

		else if (Keyboard::isKeyPressed(Keyboard::W) && !isDead && player.getGlobalBoundsRectangle().top >= 0)
		{
			IsMoving = 1;
			player.moveUp(time);

			currentFrame += animationSpeed * time;
			if (currentFrame > 7)
			{
				currentFrame -= 7;
			}

			if (IsRightDir)
			{
				player.setRectRight(sizeX, sizeY, currentFrame, 1);
			}
			else
			{
				player.setRectLeft(sizeX, sizeY, currentFrame, 1);
			}

		}
		else if (Keyboard::isKeyPressed(Keyboard::S) && !isDead && player.getGlobalBoundsRectangle().top + player.getGlobalBoundsRectangle().height <= desktop.height)
		{
			IsMoving = 1;
			player.moveDown(time);

			currentFrame += animationSpeed * time;
			if (currentFrame > 7)
			{
				currentFrame -= 7;
			}

			if (IsRightDir)
			{
				player.setRectRight(sizeX, sizeY, currentFrame, 1);
			}
			else
			{
				player.setRectLeft(sizeX, sizeY, currentFrame, 1);
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::D) && !isDead && player.getGlobalBoundsRectangle().left + player.getGlobalBoundsRectangle().width <= desktop.width)
		{
			IsRightDir = 1;
			IsMoving = 1;

			player.moveRight(time);

			currentFrame += animationSpeed * time;
			if (currentFrame > 7)
			{
				currentFrame -= 7;
			}

			player.setRectRight(sizeX, sizeY, currentFrame,1);
		
			
		}
        else if (Keyboard::isKeyPressed(Keyboard::A) && !isDead && player.getGlobalBoundsRectangle().left >= 0)
		{
			IsMoving = 1;
			IsRightDir = 0;

			player.moveLeft(time);

			currentFrame += animationSpeed * time;
			if (currentFrame > 7)
			{
				currentFrame -= 7;
			}

			player.setRectLeft(sizeX, sizeY, currentFrame,1);
		}

		/*--------------------------------------------  Reload  -----------------------------------------------------------*/

		else if (player.getAmmo() >= 0 && player.getAmmo() <= 25 && Keyboard::isKeyPressed(Keyboard::R))
		{
			currentFrame += (animationSpeed * time)/1.25;

			if (currentFrame > 8) {	currentFrame -= 8;}

			if (IsRightDir)
			{
				player.setRectRight(sizeX, sizeY, currentFrame,5);
			}
			else if (!IsRightDir)
			{
				player.setRectLeft(sizeX, sizeY, currentFrame,5);
			}

			if (clockReload.getElapsedTime().asSeconds() >= reloadTimer)
			{
				player.setAmmo(player.getAmmo() + 5);
				clockReload.restart();
			}
		}

		/*--------------------------------------------  Shoot  -----------------------------------------------------------*/

		else if (Mouse::isButtonPressed(Mouse::Left) && player.getAmmo() > 0)
		{
			currentFrame += animationSpeed * time;
			if (currentFrame > 4){ currentFrame -= 4;}

			if (IsRightDir)
			{
				player.setRectRight(sizeX, sizeY, currentFrame, 3);
			}
			else if (!IsRightDir)
			{
				player.setRectLeft(sizeX, sizeY, currentFrame, 3);
			}

			if (fireRateClock.getElapsedTime().asSeconds() >= fireCooldownPrecition)
			{
				if (player.getPosition().x < player1.getPosition().x)
				{
					isBulletFromLeft = 1;
				}
				else
				{
					isBulletFromLeft = 0;
				}

				bullet.push_back(Bullet(damageBulletPrecition, speedBullet, sizeXbullet, sizeYbullet, scaleXbullet, scaleYbullet, player, leftMouse, isBulletFromLeft, IsRightDir));
				player.setAmmo(player.getAmmo() - 1);
				
				fireRateClock.restart();
			}
		}
        else if (Mouse::isButtonPressed(Mouse::Right) && player.getAmmo() > 0)
		{
			currentFrame += animationSpeed * time;
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

			if (fireRateClock.getElapsedTime().asSeconds() >= fireCooldownAccurate)
			{
				if (player.getPosition().x < player1.getPosition().x)
				{
					isBulletFromLeft = 1;
				}
				else
				{
					isBulletFromLeft = 0;
				}

				bullet.push_back(Bullet(damageBulletAccurate, speedBullet, sizeXbullet, sizeYbullet, scaleXbullet, scaleYbullet, player, rightMouse, isBulletFromLeft, IsRightDir));

				player.setAmmo(player.getAmmo() - 1);

				fireRateClock.restart();
			}

		}

		/*-----------------------------------------  DontMoving  -----------------------------------------------------------*/

		else if (!IsMoving && !isDead)
		{
			currentFrame += animationSpeed * time;
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

		/*--------------------------------------------  Melee  -----------------------------------------------------------*/

		if (Keyboard::isKeyPressed(Keyboard::V))
		{
			currentFrame += (animationSpeed * time)/25;

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
				currentFrame += (animationSpeed * time)/20;

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

		/*--------------------------------------------  Jump  -----------------------------------------------------------*/

		else if (Keyboard::isKeyPressed(Keyboard::Space) && !isDead)
		{
			currentFrame += (animationSpeed * time)/20;

			if (currentFrame > 6)
			{
				currentFrame -= 6;
			}

			if (IsRightDir)
			{
				player.setRectRight(sizeX, sizeY, currentFrame, 9);
			}
			else if (!IsRightDir)
			{
				player.setRectLeft(sizeX, sizeY, currentFrame, 9);
			}
		}

		/*--------------------------------------------  Roll  -----------------------------------------------------------*/

		else if (Keyboard::isKeyPressed(Keyboard::E) && !isDead && player.getGlobalBoundsRectangle().top >= 0 && player.getGlobalBoundsRectangle().top + player.getGlobalBoundsRectangle().height <= desktop.height && player.getGlobalBoundsRectangle().left >= 0 && player.getGlobalBoundsRectangle().left + player.getGlobalBoundsRectangle().width <= desktop.width)
		{
			currentFrame += (animationSpeed * time)/110;

			if (currentFrame > 6)
			{
				currentFrame -= 6;
			}

			if (IsRightDir)
			{
				player.setRectRight(sizeX, sizeY, currentFrame,10);
				player.moveRight(time, rollModifier);
			}
			else if (!IsRightDir)
			{
				player.setRectLeft(sizeX, sizeY, currentFrame,10);
				player.moveLeft(time, rollModifier);
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

		if (currentFrame > 3)
		{
			currentFrame -= 3;
		}

		for (int i = bullet.size() - 1; i >= 0; --i)
		{
			FloatRect playerBounder = player1.getGlobalBoundsRectangle();
			FloatRect bulletBounder = bullet[i].getGlobalBounds();

			if ( bullet[i].getBulletDir() == 1 && bulletBounder.left + bulletBounder.width > playerBounder.left &&
				playerBounder.left + playerBounder.width > bulletBounder.left &&
				bulletBounder.top + bulletBounder.height > playerBounder.top &&
				bulletBounder.top < playerBounder.top + playerBounder.height &&
				bulletBounder.top < playerBounder.top + playerBounder.height &&
				bulletBounder.top + bulletBounder.height > playerBounder.top
				)
			{
				player1.setRectLeft(sizeX, sizeY, currentFrame, 7);

				player1.setHealth(player1.getHealth() - bullet[i].getDamage());
				bullet.erase(bullet.begin() + i);
				i--;
			}
			else if(bullet[i].getBulletDir() == 0 && bulletBounder.left < playerBounder.left + playerBounder.width && 
				bulletBounder.left + bulletBounder.width > playerBounder.left &&
				bulletBounder.top + bulletBounder.height > playerBounder.top &&
				bulletBounder.top < playerBounder.top + playerBounder.height &&
				bulletBounder.top < playerBounder.top + playerBounder.height &&
				bulletBounder.top + bulletBounder.height > playerBounder.top)
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
				bulletBounds.left > desktop.width ||
				bulletBounds.top + bulletBounds.height < 0 ||
				bulletBounds.top > desktop.height)
			{
				bullet.erase(bullet.begin() + i);
			}
		}

		/*--------------------------------------------  Draw  -----------------------------------------------------------*/
		window.clear(Color::Black);

		map.draw(window);

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