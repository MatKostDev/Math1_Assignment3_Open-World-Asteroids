#include "MovingShip.h"

std::vector<MovingShip*> MovingShip::movingShipList = std::vector<MovingShip*>();

MovingShip::MovingShip(Vect2 position) : GameObject(position, "ShootingShip.png"), MOVESPEED(20000)
{
	theta = 0;
	movingShipList.push_back(this);
}

void MovingShip::updatePhysics(float dt, Vect2 shipPosition)
{
	//call base class update
	GameObject::updatePhysics(dt);

	//check if the ship is on the player's screen
	if (GameObject::screenRect->containsPoint(sprite->getPosition()));
	{
		//have the moving ship rotate to follow our ship
		Vect2 distance = shipPosition - getPosition();
		theta = (atan2(distance.x, distance.y) * 180 / M_PI);
		sprite->runAction(RotateTo::create(0, theta)); //update the sprite's rotation

		velocity = Vect2(
			sinf(theta / 180 * M_PI),
			cosf(theta / 180 * M_PI))
			* dt * MOVESPEED;
	}
}