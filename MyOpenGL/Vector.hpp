#pragma once
#include "AbstractException.hpp"

namespace mgl {
	class VectorException : public AbstractStringException {
		using AbstractStringException::AbstractStringException;
	};

	template <typename Type>
	class AbstractVector {
	private:
		Type m_data[4];
	public:
		AbstractVector(const Type& x = 0, const Type& y = 0, const Type& z = 0, const Type& w = 0) {
			m_data[0] = (x); m_data[1] = (y); m_data[2] = (z); m_data[3] = (w); 
		}
		AbstractVector(const Type* const data) { m_data = {data[0], data[1], data[2], data[3]}; }
		bool isNull() const {
			for (int i = 0; i < 4; i++)
				if (m_data[i] != 0)
					return false;
			return true;
		}
		Type length() const {
			Type res = 0;
			for (int i = 0; i < 4; i++)
				res += m_data[i] * m_data[i];
			return sqrt(res);
		}
		void normalize() {
			Type l = length();
			for (int i = 0; i < 4; i++)
				m_data[i] /= l;
		}
		const AbstractVector normalized() const {
			return mgl::AbstractVector<Type>(*this / length());
		}

		void x(const Type& t) {m_data[0] = t;}
		void y(const Type& t) {m_data[1] = t;}
		void z(const Type& t) {m_data[2] = t;}
		void w(const Type& t) {m_data[3] = t;}
		void set(const Type& x = 0, const Type& y = 0, const Type& z = 0, const Type& w = 0) { m_data = {x,y,z,w}; }
		const Type& x() const { return m_data[0]; }
		const Type& y() const { return m_data[1]; }
		const Type& z() const { return m_data[2]; }
		const Type& w() const { return m_data[3]; }
		const Type* const get() const { return m_data; }

		AbstractVector<Type>& operator+=(const AbstractVector<Type>& vector) {
			for (int i = 0; i < 4; i++)
				m_data[i] += vector.m_data[i];
			return this;
		}
		AbstractVector<Type>& operator-=(const AbstractVector<Type>& vector) {
			for (int i = 0; i < 4; i++)
				m_data[i] -= vector.m_data[i];
			return this;
		}
		AbstractVector<Type>& operator*=(const Type& q) {
			for (int i = 0; i < 4; i++)
				m_data[i] *= q;
			return this;
		}
		AbstractVector<Type>& operator/=(const Type& q) {
			for (int i = 0; i < 4; i++)
				m_data[i] /= q;
			return this;
		}
		bool operator==(const AbstractVector<Type>& vector) { return !operator!=(vector); }
		bool operator!=(const AbstractVector<Type>& vector) {
			for (int i = 0; i < 4; i++)
				if (vector.m_data[i] == m_data[i])
					return false;
			return true;
		}

		const Type& operator[](size_t i) const { return m_data[i]; }
		Type& operator[](size_t i) { return m_data[i]; }

		friend const AbstractVector<Type> operator+(const AbstractVector<Type>& v1, const AbstractVector<Type>& v2);
		friend const AbstractVector<Type> operator-(const AbstractVector<Type>& v1, const AbstractVector<Type>& v2);
		friend const Type operator*(const AbstractVector<Type>& v1, const AbstractVector<Type>& v2);
		friend const AbstractVector<Type> operator*(const AbstractVector<Type>& v1, const Type& q);
		friend const AbstractVector<Type> operator*(const Type& q, const AbstractVector<Type>& v1);
		friend const AbstractVector<Type> operator/(const AbstractVector<Type>& v1, const Type& q);
	};

	template <typename Type> const AbstractVector<Type> operator+(const AbstractVector<Type>& v1, const AbstractVector<Type>& v2) {
		AbstractVector<Type> res;
		for (int i = 0; i < 4; i++)
			res.m_data[i] = v1.m_data[i] + v2.m_data[i];
		return res;
	}
	template <typename Type> const AbstractVector<Type> operator-(const AbstractVector<Type>& v1, const AbstractVector<Type>& v2) {
		AbstractVector<Type> res;
		for (int i = 0; i < 4; i++)
			res.m_data[i] = v1.m_data[i] - v2.m_data[i];
		return res;
	}
	template <typename Type> const AbstractVector<Type> operator*(const AbstractVector<Type>& v1, const Type& q) {
		AbstractVector<Type> res;
		for (int i = 0; i < 4; i++)
			res.m_data[i] = v1.m_data[i] * q;
		return res;
	}
	template <typename Type> const AbstractVector<Type> operator*(const Type& q, const AbstractVector<Type>& v1) {
		return v1 * q;
	}
	template <typename Type> const AbstractVector<Type> operator/(const AbstractVector<Type>& v1, const Type& q) {
		AbstractVector<Type> res;
		for (int i = 0; i < 4; i++)
			res.m_data[i] = v1.m_data[i] / q;
		return res;
	}
	template <typename Type> const Type operator*(const AbstractVector<Type>& v1, const AbstractVector<Type>& v2) {
		Type res = 0;
		for (int i = 0; i < 4; i++)
			res += v1.m_data[i] * v2.m_data[i];
		return res;
	}

	using Vector = AbstractVector<float>;

	class Vertex : public Vector {
		using Vector::AbstractVector;
	};
}