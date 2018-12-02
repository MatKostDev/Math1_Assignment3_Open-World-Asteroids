#include "BlackHole.h"

std::vector<BlackHole*> BlackHole::blackHoleList = std::vector<BlackHole*>();

BlackHole::BlackHole(Vect2 position) : GameObject(position, "BlackHole.png"), PULL_SPEED(600), RANGE(500)
{
	blackHoleList.push_back(this);
}

void BlackHole::updatePhysics(float dt, Ship* ship)
{
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