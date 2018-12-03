#include "EnemyBullet.h"

std::vector<EnemyBullet*> EnemyBullet::enemyBulletList = std::vector<EnemyBullet*>();

EnemyBullet::EnemyBullet(Vect2 position, float theta) : Bullet(position, theta, "EnemyBullet.png")
{
	enemyBulletList.push_back(this);
	lifetime = 1.8;
	moveSpeed = 400;
	moveBullet(moveSpeed);
}

void EnemyBullet::removeBullet()
{
	//remove the bullet
	destroySprite();
	enemyBulletList.erase(std::remove(enemyBulletList.begin(), enemyBulletList.end(), this), enemyBulletList.end());
}

void EnemyBullet::updatePhysics(float dt)
{
	//call base class update
	Bullet::updatePhysics(dt);

	//remove object if it's expired
	if (lifetime < 0)
	{
		destroySprite();
		enemyBulletList.erase(std::remove(enemyBulletList.begin(), enemyBulletList.end(), this), enemyBulletList.end());
	}
}