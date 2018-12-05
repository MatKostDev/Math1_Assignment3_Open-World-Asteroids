#pragma once
#include "GameObject.h"
#include "EnemyBullet.h"

class Planet : public GameObject
{
public:
	Planet(Vect2 position);

	float theta;
	float shootTimer;
	static std::vector<Planet*> planetList;

	EnemyBullet* shootBullet();
	void removeObject();
	void updatePhysics(float dt, Vect2 shipPosition);
};