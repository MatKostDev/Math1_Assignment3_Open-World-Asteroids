#include "ShootingShip.h"

ShootingShip::ShootingShip(Vect2 position) : GameObject(position, "ShootingShip.png")
{
	theta = 0;
}

void ShootingShip::Shoot()
{
}

void ShootingShip::updatePhysics(float dt, Vect2 shipPosition)
{
	//have the shooting ship rotate to follow our ship
	Vect2 distance = shipPosition - getPosition();
	theta = (atan2(distance.x, distance.y) * 180 / M_PI);
	sprite->runAction(RotateTo::create(0, theta)); //update the sprite's rotation
}
