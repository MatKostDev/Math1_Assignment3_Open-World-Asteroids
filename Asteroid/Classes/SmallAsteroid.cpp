#include "SmallAsteroid.h"

std::vector<SmallAsteroid*> SmallAsteroid::smallAsteroidList = std::vector<SmallAsteroid*>();

SmallAsteroid::SmallAsteroid(Vect2 position, Vect2 startVelocity) : GameObject(position, "SAsteroid.png")
{
	velocity = startVelocity;
	smallAsteroidList.push_back(this);
}

bool SmallAsteroid::isCollidingWith(Ship* ship)
{
	if (GameObject::isCollidingWith(ship))
	{
		ship->takeDamage();
		this->removeAsteroid();
		return true;
	}

	return false;
}

bool SmallAsteroid::isCollidingWith(FriendlyBullet* bullet)
{
	if (GameObject::isCollidingWith(bullet))
	{
		bullet->removeBullet();
		this->removeAsteroid();
		return true;
	}

	return false;
}

void SmallAsteroid::updatePhysics(float dt, Ship* ship)
{
	GameObject::updatePhysics(dt);

	this->isCollidingWith(ship);

	for (int i = 0; i < FriendlyBullet::friendlyBulletList.size(); i++)
	{
		if (this->isCollidingWith(FriendlyBullet::friendlyBulletList[i]))
			break;
	}
}

void SmallAsteroid::removeAsteroid()
{
	//remove the asteroid
	destroySprite();
	smallAsteroidList.erase(std::remove(smallAsteroidList.begin(), smallAsteroidList.end(), this), smallAsteroidList.end());
}
