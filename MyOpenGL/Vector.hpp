#pragma once
#include "AbstractException.hpp"

namespace mgl {
	class VectorException : public AbstractStringException {
		using AbstractStringException::AbstractStringException;
	};

	class Vector {
	private:
		float m_data[4];
	public:
		Vector(float x = 0.f, float y = 0.f, float z = 0.f, float w = 0.f);		
		Vector(const float* const data);
		Vector(const Vector& v);
		Vector(Vector&& v);
		
		bool isNull() const;
		float length() const;
		void normalize();		
		const Vector normalized() const;		

		void x(const float& t) { m_data[0] = t; }
		void y(const float& t) { m_data[1] = t; }
		void z(const float& t) { m_data[2] = t; }
		void w(const float& t) { m_data[3] = t; }
		void set(const float& x = 0, const float& y = 0, const float& z = 0, const float& w = 0) { m_data[0] = x; m_data[1] = y; m_data[2] = z; m_data[3] = w; }
		const float& x() const { return m_data[0]; }
		const float& y() const { return m_data[1]; }
		const float& z() const { return m_data[2]; }
		const float& w() const { return m_data[3]; }
		const float* const get() const { return m_data; }

	public:
		const float& operator[](size_t i) const { return m_data[i]; }
		float& operator[](size_t i) { return m_data[i]; }
		bool operator==(const Vector& vector);
		bool operator!=(const Vector& vector);

		Vector& operator+=(const Vector& vector);		
		Vector& operator-=(const Vector& vector);		
		Vector& operator*=(const float& q);		
		Vector& operator/=(const float& q);		

		friend const Vector operator+(const Vector& v1, const Vector& v2);
		friend const Vector operator-(const Vector& v1, const Vector& v2);
		friend const float  operator*(const Vector& v1, const Vector& v2);
		friend const Vector operator*(const Vector& v1, const float& q);
		friend const Vector operator*(const float& q, const Vector& v1);
		friend const Vector operator/(const Vector& v1, const float& q);
	};

	const Vector operator+(const Vector& v1, const Vector& v2);	
	const Vector operator-(const Vector& v1, const Vector& v2);
	const float  operator*(const Vector& v1, const Vector& v2);
	const Vector operator*(const Vector& v1, const float& q);	
	const Vector operator*(const float& q, const Vector& v1);	
	const Vector operator/(const Vector& v1, const float& q);
}