#pragma once
#include "GameObject.h"
#include "EnemyBullet.h"
class Boss : public GameObject
{
public:
	Boss(Vect2 position);

	const float ACTION_TIME;
	const float SHOT_DELAY;

	float shootDelay;

	float actionOneTimer;
	float actionOneCountdown;
	float actionOneIncrease;

	float actionTwoTimer;
	float actionTwoCountdown;
	float actionTwoIncrease;

	float bulletTheta;
	int health;

	void shootBullet(Scene* myScene);
	void updatePhysics(float dt, Scene* myScene, Vect2 shipPosition);
};