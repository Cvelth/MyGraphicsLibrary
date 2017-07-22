#pragma once
#include "SharedHeaders\Exceptions.hpp"

namespace mgl {
	namespace Exceptions {
		class VectorException : public AbstractStringException {
			using AbstractStringException::AbstractStringException;
		};
	}
	namespace math {
		class VectorInnerStructure;

		class Vector {
		private:
			VectorInnerStructure *m_data;
		protected:
			Vector(VectorInnerStructure* data);
			Vector(const VectorInnerStructure& data);
			Vector(VectorInnerStructure&& data);
		public:
			explicit Vector(const float x = 0.f, const float y = 0.f, const float z = 0.f, const float w = 0.f);
			Vector(const float* const data);

			~Vector();

			void x(const float a);
			void y(const float a);
			void z(const float a);
			void w(const float a);
			void set(const float x = 0, const float y = 0, const float z = 0, const float w = 0);
			void set(const float *a);
			const float x() const;
			const float y() const;
			const float z() const;
			const float w() const;
			const float* const get() const;
			const float* const get(float* a) const;

			bool isNull() const;
			float length() const;
			void normalize();
			const Vector normalized() const;

		public:
			const float& operator[](size_t i) const;
			float& operator[](size_t i);
			//Are vectors equal?
			bool operator==(const Vector& vector);
			//Are vectors equal?
			bool operator==(Vector&& vector);
			//Are vectors equal?
			bool operator==(Vector* vector);
			//Are vectors not equal?
			bool operator!=(const Vector& vector);
			//Are vectors not equal?
			bool operator!=(Vector&& vector);
			//Are vectors not equal?
			bool operator!=(Vector* vector);

			//Sum of two vectors
			Vector& operator+=(const Vector& vector);
			//Sum of two vectors
			Vector& operator+=(Vector&& vector);
			//Difference of two vectors
			Vector& operator-=(const Vector& vector);
			//Difference of two vectors
			Vector& operator-=(Vector&& vector);
			//A multiplication of vector with a coefficient.
			Vector& operator*=(const float q);
			//A multiplication of vector with a coefficient.
			Vector& operator/=(const float q);

			//Sum of two vectors.
			friend const Vector operator+(const Vector& v1, const Vector& v2);
			//Sum of two vectors.
			friend const Vector operator+(Vector&& v1, Vector&& v2);
			//Difference of two vectors
			friend const Vector operator-(const Vector& v1, const Vector& v2);
			//Difference of two vectors
			friend const Vector operator-(Vector&& v1, Vector&& v2);
			//Dot product of two vectors
			friend const float operator*(const Vector& v1, const Vector& v2);
			//Dot product of two vectors
			friend const float operator*(Vector&& v1, Vector&& v2);
			//A multiplication of vector with a coefficient.
			friend const Vector operator*(const Vector& v1, const float q);
			//A multiplication of vector with a coefficient.
			friend const Vector operator*(Vector&& v1, const float q);
			//A multiplication of vector with a coefficient.
			friend const Vector operator*(const float& q, const Vector& v1);
			//A multiplication of vector with a coefficient.
			friend const Vector operator*(const float q, Vector&& v1);
			//A division of vector with a coefficient.
			friend const Vector operator/(const Vector& v1, const float q);
			//A division of vector with a coefficient.
			friend const Vector operator/(Vector&& v1, const float q);
			//Cross product of two 3-dimentional vectors.
			friend const Vector operator^(const Vector& v1, const Vector& v2);
			//Cross product of two 3-dimentional vectors.
			friend const Vector operator^(Vector&& v1, Vector&& v2);
		};

		//Sum of two vectors.
		const Vector operator+(const Vector& v1, const Vector& v2);
		//Sum of two vectors.
		const Vector operator+(Vector&& v1, Vector&& v2);
		//Difference of two vectors
		const Vector operator-(const Vector& v1, const Vector& v2);
		//Difference of two vectors
		const Vector operator-(Vector&& v1, Vector&& v2);
		//Dot product of two vectors
		const float operator*(const Vector& v1, const Vector& v2);
		//Dot product of two vectors
		const float operator*(Vector&& v1, Vector&& v2);
		//A multiplication of vector with a coefficient.
		const Vector operator*(const Vector& v1, const float q);
		//A multiplication of vector with a coefficient.
		const Vector operator*(Vector&& v1, const float q);
		//A multiplication of vector with a coefficient.
		const Vector operator*(const float& q, const Vector& v1);
		//A multiplication of vector with a coefficient.
		const Vector operator*(const float q, Vector&& v1);
		//A division of vector with a coefficient.
		const Vector operator/(const Vector& v1, const float q);
		//A division of vector with a coefficient.
		const Vector operator/(Vector&& v1, const float q);
		//Cross product of two 3-dimentional vectors.
		const Vector operator^(const Vector& v1, const Vector& v2);
		//Cross product of two 3-dimentional vectors.
		const Vector operator^(Vector&& v1, Vector&& v2);
	}
}