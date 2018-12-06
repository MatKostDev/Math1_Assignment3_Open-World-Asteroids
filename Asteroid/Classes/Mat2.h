#include <Vect2.h>
#include <cocos2d.h>
#include <cmath>

class Mat2 {
public:
	Vect2 data[2];

	Mat2();
	Mat2(const float);
	Mat2(const float, const float, const float, const float);

	const Vect2& operator[] (int) const;
	Vect2& operator[](int);

	Mat2 operator+(const Mat2) const;
	Mat2 operator*(const Mat2) const;
	Mat2 operator=(const Mat2) const;

	Mat2 operator+=(const Mat2);
	Mat2 operator*=(const Mat2);

	Mat2 operator*(const float) const;
	Mat2 operator+(const float) const;

	Mat2 operator+=(const float);
	Mat2 operator*=(const float);
	
	void Rotate(const float) const;
	
};