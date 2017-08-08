#include "Vector.hpp"
#include "include\glm\glm.hpp"

namespace mgl {
	namespace math {
		class VectorInnerStructure {
		private:
			glm::vec4 m_data;
		protected:
			VectorInnerStructure(glm::vec4& data) {
				m_data = data;
			}
			VectorInnerStructure(const glm::vec4& data) {
				m_data = data;
			}
			VectorInnerStructure(glm::vec4&& data) {
				m_data = data;
			}
		public:
			explicit VectorInnerStructure(float x = 0.f, float y = 0.f, float z = 0.f, float w = 0.f) {
				m_data.x = x;
				m_data.y = y;
				m_data.z = z;
				m_data.w = w;
			}
			VectorInnerStructure(VectorInnerStructure const& other) {
				m_data = other.m_data;
			}
			VectorInnerStructure(VectorInnerStructure&& other) {
				m_data = other.m_data;
			}

			void x(const float a) {
				m_data.x = a;
			}
			void y(const float a) {
				m_data.y = a;
			}
			void z(const float a) {
				m_data.z = a;
			}
			void w(const float a) {
				m_data.w = a;
			}
			void set(const float x = 0, const float y = 0, const float z = 0, const float w = 0) {
				m_data.x = x;
				m_data.y = y;
				m_data.z = z;
				m_data.w = w;
			}
			void set(const float *a) {
				m_data.x = a[0];
				m_data.y = a[1];
				m_data.z = a[2];
				m_data.w = a[3];
			}
			const float x() const {
				return m_data.x;
			}
			const float y() const {
				return m_data.y;
			}
			const float z() const {
				return m_data.z;
			}
			const float w() const {
				return m_data.q;
			}
			const float* const get(float* a) const {
				a[0] = m_data.x;
				a[1] = m_data.y;
				a[2] = m_data.z;
				a[3] = m_data.w;
				return a;
			}
			float* const get(float* a) {
				a[0] = m_data.x;
				a[1] = m_data.y;
				a[2] = m_data.z;
				a[3] = m_data.w;
				return a;
			}

			const float& get(const size_t index) const {
				return m_data[(unsigned) index];
			}
			float& get(const size_t index) {
				return m_data[(unsigned) index];
			}

			bool isNull() const {
				return m_data == glm::vec4(0.f, 0.f, 0.f, 0.f);
			}
			float length() const {
				return float(m_data.length());
			}
			void normalize() {
				m_data = glm::normalize(m_data);
			}
			const VectorInnerStructure normalized() const {
				return glm::normalize(m_data);
			}

			VectorInnerStructure& addEq(const VectorInnerStructure& vector) {
				m_data += vector.m_data;
				return *this;
			}
			VectorInnerStructure& addEq(VectorInnerStructure&& vector) {
				m_data += vector.m_data;
				return *this;
			}
			VectorInnerStructure& addEq(VectorInnerStructure* vector) {
				m_data += vector->m_data;
				return *this;
			}
			VectorInnerStructure& subEq(const VectorInnerStructure& vector) {
				m_data -= vector.m_data;
				return *this;
			}
			VectorInnerStructure& subEq(VectorInnerStructure&& vector) {
				m_data -= vector.m_data;
				return *this;
			}
			VectorInnerStructure& subEq(VectorInnerStructure* vector) {
				m_data -= vector->m_data;
				return *this;
			}
			VectorInnerStructure& mulEq(const VectorInnerStructure& vector) {
				m_data = glm::vec4(m_data.x * vector.m_data.x,
								   m_data.y * vector.m_data.y,
								   m_data.z * vector.m_data.z,
								   m_data.w * vector.m_data.w);
				return *this;
			}
			VectorInnerStructure& mulEq(VectorInnerStructure&& vector) {
				m_data = glm::vec4(m_data.x * vector.m_data.x,
								   m_data.y * vector.m_data.y,
								   m_data.z * vector.m_data.z,
								   m_data.w * vector.m_data.w);
				return *this;
			}
			VectorInnerStructure& mulEq(VectorInnerStructure* vector) {
				m_data = glm::vec4(m_data.x * vector->m_data.x,
								   m_data.y * vector->m_data.y,
								   m_data.z * vector->m_data.z,
								   m_data.w * vector->m_data.w);
				return *this;
			}
			VectorInnerStructure& divEq(const VectorInnerStructure& vector) {
				m_data = glm::vec4(m_data.x / vector.m_data.x,
								   m_data.y / vector.m_data.y,
								   m_data.z / vector.m_data.z,
								   m_data.w / vector.m_data.w);
				return *this;
			}
			VectorInnerStructure& divEq(VectorInnerStructure&& vector) {
				m_data = glm::vec4(m_data.x / vector.m_data.x,
								   m_data.y / vector.m_data.y,
								   m_data.z / vector.m_data.z,
								   m_data.w / vector.m_data.w);
				return *this;
			}
			VectorInnerStructure& divEq(VectorInnerStructure* vector) {
				m_data = glm::vec4(m_data.x / vector->m_data.x,
								   m_data.y / vector->m_data.y,
								   m_data.z / vector->m_data.z,
								   m_data.w / vector->m_data.w);
				return *this;
			}
			VectorInnerStructure& mulEq(const float q) {
				m_data *= q;
				return *this;
			}
			VectorInnerStructure& divEq(const float q) {
				m_data /= q;
				return *this;
			}
			bool isEq(const VectorInnerStructure& vector) const {
				return m_data == vector.m_data;
			}
			bool isEq(VectorInnerStructure&& vector) const {
				return m_data == vector.m_data;
			}
			bool isEq(VectorInnerStructure* vector) const {
				return m_data == vector->m_data;
			}
			bool isNEq(const VectorInnerStructure& vector) const {
				return !isEq(vector);
			}
			bool isNEq(VectorInnerStructure&& vector) const {
				return !isEq(vector);
			}
			bool isNEq(VectorInnerStructure* vector) const {
				return !isEq(vector);
			}

			static VectorInnerStructure add(const VectorInnerStructure& a1, const VectorInnerStructure& a2) {
				return VectorInnerStructure(a1.m_data + a2.m_data);
			}
			static VectorInnerStructure add(VectorInnerStructure&& a1, VectorInnerStructure&& a2) {
				return VectorInnerStructure(a1.m_data + a2.m_data);
			}
			static VectorInnerStructure add(VectorInnerStructure* a1, VectorInnerStructure* a2) {
				return VectorInnerStructure(a1->m_data + a2->m_data);
			}
			static VectorInnerStructure sub(const VectorInnerStructure& a1, const VectorInnerStructure& a2) {
				return VectorInnerStructure(a1.m_data - a2.m_data);
			}
			static VectorInnerStructure sub(VectorInnerStructure&& a1, VectorInnerStructure&& a2) {
				return VectorInnerStructure(a1.m_data - a2.m_data);
			}
			static VectorInnerStructure sub(VectorInnerStructure* a1, VectorInnerStructure* a2) {
				return VectorInnerStructure(a1->m_data - a2->m_data);
			}
			static const float dot(const VectorInnerStructure& a1, const VectorInnerStructure& a2) {
				return glm::dot(a1.m_data, a2.m_data);
			}
			static const float dot(VectorInnerStructure&& a1, VectorInnerStructure&& a2) {
				return glm::dot(a1.m_data, a2.m_data);
			}
			static const float dot(VectorInnerStructure* a1, VectorInnerStructure* a2) {
				return glm::dot(a1->m_data, a2->m_data);
			}
			static VectorInnerStructure mul(const VectorInnerStructure& a1, const float q) {
				return VectorInnerStructure(a1.m_data * q);
			}
			static VectorInnerStructure mul(VectorInnerStructure&& a1, const float q) {
				return VectorInnerStructure(a1.m_data * q);
			}
			static VectorInnerStructure mul(VectorInnerStructure* a1, const float q) {
				return VectorInnerStructure(a1->m_data * q);
			}
			static VectorInnerStructure div(const VectorInnerStructure& a1, const float q) {
				return VectorInnerStructure(a1.m_data / q);
			}
			static VectorInnerStructure div(VectorInnerStructure&& a1, const float q) {
				return VectorInnerStructure(a1.m_data / q);
			}
			static VectorInnerStructure div(VectorInnerStructure* a1, const float q) {
				return VectorInnerStructure(a1->m_data / q);
			}
			static VectorInnerStructure cross(const VectorInnerStructure& a1, const VectorInnerStructure& a2) {
				return VectorInnerStructure(glm::vec4(glm::cross(glm::vec3(a1.m_data), glm::vec3(a2.m_data)), 0.f));
			}
			static VectorInnerStructure cross(VectorInnerStructure&& a1, VectorInnerStructure&& a2) {
				return VectorInnerStructure(glm::vec4(glm::cross(glm::vec3(a1.m_data), glm::vec3(a2.m_data)), 0.f));
			}
			static VectorInnerStructure cross(VectorInnerStructure* a1, VectorInnerStructure* a2) {
				return VectorInnerStructure(glm::vec4(glm::cross(glm::vec3(a1->m_data), glm::vec3(a2->m_data)), 0.f));
			}
		};
	}
}

mgl::math::Vector::Vector(VectorInnerStructure * data) {
	if (data)
		m_data = data;
	else
		throw Exceptions::VectorException("Incorrect Data Was Inserted.");
}
mgl::math::Vector::Vector(const VectorInnerStructure& data) {
	m_data = new VectorInnerStructure(data);
}
mgl::math::Vector::Vector(VectorInnerStructure && data) {
	m_data = new VectorInnerStructure(data);
}
mgl::math::Vector::Vector(const float x, const float y, const float z, const float w) {
	m_data = new VectorInnerStructure(x, y, z, w);
}
mgl::math::Vector::Vector(const float * const data) : Vector(data[0], data[1], data[2], data[3]) {
}
mgl::math::Vector::Vector(Vector const& other) {
	m_data = new VectorInnerStructure(*other.m_data);
}
mgl::math::Vector::Vector(Vector&& other) {
	m_data = new VectorInnerStructure(*other.m_data);
}
mgl::math::Vector const& mgl::math::Vector::operator=(Vector const& other) {
	m_data = new VectorInnerStructure(*other.m_data);
}
mgl::math::Vector::~Vector() {
	if (m_data) delete m_data;
}

void mgl::math::Vector::x(const float a) {
	m_data->x(a);
}							  
void mgl::math::Vector::y(const float a) {
	m_data->y(a);
}
void mgl::math::Vector::z(const float a) {
	m_data->z(a);
}
void mgl::math::Vector::w(const float a) {
	m_data->w(a);
}
void mgl::math::Vector::set(const float x, const float y, const float z, const float w) {
	m_data->set(x, y, z, w);
}
void mgl::math::Vector::set(const float *a) {
	m_data->set(a);
}
const float mgl::math::Vector::x() const {
	return m_data->x();
}
const float mgl::math::Vector::y() const {
	return m_data->y();
}
const float mgl::math::Vector::z() const {
	return m_data->z();
}
const float mgl::math::Vector::w() const {
	return m_data->w();
}
const float* const mgl::math::Vector::get(float* a) const {
	if (a == nullptr) a = new float[4];
	return m_data->get(a);
}

float * const mgl::math::Vector::get(float * a) {
	if (a == nullptr) a = new float[4];
	return m_data->get(a);
}

bool mgl::math::Vector::isNull() const {
	return m_data->isNull();
}
float mgl::math::Vector::length() const {
	return m_data->length();
}
void mgl::math::Vector::normalize() {
	m_data->normalize();
}
const mgl::math::Vector mgl::math::Vector::normalized() const {
	return m_data->normalized();
}

const float & mgl::math::Vector::operator[](const size_t i) const {
	return m_data->get(i);
}
float & mgl::math::Vector::operator[](const size_t i) {
	return m_data->get(i);
}

const float & mgl::math::Vector::at(const size_t i) const {
	return m_data->get(i);
}

float & mgl::math::Vector::at(const size_t i) {
	return m_data->get(i);
}

mgl::math::Vector & mgl::math::Vector::operator+=(const Vector & vector) {
	m_data->addEq(vector.m_data);
	return *this;
}
mgl::math::Vector & mgl::math::Vector::operator+=(Vector && vector) {
	m_data->addEq(vector.m_data);
	return *this;
}
mgl::math::Vector & mgl::math::Vector::operator-=(const Vector & vector) {
	m_data->subEq(vector.m_data);
	return *this;
}
mgl::math::Vector & mgl::math::Vector::operator-=(Vector && vector) {
	m_data->subEq(vector.m_data);
	return *this;
}
mgl::math::Vector & mgl::math::Vector::operator*=(const Vector & vector) {
	m_data->mulEq(vector.m_data);
	return *this;
}
mgl::math::Vector & mgl::math::Vector::operator*=(Vector && vector) {
	m_data->mulEq(vector.m_data);
	return *this;
}
mgl::math::Vector & mgl::math::Vector::operator/=(const Vector & vector) {
	m_data->divEq(vector.m_data);
	return *this;
}
mgl::math::Vector & mgl::math::Vector::operator/=(Vector && vector) {
	m_data->divEq(vector.m_data);
	return *this;
}
mgl::math::Vector & mgl::math::Vector::operator*=(float q) {
	m_data->mulEq(q);
	return *this;
}
mgl::math::Vector & mgl::math::Vector::operator/=(float q) {
	m_data->divEq(q);
	return *this;
}

bool mgl::math::Vector::operator==(const Vector & vector) { 
	return m_data->isEq(vector.m_data); 
}
bool mgl::math::Vector::operator==(Vector && vector) {
	return m_data->isEq(vector.m_data);
}
bool mgl::math::Vector::operator==(Vector * vector) {
	return m_data->isEq(vector->m_data);
}
bool mgl::math::Vector::operator!=(const Vector & vector) {
	return m_data->isNEq(vector.m_data);
}
bool mgl::math::Vector::operator!=(Vector && vector) {
	return m_data->isNEq(vector.m_data);
}
bool mgl::math::Vector::operator!=(Vector * vector) {
	return m_data->isNEq(vector->m_data);
}

const mgl::math::Vector mgl::math::operator+(const Vector & v1, const Vector & v2) {
	return Vector(VectorInnerStructure::add(v1.m_data, v2.m_data));
}
const mgl::math::Vector mgl::math::operator+(Vector && v1, Vector && v2) {
	return Vector(VectorInnerStructure::add(v1.m_data, v2.m_data));
}
const mgl::math::Vector mgl::math::operator-(const Vector & v1, const Vector & v2) {
	return Vector(VectorInnerStructure::sub(v1.m_data, v2.m_data));
}
const mgl::math::Vector mgl::math::operator-(Vector&& v1, Vector&& v2) {
	return Vector(VectorInnerStructure::sub(v1.m_data, v2.m_data));
}
const float mgl::math::operator*(const Vector & v1, const Vector & v2) {
	return VectorInnerStructure::dot(v1.m_data, v2.m_data);
}
const float mgl::math::operator*(Vector && v1, Vector && v2) {
	return VectorInnerStructure::dot(v1.m_data, v2.m_data);
}
const mgl::math::Vector mgl::math::operator*(const Vector & v1, const float q) {
	return Vector(VectorInnerStructure::mul(v1.m_data, q));
}
const mgl::math::Vector mgl::math::operator*(Vector && v1, const float q) {
	return Vector(VectorInnerStructure::mul(v1.m_data, q));
}
const mgl::math::Vector mgl::math::operator*(const float & q, const Vector & v1) {
	return Vector(VectorInnerStructure::mul(v1.m_data, q));
}
const mgl::math::Vector mgl::math::operator*(const float q, Vector && v1) {
	return Vector(VectorInnerStructure::mul(v1.m_data, q));
}
const mgl::math::Vector mgl::math::operator/(const Vector & v1, const float q) {
	return Vector(VectorInnerStructure::div(v1.m_data, q));
}
const mgl::math::Vector mgl::math::operator/(Vector && v1, const float q) {
	return Vector(VectorInnerStructure::div(v1.m_data, q));
}
const mgl::math::Vector mgl::math::operator^(const Vector & v1, const Vector & v2) {
	return Vector(VectorInnerStructure::cross(v1.m_data, v2.m_data));
}
const mgl::math::Vector mgl::math::operator^(Vector && v1, Vector && v2) {
	return Vector(VectorInnerStructure::cross(v1.m_data, v2.m_data));
}
