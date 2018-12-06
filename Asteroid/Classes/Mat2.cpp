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
	data[0][1] = 0;

	data[1][0] = 0;
	data[1][1] = a;
}

Mat2::Mat2(const float a, const float b, const float c, const float d)
{
	data[0][0] = a;
	data[0][1] = b;
	data[1][0] = c;
	data[1][1] = d;
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

Mat2 Mat2::operator=(const Mat2 a) const
{
	Mat2 temp;

	temp.data[0][0] = a.data[0][0];
	temp.data[0][1] = a.data[0][1];
	temp.data[1][0] = a.data[1][0];
	temp.data[1][1] = a.data[1][1];


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
	temp[0][1] = data[0][1] * scalar;
	temp[1][0] = data[1][0] * scalar;
	temp[1][1] = data[1][1] * scalar;

	return temp;
}

Mat2 Mat2::operator+(const float scalar) const
{
	Mat2 temp;

	temp[0][0] = data[0][0] + scalar;
	temp[0][1] = data[0][1] + scalar;
	temp[0][1] = data[1][0] + scalar;
	temp[0][1] = data[1][1] + scalar;

	return temp;
}

Mat2 Mat2::operator+=(const float scalar)
{
	data[0][0] = data[0][0] + scalar;
	data[0][1] = data[0][1] + scalar;
	data[1][0] = data[1][0] + scalar;
	data[1][1] = data[1][1] + scalar;

	return *this;
}

Mat2 Mat2::operator*=(const float scalar)
{
	data[0][0] = data[0][0] * scalar;
	data[0][1] = data[0][1] * scalar;
	data[1][0] = data[1][0] * scalar;
	data[1][1] = data[1][1] * scalar;

	return *this;
}

void Mat2::Rotate(const float theta) const
{
	float cosValue = cosf(theta);
	float sinValue = sinf(theta);

	*this = Mat2(data[0][0] * cosValue, data[0][1]*sinValue, data[1][0] * -sinValue, data[1][1] * cosValue);

}



	