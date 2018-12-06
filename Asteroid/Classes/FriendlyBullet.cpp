#include "FriendlyBullet.h"

std::vector<FriendlyBullet*> FriendlyBullet::friendlyBulletList = std::vector<FriendlyBullet*>();

FriendlyBullet::FriendlyBullet(Vect2 position, float theta) : Bullet(position, theta, "FriendlyBullet.png")
{
	friendlyBulletList.push_back(this);
	lifetime = 0.8;
	moveSpeed = 700;
	moveBullet(moveSpeed);
}

void FriendlyBullet::removeBullet()
{
	//remove the bullet
	destroySprite();
	friendlyBulletList.erase(std::remove(friendlyBulletList.begin(), friendlyBulletList.end(), this), friendlyBulletList.end());
}

bool FriendlyBullet::isCollidingWith(ShootingShip* enemyShip)
{
	if (GameObject::isCollidingWith(enemyShip))
	{
		enemyShip->takeDamage();
		removeBullet(); //remove the bullet
		return true;
	}

	return false;
}

bool FriendlyBullet::isCollidingWith(MovingShip* enemyShip)
{
	if (GameObject::isCollidingWith(enemyShip))
	{
		enemyShip->takeDamage();
		removeBullet(); //remove the bullet
		return true;
	}

	return false;
}

bool FriendlyBullet::isCollidingWith(Planet* planet)
{
	if (GameObject::isCollidingWith(planet))
	{
		removeBullet();
		return true;
	}

	return false;
}

bool FriendlyBullet::isCollidingWith(Boss* boss)
{
	if (GameObject::isCollidingWith(boss))
	{
		removeBullet();
		boss->health--;
		boss->sprite->setZOrder(0);
		return true;
	}

	return false;
}

void FriendlyBullet::updatePhysics(float dt, Boss* boss)
{
	//call base class update
	Bullet::updatePhysics(dt);

	bool collision = false;
	for (int i = 0; i < ShootingShip::shootingShipList.size(); i++)
	{
		if (isCollidingWith(ShootingShip::shootingShipList[i]))
		{
			collision = true;
			break;
		}
	}
	if (!collision)
	{
		for (int i = 0; i < MovingShip::movingShipList.size(); i++)
		{
			if (isCollidingWith(MovingShip::movingShipList[i]))
			{
				collision = true;
				break;
			}
		}
	}
	if (!collision)
	{
		for (int i = 0; i < Planet::planetList.size(); i++)
		{
			if (isCollidingWith(Planet::planetList[i]))
			{
				collision = true;
				break;
			}
		}
	}
	if (!collision)
	{
		for (int i = 0; i < Boss::bossList.size(); i++)
		{
			if (isCollidingWith(Boss::bossList[i]))
			{
				collision = true;
				break;
			}
		}
	}


	//remove object if it's expired
	if (lifetime < 0 && !collision)
		removeBullet();
}