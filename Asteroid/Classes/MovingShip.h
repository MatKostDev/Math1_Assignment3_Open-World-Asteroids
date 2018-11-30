#pragma once
#include "GameObject.h"

class MovingShip : public GameObject
{
public:
	MovingShip(Vect2);

	float theta;

	void updatePhysics(float dt, Vect2 shipPosition);
};

