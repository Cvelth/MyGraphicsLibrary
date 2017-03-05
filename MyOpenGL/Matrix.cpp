#include "Matrix.hpp"

mgl::Matrix::Matrix(const float & e00, const float & e01, const float & e02, const float & e03, 
					const float & e10, const float & e11, const float & e12, const float & e13, 
					const float & e20, const float & e21, const float & e22, const float & e23, 
					const float & e30, const float & e31, const float & e32, const float & e33) {
	m_data = MatrixHolder(e00, e01, e02, e03, e10, e11, e12, e13,
						  e20, e21, e22, e23, e30, e31, e32, e33);
}

mgl::Matrix::Matrix(const Matrix & m) {
	m_data = m.m_data;
}
mgl::Matrix::Matrix(const float & v) {
	m_data.fill(v);
}
mgl::Matrix::Matrix(InitialValue i) {
	switch (i) {
		case InitialValue::IdentityMatrix:
			m_data.identityFill();
			break;
		case InitialValue::UnitializedMatrix:
			break;
	}
}
mgl::Matrix::~Matrix() {
}

const mgl::Vector mgl::Matrix::column(const size_t & c) const {
	return Vector(m_data(0, c), m_data(1, c), m_data(2, c), m_data(3, c));
}
const mgl::Vector mgl::Matrix::row(const size_t & c) const {
	return Vector(m_data(0, c), m_data(1, c), m_data(2, c), m_data(3, c));
}

void mgl::Matrix::setColumn(const size_t & c, const Vector & v) {
	m_data(0,c) = v.x();
	m_data(1,c) = v.y();
	m_data(2,c) = v.z();
	m_data(3,c) = v.w();
}

void mgl::Matrix::setRow(const size_t & c, const Vector & v) {
	m_data(c,0) = v.x();
	m_data(c,1) = v.y();
	m_data(c,2) = v.z();
	m_data(c,3) = v.w();
}

void mgl::Matrix::fill(const float & v) {
	m_data.fill(v);
}
const float mgl::Matrix::determinant() const {
	return m_data(0,3) * m_data(1,2) * m_data(2,1) * m_data(3,0)  
		 - m_data(0,2) * m_data(1,3) * m_data(2,1) * m_data(3,0)
		 - m_data(0,3) * m_data(1,1) * m_data(2,2) * m_data(3,0)
		 + m_data(0,1) * m_data(1,3) * m_data(2,2) * m_data(3,0)
		 + m_data(0,2) * m_data(1,1) * m_data(2,3) * m_data(3,0)
		 - m_data(0,1) * m_data(1,2) * m_data(2,3) * m_data(3,0)
		 - m_data(0,3) * m_data(1,2) * m_data(2,0) * m_data(3,1)
		 + m_data(0,2) * m_data(1,3) * m_data(2,0) * m_data(3,1)
		 + m_data(0,3) * m_data(1,0) * m_data(2,2) * m_data(3,1)
		 - m_data(0,0) * m_data(1,3) * m_data(2,2) * m_data(3,1)
		 - m_data(0,2) * m_data(1,0) * m_data(2,3) * m_data(3,1)
		 + m_data(0,0) * m_data(1,2) * m_data(2,3) * m_data(3,1)
		 + m_data(0,3) * m_data(1,1) * m_data(2,0) * m_data(3,2)
		 - m_data(0,1) * m_data(1,3) * m_data(2,0) * m_data(3,2)
		 - m_data(0,3) * m_data(1,0) * m_data(2,1) * m_data(3,2)
		 + m_data(0,0) * m_data(1,3) * m_data(2,1) * m_data(3,2)
		 + m_data(0,1) * m_data(1,0) * m_data(2,3) * m_data(3,2)
		 - m_data(0,0) * m_data(1,1) * m_data(2,3) * m_data(3,2)
		 - m_data(0,2) * m_data(1,1) * m_data(2,0) * m_data(3,3)
		 + m_data(0,1) * m_data(1,2) * m_data(2,0) * m_data(3,3)
		 + m_data(0,2) * m_data(1,0) * m_data(2,1) * m_data(3,3)
		 - m_data(0,0) * m_data(1,2) * m_data(2,1) * m_data(3,3)
		 - m_data(0,1) * m_data(1,0) * m_data(2,2) * m_data(3,3)
		 + m_data(0,0) * m_data(1,1) * m_data(2,2) * m_data(3,3);
}

//To check!
void mgl::Matrix::translate(const Vector & v) {
	setRow(3, row(0) * v[0] + row(1) * v[1] + row(2) * v[2] + row(3) * v[3]);
}
void mgl::Matrix::translate(const float & x, const float & y, const float & z) {
	return translate(Vector(x, y, z));
}
void mgl::Matrix::rotate(const float & angle, const Vector & v) {
	Matrix m = rotationMatrix(angle, v);
	setRow(0, row(0) * m.m_data(0, 0) + row(1) * m.m_data(0, 1) + row(2) * m.m_data(0, 2));
	setRow(1, row(0) * m.m_data(1, 0) + row(1) * m.m_data(1, 1) + row(2) * m.m_data(1, 2));
	setRow(2, row(0) * m.m_data(2, 0) + row(1) * m.m_data(2, 1) + row(2) * m.m_data(2, 2));
}
void mgl::Matrix::rotate(const float & angle, const float & x, const float & y, const float & z) {
	return rotate(angle, Vector(x, y, z));
}
void mgl::Matrix::scale(const float & q) {
	return scale(q, q, q);
}
void mgl::Matrix::scale(const float & x, const float & y, const float & z) {
	setRow(0, row(0) * x);
	setRow(1, row(1) * y);
	setRow(2, row(2) * z);
}
void mgl::Matrix::scale(const Vector & v) {
	return scale(v.x(), v.y(), v.z());
}

const mgl::Matrix mgl::Matrix::orthographicMatrix(const float & left, const float & right, const float & top, const float & bottom, const float & near, const float & far) {
	return Matrix(2.f / (right - left), 0.f, 0.f, -(right + left) / (right - left),
				  0.f, 2.f / (top - bottom), 0.f, -(top + bottom) / (top - bottom),
				  0.f, 0.f, 2.f / (far - near), -(far + near) / (far - near),
				  0.f, 0.f, 0.f, 1.f);
}
const mgl::Matrix mgl::Matrix::orthographicUnprojectionMatrix(const float & left, const float & right, const float & top, const float & bottom, const float & near, const float &far) {
	return Matrix((right - left) / 2.f, 0.f, 0.f, (right + left) / 2.f,
				  0.f, (top - bottom) / 2.f, 0.f, (top + bottom) / 2.f,
				  0.f, 0.f, -(far - near) / 2.f, (far + near) / 2.f,
				  0.f, 0.f, 0.f, 1.f);
}
const mgl::Matrix mgl::Matrix::perspectiveMatrix(const float & left, const float & right, const float & top, const float & bottom, const float & near, const float & far) {
	return Matrix(2.f * near / (right - left), 0.f, (right + left) / (right - left), 0.f,
						 0.f, 2.f * near / (top - bottom), (top + bottom) / (top - bottom), 0.f,
						 0.f, 0.f, -(far + near) / (far - near), -2.f * far * near / (far - near),
						 0.f, 0.f, -1.f, 0.f);
}
const mgl::Matrix mgl::Matrix::translationMatrix(const Vector & v) {
	return translationMatrix(v.x(), v.y(), v.z());
}
const mgl::Matrix mgl::Matrix::translationMatrix(const float & x, const float & y, const float & z) {
	return Matrix(1.f, 0.f, 0.f, x,
				  0.f, 1.f, 0.f, y,
				  0.f, 0.f, 1.f, z,
				  0.f, 0.f, 0.f, 1.f);
}
const mgl::Matrix mgl::Matrix::rotationMatrix(const float & angle, const Vector & v) {
	float const c = cos(angle);
	float const s = sin(angle);
	Vector a = v.normalized();
	Vector t = a * (1.f - c);
	return mgl::Matrix(c + t.x() * a.x(), t.x() * a.y() + s * a.z(),
					   t.x() * a.z() - s * a.y(), 0,

					   t.y() * a.x() - s * a.z(), c + t.y() * a.y(),
					   t.y() * a.z() + s * a.x(), 0,

					   t.z() * a.x() + s * a.y(), t.z() * a.y() - s * a.x(),
					   c + t.z() * a.z(), 0,

					   0, 0, 0, 0);
}
const mgl::Matrix mgl::Matrix::rotationMatrix(const float & angle, const float & x, const float & y, const float & z) {
	return rotationMatrix(angle, Vector(x, y, z));
}
const mgl::Matrix mgl::Matrix::scalingMatrix(const float & q) {
	return scalingMatrix(q, q, q);
}
const mgl::Matrix mgl::Matrix::scalingMatrix(const float & x, const float & y, const float & z) {
	return Matrix(x, 0, 0, 0,
				  0, y, 0, 0,
				  0, 0, z, 0,
				  0, 0, 0, 1);
}
const mgl::Matrix mgl::Matrix::scalingMatrix(const Vector & v) {
	return scalingMatrix(v.x(), v.y(), v.z());
}

const mgl::Vector mgl::Matrix::operator[](size_t i) const {
	return mgl::Vector(m_data(i, 0), m_data(i, 1), m_data(i, 2), m_data(i, 3));
}
mgl::Vector mgl::Matrix::operator[](size_t i) {
	return mgl::Vector(m_data(i, 0), m_data(i, 1), m_data(i, 2), m_data(i, 3));
}
bool mgl::Matrix::operator==(const Matrix & matrix) {
	return !operator!=(matrix);
}
bool mgl::Matrix::operator!=(const Matrix & matrix) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (m_data(i, j) == matrix.m_data(i, j))
				return false;
	return true;
}

mgl::Matrix & mgl::Matrix::operator+=(const Matrix & matrix) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m_data(i, j) += matrix.m_data(i, j);
	return *this;
}
mgl::Matrix & mgl::Matrix::operator-=(const Matrix & matrix) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m_data(i, j) -= matrix.m_data(i, j);
	return *this;
}
mgl::Matrix & mgl::Matrix::operator*=(const Matrix & matrix) {
	m_data(0, 0) = m_data(0, 0) * matrix.m_data(0, 0) + m_data(1, 0) * matrix.m_data(0, 1) + m_data(2, 0) * matrix.m_data(0, 2) + m_data(3, 0) * matrix.m_data(0, 3);
	m_data(0, 1) = m_data(0, 1) * matrix.m_data(0, 0) + m_data(1, 1) * matrix.m_data(0, 1) + m_data(2, 1) * matrix.m_data(0, 2) + m_data(3, 1) * matrix.m_data(0, 3);
	m_data(0, 2) = m_data(0, 2) * matrix.m_data(0, 0) + m_data(1, 2) * matrix.m_data(0, 1) + m_data(2, 2) * matrix.m_data(0, 2) + m_data(3, 2) * matrix.m_data(0, 3);
	m_data(0, 3) = m_data(0, 3) * matrix.m_data(0, 0) + m_data(1, 3) * matrix.m_data(0, 1) + m_data(2, 3) * matrix.m_data(0, 2) + m_data(3, 3) * matrix.m_data(0, 3);

	m_data(1, 0) = m_data(0, 0) * matrix.m_data(1, 0) + m_data(1, 0) * matrix.m_data(1, 1) + m_data(2, 0) * matrix.m_data(1, 2) + m_data(3, 0) * matrix.m_data(1, 3);
	m_data(1, 1) = m_data(0, 1) * matrix.m_data(1, 0) + m_data(1, 1) * matrix.m_data(1, 1) + m_data(2, 1) * matrix.m_data(1, 2) + m_data(3, 1) * matrix.m_data(1, 3);
	m_data(1, 2) = m_data(0, 2) * matrix.m_data(1, 0) + m_data(1, 2) * matrix.m_data(1, 1) + m_data(2, 2) * matrix.m_data(1, 2) + m_data(3, 2) * matrix.m_data(1, 3);
	m_data(1, 3) = m_data(0, 3) * matrix.m_data(1, 0) + m_data(1, 3) * matrix.m_data(1, 1) + m_data(2, 3) * matrix.m_data(1, 2) + m_data(3, 3) * matrix.m_data(1, 3);

	m_data(2, 0) = m_data(0, 0) * matrix.m_data(2, 0) + m_data(1, 0) * matrix.m_data(2, 1) + m_data(2, 0) * matrix.m_data(2, 2) + m_data(3, 0) * matrix.m_data(2, 3);
	m_data(2, 1) = m_data(0, 1) * matrix.m_data(2, 0) + m_data(1, 1) * matrix.m_data(2, 1) + m_data(2, 1) * matrix.m_data(2, 2) + m_data(3, 1) * matrix.m_data(2, 3);
	m_data(2, 2) = m_data(0, 2) * matrix.m_data(2, 0) + m_data(1, 2) * matrix.m_data(2, 1) + m_data(2, 2) * matrix.m_data(2, 2) + m_data(3, 2) * matrix.m_data(2, 3);
	m_data(2, 3) = m_data(0, 3) * matrix.m_data(2, 0) + m_data(1, 3) * matrix.m_data(2, 1) + m_data(2, 3) * matrix.m_data(2, 2) + m_data(3, 3) * matrix.m_data(2, 3);

	m_data(3, 0) = m_data(0, 0) * matrix.m_data(3, 0) + m_data(1, 0) * matrix.m_data(3, 1) + m_data(2, 0) * matrix.m_data(3, 2) + m_data(3, 0) * matrix.m_data(3, 3);
	m_data(3, 1) = m_data(0, 1) * matrix.m_data(3, 0) + m_data(1, 1) * matrix.m_data(3, 1) + m_data(2, 1) * matrix.m_data(3, 2) + m_data(3, 1) * matrix.m_data(3, 3);
	m_data(3, 2) = m_data(0, 2) * matrix.m_data(3, 0) + m_data(1, 2) * matrix.m_data(3, 1) + m_data(2, 2) * matrix.m_data(3, 2) + m_data(3, 2) * matrix.m_data(3, 3);
	m_data(3, 3) = m_data(0, 3) * matrix.m_data(3, 0) + m_data(1, 3) * matrix.m_data(3, 1) + m_data(2, 3) * matrix.m_data(3, 2) + m_data(3, 3) * matrix.m_data(3, 3);

	return *this;
}
mgl::Matrix & mgl::Matrix::operator*=(const float & q) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m_data(i, j) *= q;
	return *this;
}
mgl::Matrix & mgl::Matrix::operator/=(const float & q) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m_data(i, j) /= q;
	return *this;
}

const mgl::Matrix mgl::operator+(const Matrix& m1, const Matrix& m2) {
	Matrix res(m1);
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 4; j++)
			res.m_data(i, j) += m2.m_data(i, j);
	return res;
}
const mgl::Matrix mgl::operator-(const Matrix& m1, const Matrix& m2) {
	Matrix res(m1);
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 4; j++)
			res.m_data(i, j) -= m2.m_data(i, j);
	return res;
}
const mgl::Matrix mgl::operator*(const Matrix& m1, const Matrix& m2) {
	return mgl::Matrix(
		m1.m_data(0, 0) * m2.m_data(0, 0) + m1.m_data(1, 0) * m2.m_data(0, 1) + m1.m_data(2, 0) * m2.m_data(0, 2) + m1.m_data(3, 0) * m2.m_data(0, 3),
		m1.m_data(0, 1) * m2.m_data(0, 0) + m1.m_data(1, 1) * m2.m_data(0, 1) + m1.m_data(2, 1) * m2.m_data(0, 2) + m1.m_data(3, 1) * m2.m_data(0, 3),
		m1.m_data(0, 2) * m2.m_data(0, 0) + m1.m_data(1, 2) * m2.m_data(0, 1) + m1.m_data(2, 2) * m2.m_data(0, 2) + m1.m_data(3, 2) * m2.m_data(0, 3),
		m1.m_data(0, 3) * m2.m_data(0, 0) + m1.m_data(1, 3) * m2.m_data(0, 1) + m1.m_data(2, 3) * m2.m_data(0, 2) + m1.m_data(3, 3) * m2.m_data(0, 3),

		m1.m_data(0, 0) * m2.m_data(1, 0) + m1.m_data(1, 0) * m2.m_data(1, 1) + m1.m_data(2, 0) * m2.m_data(1, 2) + m1.m_data(3, 0) * m2.m_data(1, 3),
		m1.m_data(0, 1) * m2.m_data(1, 0) + m1.m_data(1, 1) * m2.m_data(1, 1) + m1.m_data(2, 1) * m2.m_data(1, 2) + m1.m_data(3, 1) * m2.m_data(1, 3),
		m1.m_data(0, 2) * m2.m_data(1, 0) + m1.m_data(1, 2) * m2.m_data(1, 1) + m1.m_data(2, 2) * m2.m_data(1, 2) + m1.m_data(3, 2) * m2.m_data(1, 3),
		m1.m_data(0, 3) * m2.m_data(1, 0) + m1.m_data(1, 3) * m2.m_data(1, 1) + m1.m_data(2, 3) * m2.m_data(1, 2) + m1.m_data(3, 3) * m2.m_data(1, 3),

		m1.m_data(0, 0) * m2.m_data(2, 0) + m1.m_data(1, 0) * m2.m_data(2, 1) + m1.m_data(2, 0) * m2.m_data(2, 2) + m1.m_data(3, 0) * m2.m_data(2, 3),
		m1.m_data(0, 1) * m2.m_data(2, 0) + m1.m_data(1, 1) * m2.m_data(2, 1) + m1.m_data(2, 1) * m2.m_data(2, 2) + m1.m_data(3, 1) * m2.m_data(2, 3),
		m1.m_data(0, 2) * m2.m_data(2, 0) + m1.m_data(1, 2) * m2.m_data(2, 1) + m1.m_data(2, 2) * m2.m_data(2, 2) + m1.m_data(3, 2) * m2.m_data(2, 3),
		m1.m_data(0, 3) * m2.m_data(2, 0) + m1.m_data(1, 3) * m2.m_data(2, 1) + m1.m_data(2, 3) * m2.m_data(2, 2) + m1.m_data(3, 3) * m2.m_data(2, 3),
		
		m1.m_data(0, 0) * m2.m_data(3, 0) + m1.m_data(1, 0) * m2.m_data(3, 1) + m1.m_data(2, 0) * m2.m_data(3, 2) + m1.m_data(3, 0) * m2.m_data(3, 3),
		m1.m_data(0, 1) * m2.m_data(3, 0) + m1.m_data(1, 1) * m2.m_data(3, 1) + m1.m_data(2, 1) * m2.m_data(3, 2) + m1.m_data(3, 1) * m2.m_data(3, 3),
		m1.m_data(0, 2) * m2.m_data(3, 0) + m1.m_data(1, 2) * m2.m_data(3, 1) + m1.m_data(2, 2) * m2.m_data(3, 2) + m1.m_data(3, 2) * m2.m_data(3, 3),
		m1.m_data(0, 3) * m2.m_data(3, 0) + m1.m_data(1, 3) * m2.m_data(3, 1) + m1.m_data(2, 3) * m2.m_data(3, 2) + m1.m_data(3, 3) * m2.m_data(3, 3));
}
const mgl::Vector mgl::operator*(const Matrix& m, const Vector& v) {
	return Vector(m.m_data(0, 0) * v[0] + m.m_data(0, 1) * v[1] + m.m_data(0, 2) * v[2] + m.m_data(0, 3) * v[3],
				  m.m_data(1, 0) * v[0] + m.m_data(1, 1) * v[1] + m.m_data(1, 2) * v[2] + m.m_data(1, 3) * v[3],
				  m.m_data(2, 0) * v[0] + m.m_data(2, 1) * v[1] + m.m_data(2, 2) * v[2] + m.m_data(2, 3) * v[3],
				  m.m_data(3, 0) * v[0] + m.m_data(3, 1) * v[1] + m.m_data(3, 2) * v[2] + m.m_data(3, 3) * v[3]);
}
const mgl::Vector mgl::operator*(const Vector& v, const Matrix& m) {
	return Vector(v[0] * m.m_data(0, 0) + v[1] * m.m_data(1, 0) + v[2] * m.m_data(2, 0) + v[3] * m.m_data(3, 0),
				  v[0] * m.m_data(0, 1) + v[1] * m.m_data(1, 1) + v[2] * m.m_data(2, 1) + v[3] * m.m_data(3, 1),
				  v[0] * m.m_data(0, 2) + v[1] * m.m_data(1, 2) + v[2] * m.m_data(2, 2) + v[3] * m.m_data(3, 2),
				  v[0] * m.m_data(0, 3) + v[1] * m.m_data(1, 3) + v[2] * m.m_data(2, 3) + v[3] * m.m_data(3, 3));
}
const mgl::Matrix mgl::operator*(const float& q, const Matrix& m) { 
	return m * q; 
}
const mgl::Matrix mgl::operator*(const Matrix& m, const float& q) {
	Matrix res(m);
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 4; j++)
			res.m_data(i, j) *= q;
	return res;
}
const mgl::Matrix mgl::operator/(const Matrix& m, const float& q) {
	Matrix res(m);
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 4; j++)
			res.m_data(i, j) /= q;
	return res;
}

mgl::MatrixHolder::MatrixHolder(const float & e00, const float & e01, const float & e02, const float & e03, const float & e10, const float & e11, const float & e12, const float & e13, const float & e20, const float & e21, const float & e22, const float & e23, const float & e30, const float & e31, const float & e32, const float & e33) {
	m[0 + 0] = e00;
	m[0 + 1] = e01;
	m[0 + 2] = e02;
	m[0 + 3] = e03;

	m[4 + 0] = e10;
	m[4 + 1] = e11;
	m[4 + 2] = e12;
	m[4 + 3] = e13;

	m[8 + 0] = e20;
	m[8 + 1] = e21;
	m[8 + 2] = e22;
	m[8 + 3] = e23;

	m[12 + 0] = e30;
	m[12 + 1] = e31;
	m[12 + 2] = e32;
	m[12 + 3] = e33;
}

void mgl::MatrixHolder::fill(const float & v) {
	for (size_t i = 0; i < 16; i++)
		m[i] = v;
}

void mgl::MatrixHolder::identityFill() {
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 4; j++)
			m[i * 4 + j] = i == j ? 1.f : 0.f;
}

mgl::MatrixHolder & mgl::MatrixHolder::operator=(const MatrixHolder & h) {
	for (size_t i = 0; i < 16; i++)
		m[i] = h.m[i];
	return *this;
}
