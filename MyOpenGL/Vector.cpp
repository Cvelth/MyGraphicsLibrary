#include "Vector.hpp"
#include "boost\qvm\vec.hpp"

mgl::Vector::Vector(float x, float y, float z, float w) {
	m_data[0] = x;
	m_data[1] = y;
	m_data[2] = z;
	m_data[3] = w;
}
mgl::Vector::Vector(const float * const data) : Vector(data[0], data[1], data[2], data[3]) {}
mgl::Vector::Vector(const Vector & v) : Vector(v.x(), v.y(), v.z(), v.w()) {}
mgl::Vector::Vector(Vector && v) : Vector(v.x(), v.y(), v.z(), v.w()) {}

bool mgl::Vector::isNull() const {
	for (int i = 0; i < 4; i++)
		if (m_data[i] != 0)
			return false;
	return true;
}
float mgl::Vector::length() const {
	float res = 0;
	for (int i = 0; i < 4; i++)
		res += m_data[i] * m_data[i];
	return sqrt(res);
}
void mgl::Vector::normalize() {
	float l = length();
	for (int i = 0; i < 4; i++)
		m_data[i] /= l;
}
const mgl::Vector mgl::Vector::normalized() const {
	return Vector(*this / length());
}

mgl::Vector & mgl::Vector::operator+=(const Vector & vector) {
	for (int i = 0; i < 4; i++)
		m_data[i] += vector.m_data[i];
	return *this;
}
mgl::Vector & mgl::Vector::operator-=(const Vector & vector) {
	for (int i = 0; i < 4; i++)
		m_data[i] -= vector.m_data[i];
	return *this;
}
mgl::Vector & mgl::Vector::operator*=(const float & q) {
	for (int i = 0; i < 4; i++)
		m_data[i] *= q;
	return *this;
}
mgl::Vector & mgl::Vector::operator/=(const float & q) {
	for (int i = 0; i < 4; i++)
		m_data[i] /= q;
	return *this;
}
bool mgl::Vector::operator==(const Vector & vector) { 
	return !operator!=(vector); 
}
bool mgl::Vector::operator!=(const Vector & vector) {
	for (int i = 0; i < 4; i++)
		if (vector.m_data[i] == m_data[i])
			return false;
	return true;
}

const mgl::Vector mgl::operator+(const Vector & v1, const Vector & v2) {
	Vector res = v1;
	for (int i = 0; i < 4; i++)
		res.m_data[i] += v2.m_data[i];
	return res;
}
const mgl::Vector mgl::operator-(const Vector & v1, const Vector & v2) {
	Vector res = v1;
	for (int i = 0; i < 4; i++)
		res.m_data[i] -= v2.m_data[i];
	return res;
}
const mgl::Vector mgl::operator*(const Vector & v1, const float & q) {
	Vector res = v1;
	for (int i = 0; i < 4; i++)
		res.m_data[i] *= q;
	return res;
}
const mgl::Vector mgl::operator*(const float & q, const Vector & v1) {
	return v1 * q;
}
const mgl::Vector mgl::operator/(const Vector & v1, const float & q) {
	Vector res = v1;
	for (int i = 0; i < 4; i++)
		res.m_data[i] /= q;
	return res;
}
const float mgl::operator*(const Vector& v1, const Vector& v2) {
	float res = 0;
	for (int i = 0; i < 4; i++)
		res += v1[i] * v2[i];
	return res;
}