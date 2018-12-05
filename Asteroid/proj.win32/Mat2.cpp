#include "Mat2.h" 

Mat2::Mat2()
{
	data[0][0] = 1;
	data[0][1] = 0;

	data[1][0] = 0;
	data[1][1] = 1;
}

Mat2::Mat2(const float a)
{
	data[0][0] = a;
	data[0][1] = a;

	data[1][0] = a;
	data[1][1] = a;
}

const Vect2 & Mat2::operator[](int index) const
{
	return data[index];
}

Vect2 & Mat2::operator[](int index)
{
	return data[index];
}

Mat2 Mat2::operator+(const Mat2 a) const
{
	Mat2 temp;

	temp[0] = data[0] + a[0];
	temp[1] = data[1] + a[1];

	return temp;
}

Mat2 Mat2::operator*(const Mat2 a) const
{
	Mat2 temp;

	temp[0][0] = data[0][0] * a[0][0] + data[1][0] * a[0][1];
	temp[1][0] = data[0][0] * a[1][0] + data[1][0] * a[1][1];

	temp[0][1] = data[0][1] * a[0][0] + data[1][1] * a[0][1];
	temp[1][1] = data[0][1] * a[1][0] + data[1][1] * a[1][1];

	return temp;
}

Mat2 Mat2::operator+=(const Mat2 a)
{
	*this = *this + a;
	return *this;
}

Mat2 Mat2::operator*=(const Mat2 a)
{
	*this = *this * a;
	return *this;
}

Mat2 Mat2::operator*(const float scalar) const
{
	Mat2 temp;

	temp[0][0] = data[0][0] * scalar;
	temp[0][1] = data[0][1];
	temp[1][0] = data[1][0];
	temp[1][1] = data[1][1] * scalar;

	return temp;
}

Mat2 Mat2::operator+(const float scalar) const
{
	Mat2 temp;

	temp[0][0] = data[0][0] + scalar;
	temp[0][1] = data[0][1];
	temp[0][1] = data[1][0];
	temp[0][1] = data[1][1] + scalar;

	return temp;
}

Mat2 Mat2::operator+=(const float scalar)
{
	data[0][0] = data[0][0] + scalar;
	data[0][1] = data[0][1];
	data[1][0] = data[1][0];
	data[1][1] = data[1][1] + scalar;

	return *this;
}

Mat2 Mat2::operator*=(const float scalar)
{
	data[0][0] = data[0][0] * scalar;
	data[0][1] = data[0][1];
	data[1][0] = data[1][0];
	data[1][1] = data[1][1] * scalar;

	return *this;
}

Mat2 Mat2::Transpose() const
{
	Mat2 temp;

	temp[0][0] = data[0][0];
	temp[0][1] = data[1][1];
	temp[1][0] = data[1][0];
	temp[1][1] = data[0][1];

	return temp;

}
