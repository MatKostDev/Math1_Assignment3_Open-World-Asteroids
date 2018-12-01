#pragma once
#include "GameObject.h"

class MovingShip : public GameObject
{
public:
	MovingShip(Vect2);

	const float MOVESPEED;

	static std::vector<MovingShip*> movingShipList;

	void updatePhysics(float dt, Vect2 shipPosition);
};

