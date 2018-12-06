#include "MovingShip.h"

std::vector<MovingShip*> MovingShip::movingShipList = std::vector<MovingShip*>();

MovingShip::MovingShip(Vect2 position) : GameObject(position, "MShip.png"), MOVESPEED(20000)
{
	theta = 0;
	health = 3;
	spinTimer = 0;
	movingShipList.push_back(this);
}

void MovingShip::takeDamage()
{
	health--;

	if (health <= 0)
		removeShip();
}

void MovingShip::removeShip()
{
	destroySprite();

	movingShipList.erase(
		std::remove(movingShipList.begin(), movingShipList.end(), this),
		movingShipList.end());
}

void MovingShip::updatePhysics(float dt, Vect2 shipPosition)
{
	//call base class update
	GameObject::updatePhysics(dt);

	//check if the ship is on the player's screen
	if (GameObject::screenRect->containsPoint(sprite->getPosition()));
	{
		if (spinTimer <= 0)
		{
			//have the shooting ship rotate to follow our ship
			Vect2 distance = shipPosition - getPosition(); //calculate distance vector between the two ships
			theta = (atan2(distance.x, distance.y) * 180 / M_PI); //perform atan2 (returns the angle in rad between the positive x axis (1, 0) and the point provided) on the distance and convert to degrees
			sprite->runAction(RotateTo::create(0, theta)); //update the sprite's rotation

			velocity = Vect2(
				sinf(theta / 180 * M_PI),
				cosf(theta / 180 * M_PI))
				* dt * MOVESPEED;
		}
		else //should be spinning
		{
			theta += 250 * dt;
			sprite->runAction(RotateTo::create(0, theta)); //update the sprite's rotation

			spinTimer -= dt;
		}
	}
}