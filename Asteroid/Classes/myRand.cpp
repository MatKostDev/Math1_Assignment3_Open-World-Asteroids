#include "myRand.h"

myRand::myRand()
{
}

myRand::~myRand()
{
}

//gets a random number
int myRand::getRandNum(int maxNum, int scaleNum, bool canBeNegative)
{
	int randNum = (rand() % maxNum) + scaleNum;

	//number can be a negative
	if (canBeNegative)
	{
		//check randomly for either a 1 or 0 to determine if number should be negative or not
		if (rand() % 2)
			randNum *= -1;
	}

	return randNum;
}

