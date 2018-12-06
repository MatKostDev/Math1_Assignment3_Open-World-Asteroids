#include "ShootingShip.h"

std::vector<ShootingShip*> ShootingShip::shootingShipList = std::vector<ShootingShip*>();

ShootingShip::ShootingShip(Vect2 position) : GameObject(position, "SShip.png")
{
	theta = 0;
	shootTimer = 0;
	spinTimer = 0;
	health = 3;

	shootingShipList.push_back(this);
}

void ShootingShip::takeDamage()
{
	health--;

	if (health <= 0)
		removeShip();
}

void ShootingShip::removeShip()
{
	destroySprite();

	shootingShipList.erase(
		std::remove(shootingShipList.begin(), shootingShipList.end(), this),
		shootingShipList.end());
}

//shoots a bullet, adds it to the list of enemy bullets and returns it so it can be added to the scene
EnemyBullet* ShootingShip::shootBullet()
{
	EnemyBullet* newEnemyBullet = new EnemyBullet(Vect2(sprite->getPosition()), theta);
	EnemyBullet::enemyBulletList.push_back(newEnemyBullet);
	shootTimer = 0; //reset timer
	return newEnemyBullet;
}

void ShootingShip::updatePhysics(float dt, Vect2 shipPosition)
{
	//check if the ship is on the player's screen
	if (GameObject::screenRect->containsPoint(sprite->getPosition()));
	{
		if (spinTimer <= 0)
		{
			//have the shooting ship rotate to follow our ship
			Vect2 distance = shipPosition - getPosition(); //calculate distance vector between the two ships
			theta = (atan2(distance.x, distance.y) * 180 / M_PI); //perform atan2 (returns the angle in rad between the positive x axis (1, 0) and the point provided) on the distance and convert to degrees
			sprite->runAction(RotateTo::create(0, theta)); //update the sprite's rotation
		}
		else //should be spinning
		{
			theta += 250 * dt;
			sprite->runAction(RotateTo::create(0, theta)); //update the sprite's rotation

			spinTimer -= dt;
		}

		//add to the timer
		shootTimer += dt;
	}
}