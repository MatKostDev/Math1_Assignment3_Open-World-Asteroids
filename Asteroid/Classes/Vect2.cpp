#include "Vect2.h"

Vect2::Vect2()
{
	x = 0.0f;
	y = 0.0f;
}

Vect2::Vect2(const float x, const float y)
{
	this->x = x;
	this->y = y;
}

Vect2::Vect2(cocos2d::Vec2 vector)
{
	x = vector.x;
	y = vector.y;
}

Vect2 Vect2::operator+(const Vect2 a) const
{
	Vect2 sum;
	sum.x = x + a.x;
	sum.y = y + a.y;

	return sum;
}

Vect2 Vect2::operator-(const Vect2 a) const
{
	Vect2 difference;
	difference.x = x - a.x;
	difference.y = y - a.y;

	return difference;
}

Vect2 Vect2::operator*(const Vect2 a) const
{
	Vect2 result;
	result.x = x * a.x;
	result.y = y * a.y;

	return result;
}

Vect2 Vect2::operator/(const Vect2 a) const
{
	Vect2 result;
	result.x = x / a.x;
	result.y = y / a.y;

	return result;
}

bool operator>(const Vect2 vector, const float scalar)
{
	if (vector.x > scalar && vector.y > scalar)
		return true;

	return false;
}

bool operator<(const Vect2 vector, const float scalar)
{
	if (vector.x < scalar && vector.y < scalar)
		return true;

	return false;
}

bool operator>(const Vect2 lhs, const Vect2 rhs)
{
	if (lhs.x > rhs.x && lhs.y > rhs.y)
		return true;

	return false;
}

bool operator<(const Vect2 lhs, const Vect2 rhs)
{
	if (lhs.x < rhs.x && lhs.y < rhs.y)
		return true;

	return false;
}

Vect2 operator+(const float a, const Vect2 b)
{
	Vect2 temp;
	temp.x = a + b.x;
	temp.y = a + b.y;

	return temp;
}

Vect2 operator-(const float a, const Vect2 b)
{
	Vect2 temp;
	temp.x = a - b.x;
	temp.y = a - b.y;

	return temp;
}

Vect2 Vect2::operator-() const
{
	Vect2 temp;
	temp.x = 0 - this->x;
	temp.y = 0 - this->y;

	return temp;
}

Vect2 Vect2::operator+=(const Vect2 a)
{
	*this = *this + a;
	return *this;
}

Vect2 Vect2::operator-=(const Vect2 a)
{
	*this = *this - a;
	return *this;
}

Vect2 Vect2::operator*=(const Vect2 a)
{
	*this = *this * a;
	return *this;
}

Vect2 Vect2::operator/=(const Vect2 a)
{
	*this = *this / a;
	return *this;
}

Vect2 Vect2::operator*(const float scalar) const
{
	Vect2 result;
	result.x = x * scalar;
	result.y = y * scalar;
	return result;
}

Vect2 Vect2::operator/(const float scalar) const
{
	Vect2 temp;
	temp.x = x / scalar;
	temp.y = y / scalar;
	return temp;
}

// this is the addition operator to add a vector to a float
Vect2 Vect2::operator+(const float rhs) const
{
	Vect2 result;
	result.x = x + rhs;
	result.y = y + rhs;

	return result;
}

// this is the subtraction operator to add a vector to a float
Vect2 Vect2::operator-(const float rhs) const
{
	Vect2 result;
	result.x = x - rhs;
	result.y = y - rhs;

	return result;
}

Vect2 Vect2::operator+=(const float a)
{
	*this = *this + a;
	return *this;
}

Vect2 Vect2::operator-=(const float a)
{
	*this = *this - a;
	return *this;
}

Vect2 Vect2::operator*=(const float a)
{
	*this = *this * a;
	return *this;
}

Vect2 Vect2::operator/=(const float a)
{
	*this = *this / a;
	return *this;
}

const float & Vect2::operator[](int index) const
{
	return (&x)[index];
}

float & Vect2::operator[](int index)
{
	return (&x)[index];
}

float Vect2::getMagnitudeSquared()
{
	return (x * x) + (y * y); //pythagorean theorum
}

float Vect2::dotProduct(const Vect2 rhs)
{
	return (x * rhs.x) + (y * rhs.y);
}

float Vect2::crossProduct(const Vect2 rhs)
{
	return (x * rhs.y) - (y * rhs.x);
}
