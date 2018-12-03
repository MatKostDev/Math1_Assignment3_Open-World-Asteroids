#pragma once

#include "cocos2d.h"

class myRand
{
public:
	myRand();
	virtual ~myRand();

	static int getRandNum(int maxNum, int scaleNum, bool canBeNegative = false);
};