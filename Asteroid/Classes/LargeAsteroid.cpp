#include "LargeAsteroid.h"

std::vector<LargeAsteroid*> LargeAsteroid::largeAsteroidList = std::vector<LargeAsteroid*>();

LargeAsteroid::LargeAsteroid(Vect2 position, Vect2 startVelocity) : GameObject(position, "LargeAsteroid.png")
{
	velocity = startVelocity;
	largeAsteroidList.push_back(this);
}

bool LargeAsteroid::isCollidingWith(Ship* ship, Scene* myScene)
{
	if (GameObject::isCollidingWith(ship))
	{
		ship->takeDamage();
		this->removeAsteroid(myScene);
		return true;
	}

	return false;
}

bool LargeAsteroid::isCollidingWith(FriendlyBullet* bullet, Scene* myScene)
{
	if (GameObject::isCollidingWith(bullet))
	{
		bullet->removeBullet();
		this->removeAsteroid(myScene);
		return true;
	}

	return false;
}

void LargeAsteroid::updatePhysics(float dt, Ship* ship, Scene* myScene)
{
	GameObject::updatePhysics(dt);

	isCollidingWith(ship, myScene);

	for (int i = 0; i < FriendlyBullet::friendlyBulletList.size(); i++)
	{
		if (this->isCollidingWith(FriendlyBullet::friendlyBulletList[i], myScene))
			break;
	}
}

void LargeAsteroid::removeAsteroid(Scene* myScene)
{
	//spawn a random number of small asteroids
	int numAsteroids = myRand::getRandNum(3, 1);
	for (int k = 0; k <= numAsteroids; k++)
	{
		SmallAsteroid* newSmallAsteroid = new SmallAsteroid
			(Vect2(this->getPosition()),  //position is the same as parent asteroid
			Vect2(myRand::getRandNum(150, 100, true), myRand::getRandNum(150, 100, true))); //velocity is random for x and y

		myScene->addChild(newSmallAsteroid->sprite, 8);
	}

	//remove the asteroid
	destroySprite();
	largeAsteroidList.erase(std::remove(largeAsteroidList.begin(), largeAsteroidList.end(), this), largeAsteroidList.end());
}