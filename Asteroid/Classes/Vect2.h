#pragma once
#include "cocos2d.h"

class Vect2
{
public:
	float x;
	float y;

	Vect2();
	Vect2(const float x, const float y);
	Vect2(cocos2d::Vec2 vector);

	Vect2 operator+(const Vect2 a) const;
	Vect2 operator-(const Vect2 a) const;
	Vect2 operator*(const Vect2 a) const;
	Vect2 operator/(const Vect2 a) const;

	Vect2 operator+=(const Vect2 a);
	Vect2 operator-=(const Vect2 a);
	Vect2 operator*=(const Vect2 a);
	Vect2 operator/=(const Vect2 a);

	Vect2 operator*(const float scalar) const;
	Vect2 operator/(const float scalar) const;
	Vect2 operator+(const float scalar) const;
	Vect2 operator-(const float scalar) const;

	Vect2 operator+=(const float scalar);
	Vect2 operator-=(const float scalar);
	Vect2 operator*=(const float scalar);
	Vect2 operator/=(const float scalar);

	friend bool operator> (const Vect2 vector, const float scalar);
	friend bool operator< (const Vect2 vector, const float scalar);

	friend bool operator> (const Vect2 lhs, const Vect2 rhs);
	friend bool operator< (const Vect2 lhs, const Vect2 rhs);

	friend Vect2 operator+(const float a, const Vect2 b);
	friend Vect2 operator-(const float a, const Vect2 b);

	Vect2 operator-() const;

	const float & Vect2::operator[](int index) const;
	float & Vect2::operator[](int index);

	float getMagnitudeSquared();
	float dotProduct(const Vect2 rhs);
	float crossProduct(const Vect2 rhs);
};