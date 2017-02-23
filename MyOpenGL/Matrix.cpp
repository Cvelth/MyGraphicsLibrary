#include "Matrix.hpp"

template<typename Type>
mgl::AbstractMatrix<Type>::AbstractMatrix(const Type & e00, const Type & e01, const Type & e02, const Type & e03, 
										  const Type & e10, const Type & e11, const Type & e12, const Type & e13, 
										  const Type & e20, const Type & e21, const Type & e22, const Type & e23, 
										  const Type & e30, const Type & e31, const Type & e32, const Type & e33) 
	: m_data[0][0](e00), m_data[0][1](e01), m_data[0][2](e02), m_data[0][3](e03),
	  m_data[1][0](e10), m_data[1][1](e11), m_data[1][2](e12), m_data[1][3](e13),
	  m_data[2][0](e20), m_data[2][1](e21), m_data[2][2](e22), m_data[2][3](e23),
	  m_data[3][0](e30), m_data[3][1](e31), m_data[3][2](e32), m_data[3][3](e33) {	  
}


template<typename Type>
mgl::AbstractMatrix<Type>::AbstractMatrix(const Type * const m)
	: m_data[0][0](m_data[0][0]), m_data[0][1](m_data[0][1]), m_data[0][2](m_data[0][2]), m_data[0][3](m_data[0][3]),
	  m_data[1][0](m_data[1][0]), m_data[1][1](m_data[1][1]), m_data[1][2](m_data[1][2]), m_data[1][3](m_data[1][3]),
	  m_data[2][0](m_data[2][0]), m_data[2][1](m_data[2][1]), m_data[2][2](m_data[2][2]), m_data[2][3](m_data[2][3]),
	  m_data[3][0](m_data[3][0]), m_data[3][1](m_data[3][1]), m_data[3][2](m_data[3][2]), m_data[3][3](m_data[3][3]) {
}	  

template<typename Type>
const mgl::AbstractVector<Type>& mgl::AbstractMatrix<Type>::column(const size_t & c) const {
	return mgl::AbstractVector(m_data[0][c], m_data[1][c], m_data[2][c], m_data[3][c]);
}
template<typename Type>
const mgl::AbstractVector<Type>& mgl::AbstractMatrix<Type>::row(const size_t & c) const {
	return mgl::AbstractVector(m_data[c][0], m_data[c][1], m_data[c][2], m_data[c][3]);
}

template<typename Type>
Type * mgl::AbstractMatrix<Type>::data() {
	return m_data;
}
template<typename Type>
const Type * mgl::AbstractMatrix<Type>::data() const {
	return m_data;
}
template<typename Type>
void mgl::AbstractMatrix<Type>::fill(const Type & v) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m_data[i][j] = v;
}

template<typename Type>
const Type & mgl::AbstractMatrix<Type>::determinant() const {
	return m_data[0][3] * m_data[1][2] * m_data[2][1] * m_data[3][0] - m_data[0][2] * m_data[1][3] * m_data[2][1] * m_data[3][0] -
		   m_data[0][3] * m_data[1][1] * m_data[2][2] * m_data[3][0] + m_data[0][1] * m_data[1][3] * m_data[2][2] * m_data[3][0] +
		   m_data[0][2] * m_data[1][1] * m_data[2][3] * m_data[3][0] - m_data[0][1] * m_data[1][2] * m_data[2][3] * m_data[3][0] -
		   m_data[0][3] * m_data[1][2] * m_data[2][0] * m_data[3][1] + m_data[0][2] * m_data[1][3] * m_data[2][0] * m_data[3][1] +
		   m_data[0][3] * m_data[1][0] * m_data[2][2] * m_data[3][1] - m_data[0][0] * m_data[1][3] * m_data[2][2] * m_data[3][1] -
		   m_data[0][2] * m_data[1][0] * m_data[2][3] * m_data[3][1] + m_data[0][0] * m_data[1][2] * m_data[2][3] * m_data[3][1] +
		   m_data[0][3] * m_data[1][1] * m_data[2][0] * m_data[3][2] - m_data[0][1] * m_data[1][3] * m_data[2][0] * m_data[3][2] -
		   m_data[0][3] * m_data[1][0] * m_data[2][1] * m_data[3][2] + m_data[0][0] * m_data[1][3] * m_data[2][1] * m_data[3][2] +
		   m_data[0][1] * m_data[1][0] * m_data[2][3] * m_data[3][2] - m_data[0][0] * m_data[1][1] * m_data[2][3] * m_data[3][2] -
		   m_data[0][2] * m_data[1][1] * m_data[2][0] * m_data[3][3] + m_data[0][1] * m_data[1][2] * m_data[2][0] * m_data[3][3] +
		   m_data[0][2] * m_data[1][0] * m_data[2][1] * m_data[3][3] - m_data[0][0] * m_data[1][2] * m_data[2][1] * m_data[3][3] -
		   m_data[0][1] * m_data[1][0] * m_data[2][2] * m_data[3][3] + m_data[0][0] * m_data[1][1] * m_data[2][2] * m_data[3][3];
}

template<typename Type>
const mgl::AbstractMatrix<Type>& mgl::AbstractMatrix<Type>::orthographicMatrix(const Type & left, const Type & right, const Type & top, const Type & bottom, const Type & near, const Type &) {
	return AbstractMatrix<Type>(2.0 / (right - left), 0, 0, -(right + left) / (right - left),
								0, 2.0 / (top - bottom), 0, -(top + bottom) / (top - bottom),
								0, 0, -2.0 / (far - near), -(far + near) / (far - near),
								0, 0, 0, 1);
}

template<typename Type>
const mgl::AbstractMatrix<Type>& mgl::AbstractMatrix<Type>::orthographicUnprojectionMatrix(const Type & left, const Type & right, const Type & top, const Type & bottom, const Type & near, const Type &) {
	return AbstractMatrix<Type>((right - left) / 2.0, 0, 0, (right + left) / 2.0,
								0, (top - bottom) / 2.0, 0, (top + bottom) / 2.0,
								0, 0, -(far - near) / 2.0, (far + near) / 2.0,
								0, 0, 0, 1);
}

template<typename Type>
const mgl::AbstractMatrix<Type>& mgl::AbstractMatrix<Type>::perspectiveMatrix(const Type & left, const Type & right, const Type & top, const Type & bottom, const Type & near, const Type &) {
	return AbstractMatrix<Type>(2.0 * near / (right - left), 0, (right + left) / (right - left), 0,
								0, 2.0 * near / (top - bottom), (top + bottom) / (top - bottom), 0,
								0, 0, -(far + near) / (far - near), -2.0 * far * near/ (far - near),
								0, 0, -1, 0);
}

template<typename Type>
const mgl::AbstractMatrix<Type>& mgl::AbstractMatrix<Type>::translationMatrix(const AbstractVector<Type>& v) {
	return translationMatrix(v.x(), v.y(), v.z());
}
template<typename Type>
const mgl::AbstractMatrix<Type>& mgl::AbstractMatrix<Type>::translationMatrix(const Type & x, const Type & y, const Type & z) {
	return AbstractMatrix<Type>(1, 0, 0, x,
								0, 1, 0, y,
								0, 0, 1, z,
								0, 0, 0, 1);
}

template<typename Type>
const mgl::AbstractMatrix<Type>& mgl::AbstractMatrix<Type>::rotationMatrix(const Type & angle, const AbstractVector<Type>& v) {
	Type const c = cos(angle);
	Type const s = sin(angle);
	AbstractVector<Type> t = v.normalized() * (Type(1) - c);
	return mgl::AbstractMatrix(c + t.x() * v.x(), t.x() * v.y() + s * v.z(),
							   t.x() * v.y() - s * v.y(), 0,

							   t.y() * v.x() - s * v.y(), c + t.y() * v.y(),
							   t.y() * v.z() + s * v.x(), 0,

							   t.z() * v.x() + s * v.y(), t.z() * v.y() - s * v.x(),
							   c + t.z() * v.z(), 0,

							   0, 0, 0, 0);
}
template<typename Type>
const mgl::AbstractMatrix<Type>& mgl::AbstractMatrix<Type>::rotationMatrix(const Type & angle, const Type & x, const Type & y, const Type & z) {
	return AbstractMatrix<Type>(angle, mgl::AbstractVector<Type>(x, y, z));
}

template<typename Type>
const mgl::AbstractMatrix<Type>& mgl::AbstractMatrix<Type>::scalingMatrix(const Type & q) {
	return AbstractMatrix<Type>(q, q, q);
}
template<typename Type>
const mgl::AbstractMatrix<Type>& mgl::AbstractMatrix<Type>::scalingMatrix(const Type & x, const Type & y, const Type & z) {
	return AbstractMatrix<Type>(x, 0, 0, 0,
								0, y, 0, 0,
								0, 0, z, 0,
								0, 0, 0, 1);
}
template<typename Type>
const mgl::AbstractMatrix<Type>& mgl::AbstractMatrix<Type>::scalingMatrix(const AbstractVector<Type>& v) {
	return AbstractMatrix<Type>(v.x(), v.y(), v.z());
}

template<typename Type>
bool mgl::AbstractMatrix<Type>::operator==(const AbstractMatrix<Type>& matrix) {
	return !operator!=(matrix);
}
template<typename Type>
bool mgl::AbstractMatrix<Type>::operator!=(const AbstractMatrix<Type>& matrix) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (m_data[i][j] == matrix.m_data[i][j])
				return false;
	return true;
}

template<typename Type>
mgl::AbstractMatrix<Type>& mgl::AbstractMatrix<Type>::operator+=(const AbstractMatrix<Type>& matrix) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m_data[i][j] += matrix.m_data[i][j];
	return this;
}
template<typename Type>
mgl::AbstractMatrix<Type>& mgl::AbstractMatrix<Type>::operator-=(const AbstractMatrix<Type>& matrix) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m_data[i][j] -= matrix.m_data[i][j];
	return this;
}
template<typename Type>
mgl::AbstractMatrix<Type>& mgl::AbstractMatrix<Type>::operator*=(const AbstractMatrix<Type>& matrix) {
	//ToDo
}
template<typename Type>
mgl::AbstractMatrix<Type>& mgl::AbstractMatrix<Type>::operator*=(const Type& q) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m_data[i][j] *= q;
	return this;
}
template<typename Type>
mgl::AbstractMatrix<Type>& mgl::AbstractMatrix<Type>::operator/=(const Type& q) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m_data[i][j] /= q;
	return this;
}