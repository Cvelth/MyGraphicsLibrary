#include "Matrix.hpp"
#include "vector.hpp"
#include "dependencies/include/glm/glm.hpp"
#include "dependencies/include/glm/gtc/matrix_transform.hpp"

namespace mgl {
	namespace math {
		class MatrixInnerStructure {
		private:
			glm::mat4 m_data;
		protected:
			MatrixInnerStructure(glm::mat4* data) {
				m_data = *data;
			}
			MatrixInnerStructure(const glm::mat4& data) {
				m_data = data;
			}
			MatrixInnerStructure(glm::mat4&& data) {
				m_data = data;
			}
		public:
			explicit MatrixInnerStructure(const float e00, const float e01, const float e02, const float e03,
										  const float e10, const float e11, const float e12, const float e13,
										  const float e20, const float e21, const float e22, const float e23,
										  const float e30, const float e31, const float e32, const float e33) {
				m_data[0][0] = e00;		m_data[1][0] = e10;
				m_data[0][1] = e01;		m_data[1][1] = e11;
				m_data[0][2] = e02;		m_data[1][2] = e12;
				m_data[0][3] = e03;		m_data[1][3] = e13;

				m_data[2][0] = e20;		m_data[3][0] = e30;
				m_data[2][1] = e21;		m_data[3][1] = e31;
				m_data[2][2] = e22;		m_data[3][2] = e32;
				m_data[2][3] = e23;		m_data[3][3] = e33;
			}
			explicit MatrixInnerStructure(const float v) {
				fill(v);
			}
			explicit MatrixInnerStructure(const float* v) {
				for (size_t i = 0; i < 4; i++)
					for (size_t j = 0; j < 4; j++)
						m_data[(unsigned) i][(unsigned) j] = v[i * 4 + j];
			}
			explicit MatrixInnerStructure(const float** v) {
				for (size_t i = 0; i < 4; i++)
					for (size_t j = 0; j < 4; j++)
						m_data[(unsigned) i][(unsigned) j] = v[i][j];
			}
			explicit MatrixInnerStructure() {
			}

			void fill(const float v) {
				for (size_t i = 0; i < 4; i++)
					for (size_t j = 0; j < 4; j++)
						m_data[(unsigned) i][(unsigned) j] = v;
			}
			void identityFill(const float v = 1.f) {
				for (size_t i = 0; i < 4; i++)
					for (size_t j = 0; j < 4; j++)
						m_data[(unsigned) i][(unsigned) j] = (i == j) ? v : 0.f;
			}

			const float& get(const size_t i, const size_t j) const {
				return m_data[(unsigned) i][(unsigned) j];
			}
			float& get(const size_t i, const size_t j) {
				return m_data[(unsigned) i][(unsigned) j];
			}

		protected:
			float* dataIxJ(size_t i, size_t j, float* data = nullptr) const {
				if (i > 4 || j > 4)
					throw Exceptions::MatrixException("Incorrect index was passed");
				if (!data) data = new float[i * j];
				for (size_t a = 0; a < i; a++)
					for (size_t b = 0; b < j; b++)
						data[a * 4 + b] = m_data[(unsigned) a][(unsigned) b];
				return data;
			}
			float** dataIxJ(size_t i, size_t j, float** data) const {
				if (i > 4 || j > 4)
					throw Exceptions::MatrixException("Incorrect index was passed");
				for (size_t a = 0; a < i; a++)
					for (size_t b = 0; b < j; b++)
						data[a][b] = m_data[(unsigned) a][(unsigned) b];
				return data;
			}

		public:
			float* data4x4(float* data = nullptr) const {
				return dataIxJ(4, 4, data);
			}
			float** data4x4(float** data) const {
				return dataIxJ(4, 4, data);
			}
			float* data3x3(float* data = nullptr) const {
				return dataIxJ(3, 3, data);
			}
			float** data3x3(float** data) const {
				return dataIxJ(3, 3, data);
			}
			float* data2x2(float* data = nullptr) const {
				return dataIxJ(2, 2, data);
			}
			float** data2x2(float** data) const {
				return dataIxJ(2, 2, data);
			}
			const float det() const {
				return glm::determinant(m_data);
			}
			
			void translate(const float x = 0.f, const float y = 0.f, const float z = 0.f) {
				m_data = glm::translate(m_data, glm::vec3(x, y, z));
			}
			void rotate(const float angle, const float x = 0.f, const float y = 0.f, const float z = 1.f) {
				m_data = glm::rotate(m_data, angle, glm::vec3(x, y, z));
			}
			void scale(const float x, const float y, const float z = 1.f) {
				m_data = glm::scale(m_data, glm::vec3(x, y, z));
			}

			static const MatrixInnerStructure orthographicMatrix(const float left, const float right,
																 const float bottom, const float top,
																 const float near, const float far) {
				return glm::ortho(left, right, bottom, top, near, far);
			}
			static const MatrixInnerStructure perspectiveMatrix(const float left, const float right,
																const float bottom, const float top,
																const float near, const float far) {
				return glm::frustum(left, right, bottom, top, near, far);
			}
			static const MatrixInnerStructure translationMatrix(const float x = 0.f, const float y = 0.f, const float z = 0.f) {
				glm::mat4 ret;
				return glm::translate(ret, glm::vec3(x, y, z));
			}
			static const MatrixInnerStructure rotationMatrix(const float angle, const float x = 0.f, const float y = 0.f, const float z = 1.f) {
				glm::mat4 ret;
				return glm::rotate(ret, angle, glm::vec3(x, y, z));
			}
			static const MatrixInnerStructure scalingMatrix(const float x, const float y, const float z = 1.f) {
				glm::mat4 ret;
				return glm::scale(ret, glm::vec3(x, y, z));
			}

			bool isEq(const MatrixInnerStructure& matrix) {
				return m_data == matrix.m_data;
			}
			bool isEq(MatrixInnerStructure* matrix) {
				return m_data == matrix->m_data;
			}
			bool isNEq(const MatrixInnerStructure& matrix) {
				return m_data != matrix.m_data;
			}
			bool isNEq(MatrixInnerStructure* matrix) {
				return m_data != matrix->m_data;
			}

			MatrixInnerStructure& addEq(const MatrixInnerStructure& matrix) {
				m_data += matrix.m_data;
				return *this;
			}
			MatrixInnerStructure& addEq(MatrixInnerStructure* matrix) {
				m_data += matrix->m_data;
				return *this;
			}
			MatrixInnerStructure& subEq(const MatrixInnerStructure& matrix) {
				m_data -= matrix.m_data;
				return *this;
			}
			MatrixInnerStructure& subEq(MatrixInnerStructure* matrix) {
				m_data -= matrix->m_data;
				return *this;
			}
			MatrixInnerStructure& dotEq(const MatrixInnerStructure& matrix) {
				m_data *= matrix.m_data;
				return *this;
			}
			MatrixInnerStructure& dotEq(MatrixInnerStructure* matrix) {
				m_data *= matrix->m_data;
				return *this;
			}
			MatrixInnerStructure& mulEq(const float q) {
				m_data *= q;
				return *this;
			}
			MatrixInnerStructure& divEq(const float q) {
				m_data /= q;
				return *this;
			}

			static const MatrixInnerStructure add(const MatrixInnerStructure& m1, const MatrixInnerStructure& m2) {
				return MatrixInnerStructure(m1.m_data + m2.m_data);
			}
			static const MatrixInnerStructure add(MatrixInnerStructure* m1, MatrixInnerStructure* m2) {
				return MatrixInnerStructure(m1->m_data + m2->m_data);
			}
			static const MatrixInnerStructure sub(const MatrixInnerStructure& m1, const MatrixInnerStructure& m2) {
				return MatrixInnerStructure(m1.m_data - m2.m_data);
			}
			static const MatrixInnerStructure sub(MatrixInnerStructure* m1, MatrixInnerStructure* m2) {
				return MatrixInnerStructure(m1->m_data - m2->m_data);
			}
			static const MatrixInnerStructure dot(const MatrixInnerStructure& m1, const MatrixInnerStructure& m2) {
				return MatrixInnerStructure(m1.m_data * m2.m_data);
			}
			static const MatrixInnerStructure dot(MatrixInnerStructure* m1, MatrixInnerStructure* m2) {
				return MatrixInnerStructure(m1->m_data * m2->m_data);
			}
			static const vectorH dot(const MatrixInnerStructure& m1, const float x, const float y, const float z, const float w) {
				auto temp = m1.m_data * glm::vec4(x, y, z, w);
				return vectorH(temp.x, temp.y, temp.z, temp.w);
			}
			static const vectorH dot(MatrixInnerStructure* m1, const float x, const float y, const float z, const float w) {
				auto temp = m1->m_data * glm::vec4(x, y, z, w);
				return vectorH(temp.x, temp.y, temp.z, temp.w);
			}
			static const vectorH dot(const float x, const float y, const float z, const float w, const MatrixInnerStructure& m1) {
				auto temp = glm::vec4(x, y, z, w) * m1.m_data;
				return vectorH(temp.x, temp.y, temp.z, temp.w);
			}
			static const vectorH dot(const float x, const float y, const float z, const float w, MatrixInnerStructure* m1) {
				auto temp = glm::vec4(x, y, z, w) * m1->m_data;
				return vectorH(temp.x, temp.y, temp.z, temp.w);
			}
			static const MatrixInnerStructure mul(const MatrixInnerStructure& m1, const float q) {
				return MatrixInnerStructure(m1.m_data * q);
			}
			static const MatrixInnerStructure mul(MatrixInnerStructure* m1, const float q) {
				return MatrixInnerStructure(m1->m_data * q);
			}
			static const MatrixInnerStructure div(const MatrixInnerStructure& m1, const float q) {
				return MatrixInnerStructure(m1.m_data / q);
			}
			static const MatrixInnerStructure div(MatrixInnerStructure* m1, const float q) {
				return MatrixInnerStructure(m1->m_data / q);
			}
		};
	}
}

mgl::math::Matrix::Matrix(MatrixInnerStructure * data) {
	if (data)
		m_data = data;
	else
		throw mgl::Exceptions::MatrixException("Incorrect Data Was Inserted.");
}
mgl::math::Matrix::Matrix(const MatrixInnerStructure & data) {
	m_data = new MatrixInnerStructure();
	*m_data = data;
}
mgl::math::Matrix::Matrix(MatrixInnerStructure && data) {
	m_data = new MatrixInnerStructure();
	*m_data = data;
}
mgl::math::Matrix::Matrix(const float e00, const float e01, const float e02, const float e03,
						  const float e10, const float e11, const float e12, const float e13, 
						  const float e20, const float e21, const float e22, const float e23, 
						  const float e30, const float e31, const float e32, const float e33) {
	m_data = new MatrixInnerStructure(e00, e01, e02, e03,
									  e10, e11, e12, e13,
									  e20, e21, e22, e23,
									  e30, e31, e32, e33);
}
mgl::math::Matrix::Matrix(const float v) {
	m_data = new MatrixInnerStructure(v);
}
mgl::math::Matrix::Matrix(const float * v) {
	m_data = new MatrixInnerStructure(v);
}
mgl::math::Matrix::Matrix(const float ** v) {
	m_data = new MatrixInnerStructure(v);
}
mgl::math::Matrix::Matrix(InitialMatrixValue i) {
	m_data = new MatrixInnerStructure();
	switch (i) {
		case InitialMatrixValue::IdentityMatrix:
			m_data->identityFill();
			break;
		case InitialMatrixValue::UnitializedMatrix:
			break;
	}
}
mgl::math::Matrix::~Matrix() {
	delete m_data;
}

const mgl::math::vectorH mgl::math::Matrix::column(const size_t c) const {
	return vectorH(m_data->get(0, c), m_data->get(1, c), m_data->get(2, c), m_data->get(3, c));
}

const mgl::math::vectorH mgl::math::Matrix::row(const size_t c) const {
	return vectorH(m_data->get(c, 0), m_data->get(c, 1), m_data->get(c, 2), m_data->get(c, 3));
}

void mgl::math::Matrix::setColumn(const size_t c, const vectorH & v) {
	m_data->get(0, c) = v.x();
	m_data->get(1, c) = v.y();
	m_data->get(2, c) = v.z();
	m_data->get(3, c) = v.w();
}

void mgl::math::Matrix::setRow(const size_t c, const vectorH & v) {
	m_data->get(c, 0) = v.x();
	m_data->get(c, 1) = v.y();
	m_data->get(c, 2) = v.z();
	m_data->get(c, 3) = v.w();
}

float* mgl::math::Matrix::data(float* data) const {
	return m_data->data4x4(data);
}

float** mgl::math::Matrix::data(float** data) const {
	return m_data->data4x4(data);
}

float * mgl::math::Matrix::data4x4(float * data) const {
	return m_data->data4x4(data);
}

float ** mgl::math::Matrix::data4x4(float ** data) const {
	return m_data->data4x4(data);
}

float * mgl::math::Matrix::data3x3(float * data) const {
	return m_data->data3x3(data);
}

float ** mgl::math::Matrix::data3x3(float ** data) const {
	return m_data->data3x3(data);
}

float * mgl::math::Matrix::data2x2(float * data) const {
	return m_data->data2x2(data);
}

float ** mgl::math::Matrix::data2x2(float ** data) const {
	return m_data->data2x2(data);
}

void mgl::math::Matrix::fill(const float v) {
	m_data->fill(v);
}
const float mgl::math::Matrix::determinant() const {
	return m_data->det();
}

mgl::math::Matrix& mgl::math::Matrix::translate(const vector & v) {
	translate(v[0], v[1], v[2]);
	return *this;
}
mgl::math::Matrix& mgl::math::Matrix::translate(const float x, const float y, const float z) {
	m_data->translate(x, y, z);
	return *this;
}
mgl::math::Matrix& mgl::math::Matrix::rotate(const float angle, const vector & v) {
	rotate(angle, v[0], v[1], v[2]);
	return *this;
}
mgl::math::Matrix& mgl::math::Matrix::rotate(const float angle, const float x, const float y, const float z) {
	m_data->rotate(angle, x, y, z);
	return *this;
}
mgl::math::Matrix& mgl::math::Matrix::scale(const float q) {
	scale(q, q, q);
	return *this;
}
mgl::math::Matrix& mgl::math::Matrix::scale(const float x, const float y, const float z) {
	m_data->scale(x, y, z);
	return *this;
}
mgl::math::Matrix& mgl::math::Matrix::scale(const vector & v) {
	scale(v[0], v[1], v[2]);
	return *this;
}

const mgl::math::Matrix mgl::math::Matrix::orthographicMatrix(const float left, const float right, const float bottom, const float top, const float near, const float far) {
	return MatrixInnerStructure::orthographicMatrix(left, right, bottom, top, near, far);
}

const mgl::math::Matrix mgl::math::Matrix::perspectiveMatrix(const float left, const float right, const float bottom, const float top, const float near, const float far) {
	return MatrixInnerStructure::perspectiveMatrix(left, right, bottom, top, near, far);
}

const mgl::math::Matrix mgl::math::Matrix::translationMatrix(const vector & v) {
	return translationMatrix(v[0], v[1], v[2]);
}
const mgl::math::Matrix mgl::math::Matrix::translationMatrix(const float x, const float y, const float z) {
	return MatrixInnerStructure::translationMatrix(x, y, z);
}
const mgl::math::Matrix mgl::math::Matrix::rotationMatrix(const float angle, const vector & v) {
	return rotationMatrix(angle, v[0], v[1], v[2]);
}
const mgl::math::Matrix mgl::math::Matrix::rotationMatrix(const float angle, const float x, const float y, const float z) {
	return MatrixInnerStructure::rotationMatrix(angle, x, y, z);
}
const mgl::math::Matrix mgl::math::Matrix::scalingMatrix(const float q) {
	return scalingMatrix(q, q, q);
}
const mgl::math::Matrix mgl::math::Matrix::scalingMatrix(const float x, const float y, const float z) {
	return MatrixInnerStructure::scalingMatrix(x, y, z);
}
const mgl::math::Matrix mgl::math::Matrix::scalingMatrix(const vector & v) {
	return scalingMatrix(v[0], v[1], v[2]);
}

const mgl::math::vectorH mgl::math::Matrix::operator[](size_t i) const {
	return row(i);
}
mgl::math::vectorH mgl::math::Matrix::operator[](size_t i) {
	return column(i);
}
bool mgl::math::Matrix::operator==(const Matrix & matrix) {
	return m_data->isEq(matrix.m_data);
}
bool mgl::math::Matrix::operator!=(const Matrix & matrix) {
	return m_data->isNEq(matrix.m_data);
}

mgl::math::Matrix& mgl::math::Matrix::operator+=(const Matrix& matrix) {
	m_data->addEq(matrix.m_data);
	return *this;
}
mgl::math::Matrix& mgl::math::Matrix::operator-=(const Matrix& matrix) {
	m_data->subEq(matrix.m_data);
	return *this;
}
mgl::math::Matrix& mgl::math::Matrix::operator*=(const Matrix& matrix) {
	m_data->dotEq(matrix.m_data);
	return *this;
}
mgl::math::Matrix& mgl::math::Matrix::operator*=(const float q) {
	m_data->mulEq(q);
	return *this;
}
mgl::math::Matrix& mgl::math::Matrix::operator/=(const float q) {
	m_data->divEq(q);
	return *this;
}

float mgl::math::Matrix::operator()(size_t row, size_t col) {
	return m_data->get(row, col);
}
const float mgl::math::Matrix::operator()(size_t row, size_t col) const {
	return m_data->get(row, col);
}

const mgl::math::Matrix mgl::math::operator+(const Matrix & m1, const Matrix & m2) {
	return Matrix(MatrixInnerStructure::add(m1.m_data, m2.m_data));
}
const mgl::math::Matrix mgl::math::operator-(const Matrix & m1, const Matrix & m2) {
	return Matrix(MatrixInnerStructure::sub(m1.m_data, m2.m_data));
}
const mgl::math::Matrix mgl::math::operator*(const Matrix & m1, const Matrix & m2) {
	return Matrix(MatrixInnerStructure::dot(m1.m_data, m2.m_data));
}
const mgl::math::vectorH mgl::math::operator*(const Matrix & m, const vectorH & v) {
	return MatrixInnerStructure::dot(m.m_data, v.x(), v.y(), v.z(), v.w());
}
const mgl::math::vectorH mgl::math::operator*(const vectorH & v, const Matrix & m) {
	return MatrixInnerStructure::dot(v.x(), v.y(), v.z(), v.w(), m.m_data);
}
const mgl::math::Matrix mgl::math::operator*(const Matrix & m, const float q) {
	return Matrix(MatrixInnerStructure::mul(m.m_data, q));
}
const mgl::math::Matrix mgl::math::operator*(const float q, const Matrix & m) {
	return Matrix(MatrixInnerStructure::mul(m.m_data, q));
}
const mgl::math::Matrix mgl::math::operator/(const Matrix & m, const float q) {
	return Matrix(MatrixInnerStructure::div(m.m_data, q));
}