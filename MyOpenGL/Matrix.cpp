#include "Matrix.hpp"

template<typename Type>
mgl::AbstractMatrix<Type>::AbstractMatrix(const Type & e00, const Type & e01, const Type & e02, const Type & e03,
										  const Type & e10, const Type & e11, const Type & e12, const Type & e13,
										  const Type & e20, const Type & e21, const Type & e22, const Type & e23,
										  const Type & e30, const Type & e31, const Type & e32, const Type & e33)
	: m_data ({e00, e01, e02, e03, e10, e11, e12, e13,
			   e20, e21, e22, e23, e30, e31, e32, e33}) {
}


template<typename Type>
mgl::AbstractMatrix<Type>::AbstractMatrix(const Type * const m)
	: m_data(m) {
}

template<typename Type>
mgl::AbstractMatrix<Type>::AbstractMatrix(const Type& v)
	: m_data({v, v, v, v, v, v, v, v,
			  v, v, v, v, v, v, v, v}) {
}

template<typename Type>
mgl::AbstractMatrix<Type>::AbstractMatrix(InitialValue i)
	: m_data({i, 0, 0, 0, 0, i, 0, 0,
			  0, 0, i, 0, 0, 0, 0, i}) {
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
	m_data[0][0] = m_data[0][0]*matrix.m_data[0][0] + m_data[1][0]*matrix.m_data[0][1] + m_data[2][0]*matrix.m_data[0][2] + m_data[3][0]*matrix.m_data[0][3];
	m_data[0][1] = m_data[0][1]*matrix.m_data[0][0] + m_data[1][1]*matrix.m_data[0][1] + m_data[2][1]*matrix.m_data[0][2] + m_data[3][1]*matrix.m_data[0][3];
	m_data[0][2] = m_data[0][2]*matrix.m_data[0][0] + m_data[1][2]*matrix.m_data[0][1] + m_data[2][2]*matrix.m_data[0][2] + m_data[3][2]*matrix.m_data[0][3];
	m_data[0][3] = m_data[0][3]*matrix.m_data[0][0] + m_data[1][3]*matrix.m_data[0][1] + m_data[2][3]*matrix.m_data[0][2] + m_data[3][3]*matrix.m_data[0][3];

	m_data[1][0] = m_data[0][0]*matrix.m_data[1][0] + m_data[1][0]*matrix.m_data[1][1] + m_data[2][0]*matrix.m_data[1][2] + m_data[3][0]*matrix.m_data[1][3];
	m_data[1][1] = m_data[0][1]*matrix.m_data[1][0] + m_data[1][1]*matrix.m_data[1][1] + m_data[2][1]*matrix.m_data[1][2] + m_data[3][1]*matrix.m_data[1][3];
	m_data[1][2] = m_data[0][2]*matrix.m_data[1][0] + m_data[1][2]*matrix.m_data[1][1] + m_data[2][2]*matrix.m_data[1][2] + m_data[3][2]*matrix.m_data[1][3];
	m_data[1][3] = m_data[0][3]*matrix.m_data[1][0] + m_data[1][3]*matrix.m_data[1][1] + m_data[2][3]*matrix.m_data[1][2] + m_data[3][3]*matrix.m_data[1][3];

	m_data[2][0] = m_data[0][0]*matrix.m_data[2][0] + m_data[1][0]*matrix.m_data[2][1] + m_data[2][0]*matrix.m_data[2][2] + m_data[3][0]*matrix.m_data[2][3];
	m_data[2][1] = m_data[0][1]*matrix.m_data[2][0] + m_data[1][1]*matrix.m_data[2][1] + m_data[2][1]*matrix.m_data[2][2] + m_data[3][1]*matrix.m_data[2][3];
	m_data[2][2] = m_data[0][2]*matrix.m_data[2][0] + m_data[1][2]*matrix.m_data[2][1] + m_data[2][2]*matrix.m_data[2][2] + m_data[3][2]*matrix.m_data[2][3];
	m_data[2][3] = m_data[0][3]*matrix.m_data[2][0] + m_data[1][3]*matrix.m_data[2][1] + m_data[2][3]*matrix.m_data[2][2] + m_data[3][3]*matrix.m_data[2][3];

	m_data[3][0] = m_data[0][0]*matrix.m_data[3][0] + m_data[1][0]*matrix.m_data[3][1] + m_data[2][0]*matrix.m_data[3][2] + m_data[3][0]*matrix.m_data[3][3];
	m_data[3][1] = m_data[0][1]*matrix.m_data[3][0] + m_data[1][1]*matrix.m_data[3][1] + m_data[2][1]*matrix.m_data[3][2] + m_data[3][1]*matrix.m_data[3][3];
	m_data[3][2] = m_data[0][2]*matrix.m_data[3][0] + m_data[1][2]*matrix.m_data[3][1] + m_data[2][2]*matrix.m_data[3][2] + m_data[3][2]*matrix.m_data[3][3];
	m_data[3][3] = m_data[0][3]*matrix.m_data[3][0] + m_data[1][3]*matrix.m_data[3][1] + m_data[2][3]*matrix.m_data[3][2] + m_data[3][3]*matrix.m_data[3][3];

	return this;
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

template<typename Type>
Type & mgl::AbstractMatrix<Type>::operator()(size_t row, size_t col) {
	return m_data[row][col];
}
template<typename Type>
const Type & mgl::AbstractMatrix<Type>::operator()(size_t row, size_t col) const {
	return m_data[row][col];
}

template<typename Type>
const mgl::AbstractMatrix<Type>& mgl::operator+(const AbstractMatrix<Type>& m1, const AbstractMatrix<Type>& m2) {
	AbstractMatrix<Type> res(m1);
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 4; j++)
			res[i][j] += m2[i][j];
	return res;
}

template<typename Type>
const mgl::AbstractMatrix<Type>& mgl::operator-(const AbstractMatrix<Type>& m1, const AbstractMatrix<Type>& m2) {
	AbstractMatrix<Type> res(m1);
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 4; j++)
			res[i][j] -= m2[i][j];
	return res;
}

template<typename Type>
const mgl::AbstractMatrix<Type>& mgl::operator*(const AbstractMatrix<Type>& m1, const AbstractMatrix<Type>& m2) {
	AbstractMatrix<Type> res(UnitializedMatrix);

	res.m_data[0][0] = m1.m_data[0][0] * m2.m_data[0][0] + m1.m_data[1][0] * m2.m_data[0][1] + m1.m_data[2][0] * m2.m_data[0][2] + m1.m_data[3][0] * m2.m_data[0][3];
	res.m_data[0][1] = m1.m_data[0][1] * m2.m_data[0][0] + m1.m_data[1][1] * m2.m_data[0][1] + m1.m_data[2][1] * m2.m_data[0][2] + m1.m_data[3][1] * m2.m_data[0][3];
	res.m_data[0][2] = m1.m_data[0][2] * m2.m_data[0][0] + m1.m_data[1][2] * m2.m_data[0][1] + m1.m_data[2][2] * m2.m_data[0][2] + m1.m_data[3][2] * m2.m_data[0][3];
	res.m_data[0][3] = m1.m_data[0][3] * m2.m_data[0][0] + m1.m_data[1][3] * m2.m_data[0][1] + m1.m_data[2][3] * m2.m_data[0][2] + m1.m_data[3][3] * m2.m_data[0][3];

	res.m_data[1][0] = m1.m_data[0][0] * m2.m_data[1][0] + m1.m_data[1][0] * m2.m_data[1][1] + m1.m_data[2][0] * m2.m_data[1][2] + m1.m_data[3][0] * m2.m_data[1][3];
	res.m_data[1][1] = m1.m_data[0][1] * m2.m_data[1][0] + m1.m_data[1][1] * m2.m_data[1][1] + m1.m_data[2][1] * m2.m_data[1][2] + m1.m_data[3][1] * m2.m_data[1][3];
	res.m_data[1][2] = m1.m_data[0][2] * m2.m_data[1][0] + m1.m_data[1][2] * m2.m_data[1][1] + m1.m_data[2][2] * m2.m_data[1][2] + m1.m_data[3][2] * m2.m_data[1][3];
	res.m_data[1][3] = m1.m_data[0][3] * m2.m_data[1][0] + m1.m_data[1][3] * m2.m_data[1][1] + m1.m_data[2][3] * m2.m_data[1][2] + m1.m_data[3][3] * m2.m_data[1][3];

	res.m_data[2][0] = m1.m_data[0][0] * m2.m_data[2][0] + m1.m_data[1][0] * m2.m_data[2][1] + m1.m_data[2][0] * m2.m_data[2][2] + m1.m_data[3][0] * m2.m_data[2][3];
	res.m_data[2][1] = m1.m_data[0][1] * m2.m_data[2][0] + m1.m_data[1][1] * m2.m_data[2][1] + m1.m_data[2][1] * m2.m_data[2][2] + m1.m_data[3][1] * m2.m_data[2][3];
	res.m_data[2][2] = m1.m_data[0][2] * m2.m_data[2][0] + m1.m_data[1][2] * m2.m_data[2][1] + m1.m_data[2][2] * m2.m_data[2][2] + m1.m_data[3][2] * m2.m_data[2][3];
	res.m_data[2][3] = m1.m_data[0][3] * m2.m_data[2][0] + m1.m_data[1][3] * m2.m_data[2][1] + m1.m_data[2][3] * m2.m_data[2][2] + m1.m_data[3][3] * m2.m_data[2][3];

	res.m_data[3][0] = m1.m_data[0][0] * m2.m_data[3][0] + m1.m_data[1][0] * m2.m_data[3][1] + m1.m_data[2][0] * m2.m_data[3][2] + m1.m_data[3][0] * m2.m_data[3][3];
	res.m_data[3][1] = m1.m_data[0][1] * m2.m_data[3][0] + m1.m_data[1][1] * m2.m_data[3][1] + m1.m_data[2][1] * m2.m_data[3][2] + m1.m_data[3][1] * m2.m_data[3][3];
	res.m_data[3][2] = m1.m_data[0][2] * m2.m_data[3][0] + m1.m_data[1][2] * m2.m_data[3][1] + m1.m_data[2][2] * m2.m_data[3][2] + m1.m_data[3][2] * m2.m_data[3][3];
	res.m_data[3][3] = m1.m_data[0][3] * m2.m_data[3][0] + m1.m_data[1][3] * m2.m_data[3][1] + m1.m_data[2][3] * m2.m_data[3][2] + m1.m_data[3][3] * m2.m_data[3][3];

	return res;
}

template<typename Type>
const mgl::AbstractVector<Type>& mgl::operator*(const AbstractMatrix<Type>& m, const AbstractVector<Type>& v) {
	return AbstractVector<Type>(m.m_data[0][0] * v[0] + m.m_data[0][1] * v[1] + m.m_data[0][2] * v[2] + m.m_data[0][3] * v[3],
								m.m_data[1][0] * v[0] + m.m_data[1][1] * v[1] + m.m_data[1][2] * v[2] + m.m_data[1][3] * v[3],
								m.m_data[2][0] * v[0] + m.m_data[2][1] * v[1] + m.m_data[2][2] * v[2] + m.m_data[2][3] * v[3],
								m.m_data[3][0] * v[0] + m.m_data[3][1] * v[1] + m.m_data[3][2] * v[2] + m.m_data[3][3] * v[3]);
}

template<typename Type>
const mgl::AbstractVector<Type>& mgl::operator*(const AbstractVector<Type>& v, const AbstractMatrix<Type>& m) {
	return AbstractVector<Type>(v[0] * m.m_data[0][0] + v[1] * m.m_data[1][0] + v[2] * m.m_data[2][0] + v[3] * m.m_data[3][0],
								v[0] * m.m_data[0][1] + v[1] * m.m_data[1][1] + v[2] * m.m_data[2][1] + v[3] * m.m_data[3][1],
								v[0] * m.m_data[0][2] + v[1] * m.m_data[1][2] + v[2] * m.m_data[2][2] + v[3] * m.m_data[3][2],
								v[0] * m.m_data[0][3] + v[1] * m.m_data[1][3] + v[2] * m.m_data[2][3] + v[3] * m.m_data[3][3]);
}

template<typename Type>
const mgl::AbstractMatrix<Type>& mgl::operator*(const Type & q, const AbstractMatrix<Type>& m) {
	return m * q;
}

template<typename Type>
const mgl::AbstractMatrix<Type>& mgl::operator*(const AbstractMatrix<Type>& m, const Type & q) {
	AbstractMatrix<Type> res(m1);
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 4; j++)
			res[i][j] *= q;
	return res;
}

template<typename Type>
const mgl::AbstractMatrix<Type>& mgl::operator/(const AbstractMatrix<Type>& m, const Type & q) {
	AbstractMatrix<Type> res(m1);
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 4; j++)
			res[i][j] /= q;
	return res;
}