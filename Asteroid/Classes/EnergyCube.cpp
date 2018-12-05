#include "EnergyCube.h"

std::vector<EnergyCube*> EnergyCube::energyCubeList = std::vector<EnergyCube*>();

EnergyCube::EnergyCube(Vect2 startVelocity, Vect2 position) : GameObject(position, "EnergyCube.png")
{
	velocity = startVelocity;
	energyCubeList.push_back(this);
}

void EnergyCube::removeObject()
{
	//remove the bullet
	destroySprite();
	energyCubeList.erase(std::remove(energyCubeList.begin(), energyCubeList.end(), this), energyCubeList.end());
}

void EnergyCube::updatePhysics(float dt, Ship* ship)
{
	GameObject::updatePhysics(dt);

	if (isCollidingWith(ship))
	{
		ship->numEnergyCubes++;
		destroySprite();
		energyCubeList.erase(
			std::remove(energyCubeList.begin(), energyCubeList.end(), this),
			energyCubeList.end());
	}
}