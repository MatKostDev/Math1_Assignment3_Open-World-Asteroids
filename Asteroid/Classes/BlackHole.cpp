#include "BlackHole.h"

std::vector<BlackHole*> BlackHole::blackHoleList = std::vector<BlackHole*>();

BlackHole::BlackHole(Vect2 position) : GameObject(position, "BlackHole.png"), PULL_SPEED(600), RANGE(500)
{
	blackHoleList.push_back(this);
}

bool BlackHole::isCollidingWith(Ship* ship)
{
	if (GameObject::isCollidingWith(ship))
	{
		ship->takeDamage();
		return true;
	}

	return false;
}

bool BlackHole::isCollidingWith(FriendlyBullet * bullet)
{
	if (GameObject::isCollidingWith(bullet))
	{
		bullet->removeBullet();
		return true;
	}

	return false;
}

void BlackHole::updatePhysics(float dt, Ship* ship)
{
	//check for collision on the ship
	isCollidingWith(ship);

	//check for collision on the ship's bullets
	for (int i = 0; i < FriendlyBullet::friendlyBulletList.size(); i++)
	{
		if (isCollidingWith(FriendlyBullet::friendlyBulletList[i]))
			break;
	}

	//find the angle to pull the ship towards the blackhole
	Vect2 distance = getPosition() - ship->getPosition(); //calculate distance vector between the backhole and ship

	//if the ship is within range of the blackhole
	if (distance < RANGE && distance > -RANGE)
	{
		theta = (atan2(distance.x, distance.y)); //perform atan2 (returns the angle in rad between the positive x axis (1, 0) and the point provided) on the distance

		//apply the pull to the ship
		ship->velocity += Vect2(sinf(theta), cosf(theta)) * dt * PULL_SPEED;
	}
}