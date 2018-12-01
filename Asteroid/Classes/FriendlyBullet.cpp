#include "FriendlyBullet.h"

std::vector<FriendlyBullet*> FriendlyBullet::friendlyBulletList = std::vector<FriendlyBullet*>();

FriendlyBullet::FriendlyBullet(Vect2 position, float theta) : Bullet(position, theta, "FriendlyBullet.png")
{
	friendlyBulletList.push_back(this);
	lifetime = 1;
	moveSpeed = 700;
	moveBullet(moveSpeed);
}

void FriendlyBullet::updatePhysics(float dt)
{
	//call base class update
	Bullet::updatePhysics(dt);

	//remove object if it's expired
	if (lifetime < 0)
	{
		destroySprite();
		friendlyBulletList.erase(std::remove(friendlyBulletList.begin(), friendlyBulletList.end(), this), friendlyBulletList.end());
	}
}