#include "Vector.hpp"

template<typename Type>
mgl::AbstractVector<Type>::AbstractVector(const Type & x, const Type & y, const Type & z, const Type & w)
	: m_data[0](x), m_data[1](y), m_data[2](z), m_data[3](w) {
}

template<typename Type>
mgl::AbstractVector<Type>::AbstractVector(const Type * const data) 
	: m_data[0](data[0]), m_data[1](data[1]), m_data[2](data[2]), m_data[3](data[3]) {
}

template<typename Type>
bool mgl::AbstractVector<Type>::isNull() const {
	for (int i = 0; i < 4; i++)
		if (m_data[i] != 0)
			return false;
	return true;
}

template<typename Type>
Type mgl::AbstractVector<Type>::length() const {
	Type res = 0;
	for (int i = 0; i < 4; i++)
		res += m_data[i] * m_data[i];
	return sqrt(res);
}

template<typename Type>
void mgl::AbstractVector<Type>::normalize() {
	Type l = length();
	for (int i = 0; i < 4; i++)
		m_data[i] /= l;
}

template<typename Type>
const mgl::AbstractVector<Type> mgl::AbstractVector<Type>::normalized() const {
	return mgl::AbstractVector<Type>(*this / length());
}

template<typename Type>
void mgl::AbstractVector<Type>::x(const Type & t) {
	m_data[0] = t;
}

template<typename Type>
void mgl::AbstractVector<Type>::y(const Type & t) {
	m_data[1] = t;
}

template<typename Type>
void mgl::AbstractVector<Type>::z(const Type & t) {
	m_data[2] = t;
}

template<typename Type>
void mgl::AbstractVector<Type>::w(const Type & t) {
	m_data[3] = t;
}

template<typename Type>
void mgl::AbstractVector<Type>::set(const Type & x, const Type & y, const Type & z, const Type & w) {
	m_data[0] = x;
	m_data[1] = y;
	m_data[2] = z;
	m_data[3] = w;
}

template<typename Type>
const Type & mgl::AbstractVector<Type>::x() const {
	return m_data[0];
}

template<typename Type>
const Type * const mgl::AbstractVector<Type>::get() const {
	return m_data;
}

template<typename Type>
mgl::AbstractVector<Type>& mgl::AbstractVector<Type>::operator+=(const AbstractVector<Type>& vector) {
	for (int i = 0; i < 4; i++)
		m_data[i] += vector.m_data[i];
	return this;
}

template<typename Type>
mgl::AbstractVector<Type>& mgl::AbstractVector<Type>::operator-=(const AbstractVector<Type>& vector) {
	for (int i = 0; i < 4; i++)
		m_data[i] -= vector.m_data[i];
	return this;
}

template<typename Type>
mgl::AbstractVector<Type>& mgl::AbstractVector<Type>::operator*=(const Type & q) {
	for (int i = 0; i < 4; i++)
		m_data[i] *= q;
	return this;
}

template<typename Type>
mgl::AbstractVector<Type>& mgl::AbstractVector<Type>::operator/=(const Type & q) {
	for (int i = 0; i < 4; i++)
		m_data[i] /= q;
	return this;
}

template<typename Type>
bool mgl::AbstractVector<Type>::operator==(const AbstractVector<Type>& vector) {
	return !operator!=(vector);
}

template<typename Type>
bool mgl::AbstractVector<Type>::operator!=(const AbstractVector<Type>& vector) {
	for (int i = 0; i < 4; i++)
		if (vector.m_data[i] == m_data[i])
			return false;
	return true;
}

template<typename Type>
const Type & mgl::AbstractVector<Type>::y() const {
	return m_data[1];
}

template<typename Type>
const Type & mgl::AbstractVector<Type>::z() const {
	return m_data[2];
}

template<typename Type>
const Type & mgl::AbstractVector<Type>::w() const {
	return m_data[3];
}

template<typename Type>
const mgl::AbstractVector<Type> mgl::operator+(const AbstractVector<Type>& v1, const AbstractVector<Type>& v2) {
	AbstractVector<Type> res;
	for (int i = 0; i < 4; i++)
		res.m_data[i] = v1.m_data[i] + v2.m_data[i];
	return res;
}

template<typename Type>
const mgl::AbstractVector<Type> mgl::operator-(const AbstractVector<Type>& v1, const AbstractVector<Type>& v2) {
	AbstractVector<Type> res;
	for (int i = 0; i < 4; i++)
		res.m_data[i] = v1.m_data[i] - v2.m_data[i];
	return res;
}

template<typename Type>
const mgl::AbstractVector<Type> mgl::operator*(const AbstractVector<Type>& v1, const Type & q) {
	AbstractVector<Type> res;
	for (int i = 0; i < 4; i++)
		res.m_data[i] = v1.m_data[i] * q;
	return res;
}

template<typename Type>
const mgl::AbstractVector<Type> mgl::operator*(const Type & q, const AbstractVector<Type>& v1) {
	return v1 * q;
}

template<typename Type>
const mgl::AbstractVector<Type> mgl::operator/(const AbstractVector<Type>& v1, const Type & q) {
	AbstractVector<Type> res;
	for (int i = 0; i < 4; i++)
		res.m_data[i] = v1.m_data[i] / q;
	return res;
}

template<typename Type>
const Type mgl::operator*(const AbstractVector<Type>& v1, const AbstractVector<Type>& v2) {
	Type res = 0;
	for (int i = 0; i < 4; i++)
		res += v1.m_data[i] * v2.m_data[i];
	return res;
}
