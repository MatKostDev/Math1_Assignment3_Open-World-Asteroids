#include "Boss.h"

Boss::Boss(Vect2 position) : GameObject(position, "Boss.png"), ACTION_TIME(10), SHOT_DELAY(0.1)
{
	actionOneTimer = 1;
	actionOneCountdown = ACTION_TIME;
	actionOneIncrease = 25;

	actionTwoTimer = ACTION_TIME + 1;
	actionTwoCountdown = ACTION_TIME;
	actionTwoIncrease = 200;

	bulletTheta = 0;
	shootDelay = 0;
	health = 90;
}

void Boss::removeObject()
{
}

void Boss::shootBullet(Scene* myScene)
{
	EnemyBullet* newEnemyBullet = new EnemyBullet(Vect2(sprite->getPosition()), bulletTheta);
	EnemyBullet::enemyBulletList.push_back(newEnemyBullet);
	myScene->addChild(newEnemyBullet->sprite, 6);
}

void Boss::updatePhysics(float dt, Scene* myScene, Vect2 shipPosition)
{
	GameObject::updatePhysics(dt);

	sprite->setZOrder(8);

	actionOneTimer -= dt;
	actionTwoTimer -= dt;

	//check for the first action
	if (actionOneTimer < 0)
	{
		actionOneCountdown -= dt;

		if (shootDelay > SHOT_DELAY)
		{
			for (int i = 0; i < 8; i++)
			{
				bulletTheta += i * 45;
				shootBullet(myScene);
			}
			shootDelay = 0;
		}

		//check for reset
		if (actionOneCountdown < 0)
		{
			actionOneCountdown = ACTION_TIME * 2;
			actionOneTimer = ACTION_TIME;
		}

		bulletTheta += actionOneIncrease * dt;
		shootDelay += dt;
	}
	//check for second action
	else if (actionTwoTimer < 0)
	{
		actionOneCountdown -= dt;

		if (shootDelay > SHOT_DELAY)
		{
			for (int i = 0; i < 8; i++)
			{
				bulletTheta += i * 45;
				shootBullet(myScene);
			}
			shootDelay = 0;
		}

		//check for reset
		if (actionOneCountdown < 0)
		{
			actionOneCountdown = ACTION_TIME * 2;
			actionOneTimer = ACTION_TIME;
		}

		bulletTheta += actionTwoIncrease * dt;
		shootDelay += dt;
	}

	//phase two
	if (health < 60)
	{
		//have the boss rotate to follow our ship
		Vect2 distance = shipPosition - getPosition(); //calculate distance vector between the two ships
		theta = (atan2(distance.x, distance.y) * 180 / M_PI); //perform atan2 (returns the angle in rad between the positive x axis (1, 0) and the point provided) on the distance and convert to degrees

		velocity = Vect2(
			sinf(theta / 180 * M_PI),
			cosf(theta / 180 * M_PI))
			* dt * 4000;
	}

	//phase three
	if (health < 30)
	{
		actionOneIncrease += 20;
		actionTwoIncrease += 50;
	}

	//check if boss is dead
	if (health <= 0)
		destroySprite();
}
