#include <Vect2.h>
#include <cocos2d.h>
#include <cmath>

class Mat2 {
public:
	Vect2 data[2];
	
	Mat2();
	Mat2(const float a);

	const Vect2& operator[] (int index) const;
	Vect2& operator[](int index);

	Mat2 operator+(const Mat2 a) const;
	Mat2 operator*(const Mat2 a) const;

	Mat2 operator+=(const Mat2 a);
	Mat2 operator*=(const Mat2 a);

	Mat2 operator*(const float scalar) const;
	Mat2 operator+(const float scalar) const;
	
	Mat2 operator+=(const float scalar);
	Mat2 operator*=(const float scalar);

	Mat2 Transpose() const;
	Mat2 Determinent() const;
	Mat2 Inverse() const;
	Mat2 NonUniScale(const float scalar) const;
	Mat2 Rotate(const float scalar) const;


};
