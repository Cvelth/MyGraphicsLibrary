#pragma once
#include "Enums.hpp"

namespace mgl {
	class VectorException : public AbstractStringException {
		using AbstractStringException::AbstractStringException;
	};

	template <typename Type>
	class AbstractVector {
	private:
		Type m_data[4];
	public:
		AbstractVector(const Type& x = 0, const Type& y = 0, const Type& z = 0, const Type& w = 0);
		AbstractVector(const Type* const data);
		bool isNull() const;
		Type length() const;
		void normalize();
		const AbstractVector normalized() const;

		void x(const Type& t);
		void y(const Type& t);
		void z(const Type& t);
		void w(const Type& t);
		void set(const Type& x = 0, const Type& y = 0, const Type& z = 0, const Type& w = 0);
		const Type& x() const;
		const Type& y() const;
		const Type& z() const;
		const Type& w() const;
		const Type* const get() const;

		AbstractVector<Type>& operator+=(const AbstractVector<Type>& vector);
		AbstractVector<Type>& operator-=(const AbstractVector<Type>& vector);
		AbstractVector<Type>& operator*=(const Type& q);
		AbstractVector<Type>& operator/=(const Type& q);
		bool operator==(const AbstractVector<Type>& vector);
		bool operator!=(const AbstractVector<Type>& vector);

		const Type& operator[](size_t i) const;
		Type& operator[](size_t i);
		
		friend const AbstractVector<Type> operator+(const AbstractVector<Type>& v1, const AbstractVector<Type>& v2);
		friend const AbstractVector<Type> operator-(const AbstractVector<Type>& v1, const AbstractVector<Type>& v2);
		friend const Type operator*(const AbstractVector<Type>& v1, const AbstractVector<Type>& v2);
		friend const AbstractVector<Type> operator*(const AbstractVector<Type>& v1, const Type& q);
		friend const AbstractVector<Type> operator*(const Type& q, const AbstractVector<Type>& v1);
		friend const AbstractVector<Type> operator/(const AbstractVector<Type>& v1, const Type& q);
	};

	template <typename Type>
	const AbstractVector<Type> operator+(const AbstractVector<Type>& v1, const AbstractVector<Type>& v2);
	template <typename Type>
	const AbstractVector<Type> operator-(const AbstractVector<Type>& v1, const AbstractVector<Type>& v2);
	template <typename Type>
	const AbstractVector<Type> operator*(const AbstractVector<Type>& v1, const Type& q);
	template <typename Type>
	const AbstractVector<Type> operator*(const Type& q, const AbstractVector<Type>& v1);
	template <typename Type>
	const AbstractVector<Type> operator/(const AbstractVector<Type>& v1, const Type& q);

	template <typename Type>
	const Type operator*(const AbstractVector<Type>& v1, const AbstractVector<Type>& v2);

	using Vector = AbstractVector<float>;

	using Vertex = Vector;
}