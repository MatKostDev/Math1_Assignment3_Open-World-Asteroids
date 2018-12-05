#include "Planet.h"

std::vector<Planet*> Planet::planetList = std::vector<Planet*>();

Planet::Planet(Vect2 position) : GameObject(position, "Planet.png")
{
	theta = 0;
	shootTimer = 0;

	planetList.push_back(this);
}

//shoots a bullet, adds it to the list of enemy bullets and returns it so it can be added to the scene
EnemyBullet* Planet::shootBullet()
{
	EnemyBullet* newEnemyBullet = new EnemyBullet(Vect2(sprite->getPosition()), theta);
	EnemyBullet::enemyBulletList.push_back(newEnemyBullet);
	shootTimer = 0; //reset timer
	return newEnemyBullet;
}

void Planet::removeObject()
{
	//remove the object
	destroySprite();
	planetList.erase(std::remove(planetList.begin(), planetList.end(), this), planetList.end());
}

void Planet::updatePhysics(float dt, Vect2 shipPosition)
{
	//check if the ship is on the player's screen
	if (GameObject::screenRect->containsPoint(sprite->getPosition()));
	{
		//have the shooting ship rotate to follow our ship
		Vect2 distance = shipPosition - getPosition(); //calculate distance vector between the two ships
		theta = (atan2(distance.x, distance.y) * 180 / M_PI); //perform atan2 (returns the angle in rad between the positive x axis (1, 0) and the point provided) on the distance and convert to degrees
		
		//add to the timer
		shootTimer += dt;
	}
}