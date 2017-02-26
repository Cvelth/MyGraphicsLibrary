#pragma once
#include "Vector.hpp"

namespace mgl {
	enum InitialValue {UnitializedMatrix = 0, IdentityMatrix = 1};

	template<typename Type>
	class AbstractMatrix {
	private:
		Type m_data[4][4];
	public:
		AbstractMatrix(const Type& e00, const Type& e01, const Type& e02, const Type& e03,
					   const Type& e10, const Type& e11, const Type& e12, const Type& e13,
					   const Type& e20, const Type& e21, const Type& e22, const Type& e23,
					   const Type& e30, const Type& e31, const Type& e32, const Type& e33)
			: m_data({e00, e01, e02, e03, e10, e11, e12, e13,
					 e20, e21, e22, e23, e30, e31, e32, e33}) {}
		AbstractMatrix(const Type* const m) : m_data(m) {}
		AbstractMatrix(const Type& v) : m_data({v, v, v, v, v, v, v, v,
												v, v, v, v, v, v, v, v}) {}
		AbstractMatrix(InitialValue i = IdentityMatrix) : m_data({i, 0, 0, 0, 0, i, 0, 0,
																	 0, 0, i, 0, 0, 0, 0, i}) {}

		const AbstractVector<Type>& column(const size_t& c) const {
			return mgl::AbstractVector(m_data[0][c], m_data[1][c], m_data[2][c], m_data[3][c]);
		}
		const AbstractVector<Type>& row(const size_t& c) const {
			return mgl::AbstractVector(m_data[c][0], m_data[c][1], m_data[c][2], m_data[c][3]);
		}
		Type* data() { return m_data; }
		const Type* data() const { return m_data; }

		void fill(const Type& v) {
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					m_data[i][j] = v;
		}

		const Type& determinant() const {
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

		static const AbstractMatrix<Type>& orthographicMatrix(const Type& left, const Type& right, const Type& top, const Type& bottom, const Type& near, const Type& far) {
			return AbstractMatrix<Type>(2.0 / (right - left), 0, 0, -(right + left) / (right - left),
										0, 2.0 / (top - bottom), 0, -(top + bottom) / (top - bottom),
										0, 0, -2.0 / (far - near), -(far + near) / (far - near),
										0, 0, 0, 1);
		}
		static const AbstractMatrix<Type>& orthographicUnprojectionMatrix(const Type& left, const Type& right, const Type& top, const Type& bottom, const Type& near, const Type& far) {
			return AbstractMatrix<Type>((right - left) / 2.0, 0, 0, (right + left) / 2.0,
										0, (top - bottom) / 2.0, 0, (top + bottom) / 2.0,
										0, 0, -(far - near) / 2.0, (far + near) / 2.0,
										0, 0, 0, 1);
		}
		static const AbstractMatrix<Type>& perspectiveMatrix(const Type& left, const Type& right, const Type& top, const Type& bottom, const Type& near, const Type& far) {
			return AbstractMatrix<Type>(2.0 * near / (right - left), 0, (right + left) / (right - left), 0,
										0, 2.0 * near / (top - bottom), (top + bottom) / (top - bottom), 0,
										0, 0, -(far + near) / (far - near), -2.0 * far * near / (far - near),
										0, 0, -1, 0);
		}

		static const AbstractMatrix<Type>& translationMatrix(const AbstractVector<Type>& v) {
			return translationMatrix(v.x(), v.y(), v.z());
		}
		static const AbstractMatrix<Type>& translationMatrix(const Type& x = 0, const Type& y = 0, const Type& z = 0) {
			return AbstractMatrix<Type>(1, 0, 0, x,
										0, 1, 0, y,
										0, 0, 1, z,
										0, 0, 0, 1);
		}
		static const AbstractMatrix<Type>& rotationMatrix(const Type& angle, const AbstractVector<Type>& v) {
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
		static const AbstractMatrix<Type>& rotationMatrix(const Type& angle, const Type& x = 0, const Type& y = 0, const Type& z = 1) {
			return AbstractMatrix<Type>(angle, mgl::AbstractVector<Type>(x, y, z));
		}
		static const AbstractMatrix<Type>& scalingMatrix(const Type& q) {
			return AbstractMatrix<Type>(q, q, q);
		}
		static const AbstractMatrix<Type>& scalingMatrix(const Type& x = 1, const Type& y = 1, const Type& z = 1) {
			return AbstractMatrix<Type>(x, 0, 0, 0,
										0, y, 0, 0,
										0, 0, z, 0,
										0, 0, 0, 1);
		}
		static const AbstractMatrix<Type>& scalingMatrix(const AbstractVector<Type>& v) {
			return AbstractMatrix<Type>(v.x(), v.y(), v.z());
		}

		bool operator==(const AbstractMatrix<Type>& matrix) {
			return !operator!=(matrix);
		}
		bool operator!=(const AbstractMatrix<Type>& matrix) {
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					if (m_data[i][j] == matrix.m_data[i][j])
						return false;
			return true;
		}
		AbstractMatrix<Type>& operator+=(const AbstractMatrix<Type>& matrix) {
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					m_data[i][j] += matrix.m_data[i][j];
			return this;
		}
		AbstractMatrix<Type>& operator-=(const AbstractMatrix<Type>& matrix) {
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					m_data[i][j] -= matrix.m_data[i][j];
			return this;
		}
		AbstractMatrix<Type>& operator*=(const AbstractMatrix<Type>& matrix) {
			m_data[0][0] = m_data[0][0] * matrix.m_data[0][0] + m_data[1][0] * matrix.m_data[0][1] + m_data[2][0] * matrix.m_data[0][2] + m_data[3][0] * matrix.m_data[0][3];
			m_data[0][1] = m_data[0][1] * matrix.m_data[0][0] + m_data[1][1] * matrix.m_data[0][1] + m_data[2][1] * matrix.m_data[0][2] + m_data[3][1] * matrix.m_data[0][3];
			m_data[0][2] = m_data[0][2] * matrix.m_data[0][0] + m_data[1][2] * matrix.m_data[0][1] + m_data[2][2] * matrix.m_data[0][2] + m_data[3][2] * matrix.m_data[0][3];
			m_data[0][3] = m_data[0][3] * matrix.m_data[0][0] + m_data[1][3] * matrix.m_data[0][1] + m_data[2][3] * matrix.m_data[0][2] + m_data[3][3] * matrix.m_data[0][3];

			m_data[1][0] = m_data[0][0] * matrix.m_data[1][0] + m_data[1][0] * matrix.m_data[1][1] + m_data[2][0] * matrix.m_data[1][2] + m_data[3][0] * matrix.m_data[1][3];
			m_data[1][1] = m_data[0][1] * matrix.m_data[1][0] + m_data[1][1] * matrix.m_data[1][1] + m_data[2][1] * matrix.m_data[1][2] + m_data[3][1] * matrix.m_data[1][3];
			m_data[1][2] = m_data[0][2] * matrix.m_data[1][0] + m_data[1][2] * matrix.m_data[1][1] + m_data[2][2] * matrix.m_data[1][2] + m_data[3][2] * matrix.m_data[1][3];
			m_data[1][3] = m_data[0][3] * matrix.m_data[1][0] + m_data[1][3] * matrix.m_data[1][1] + m_data[2][3] * matrix.m_data[1][2] + m_data[3][3] * matrix.m_data[1][3];

			m_data[2][0] = m_data[0][0] * matrix.m_data[2][0] + m_data[1][0] * matrix.m_data[2][1] + m_data[2][0] * matrix.m_data[2][2] + m_data[3][0] * matrix.m_data[2][3];
			m_data[2][1] = m_data[0][1] * matrix.m_data[2][0] + m_data[1][1] * matrix.m_data[2][1] + m_data[2][1] * matrix.m_data[2][2] + m_data[3][1] * matrix.m_data[2][3];
			m_data[2][2] = m_data[0][2] * matrix.m_data[2][0] + m_data[1][2] * matrix.m_data[2][1] + m_data[2][2] * matrix.m_data[2][2] + m_data[3][2] * matrix.m_data[2][3];
			m_data[2][3] = m_data[0][3] * matrix.m_data[2][0] + m_data[1][3] * matrix.m_data[2][1] + m_data[2][3] * matrix.m_data[2][2] + m_data[3][3] * matrix.m_data[2][3];

			m_data[3][0] = m_data[0][0] * matrix.m_data[3][0] + m_data[1][0] * matrix.m_data[3][1] + m_data[2][0] * matrix.m_data[3][2] + m_data[3][0] * matrix.m_data[3][3];
			m_data[3][1] = m_data[0][1] * matrix.m_data[3][0] + m_data[1][1] * matrix.m_data[3][1] + m_data[2][1] * matrix.m_data[3][2] + m_data[3][1] * matrix.m_data[3][3];
			m_data[3][2] = m_data[0][2] * matrix.m_data[3][0] + m_data[1][2] * matrix.m_data[3][1] + m_data[2][2] * matrix.m_data[3][2] + m_data[3][2] * matrix.m_data[3][3];
			m_data[3][3] = m_data[0][3] * matrix.m_data[3][0] + m_data[1][3] * matrix.m_data[3][1] + m_data[2][3] * matrix.m_data[3][2] + m_data[3][3] * matrix.m_data[3][3];

			return this;
		}
		AbstractMatrix<Type>& operator*=(const Type& q) {
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					m_data[i][j] *= q;
			return this;
		}
		AbstractMatrix<Type>& operator/=(const Type& q) {
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					m_data[i][j] /= q;
			return this;
		}

		Type& operator()(size_t row, size_t col) { return m_data[row][col]; }
		const Type& operator()(size_t row, size_t col) const { return m_data[row][col]; }

		friend const AbstractMatrix<Type>& operator+(const AbstractMatrix<Type>& m1, const AbstractMatrix<Type>& m2);
		friend const AbstractMatrix<Type>& operator-(const AbstractMatrix<Type>& m1, const AbstractMatrix<Type>& m2);		
		friend const AbstractMatrix<Type>& operator*(const AbstractMatrix<Type>& m1, const AbstractMatrix<Type>& m2);		
		friend const AbstractVector<Type>& operator*(const AbstractMatrix<Type>& m, const AbstractVector<Type>& v);		
		friend const AbstractVector<Type>& operator*(const AbstractVector<Type>& v, const AbstractMatrix<Type>& m);		
		friend const AbstractMatrix<Type>& operator*(const Type& q, const AbstractMatrix<Type>& m);		
		friend const AbstractMatrix<Type>& operator*(const AbstractMatrix<Type>& m, const Type& q);		
		friend const AbstractMatrix<Type>& operator/(const AbstractMatrix<Type>& m, const Type& q);	
	};

	template<typename Type>
	const AbstractMatrix<Type>& operator+(const AbstractMatrix<Type>& m1, const AbstractMatrix<Type>& m2) {
		AbstractMatrix<Type> res(m1);
		for (size_t i = 0; i < 4; i++)
			for (size_t j = 0; j < 4; j++)
				res[i][j] += m2[i][j];
		return res;
	}
	template<typename Type>
	const AbstractMatrix<Type>& operator-(const AbstractMatrix<Type>& m1, const AbstractMatrix<Type>& m2) {
		AbstractMatrix<Type> res(m1);
		for (size_t i = 0; i < 4; i++)
			for (size_t j = 0; j < 4; j++)
				res[i][j] -= m2[i][j];
		return res;
	}
	template<typename Type>
	const AbstractMatrix<Type>& operator*(const AbstractMatrix<Type>& m1, const AbstractMatrix<Type>& m2) {
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
	const AbstractVector<Type>& operator*(const AbstractMatrix<Type>& m, const AbstractVector<Type>& v) {
		return AbstractVector<Type>(m.m_data[0][0] * v[0] + m.m_data[0][1] * v[1] + m.m_data[0][2] * v[2] + m.m_data[0][3] * v[3],
									m.m_data[1][0] * v[0] + m.m_data[1][1] * v[1] + m.m_data[1][2] * v[2] + m.m_data[1][3] * v[3],
									m.m_data[2][0] * v[0] + m.m_data[2][1] * v[1] + m.m_data[2][2] * v[2] + m.m_data[2][3] * v[3],
									m.m_data[3][0] * v[0] + m.m_data[3][1] * v[1] + m.m_data[3][2] * v[2] + m.m_data[3][3] * v[3]);
	}
	template<typename Type>
	const AbstractVector<Type>& operator*(const AbstractVector<Type>& v, const AbstractMatrix<Type>& m) {
		return AbstractVector<Type>(v[0] * m.m_data[0][0] + v[1] * m.m_data[1][0] + v[2] * m.m_data[2][0] + v[3] * m.m_data[3][0],
									v[0] * m.m_data[0][1] + v[1] * m.m_data[1][1] + v[2] * m.m_data[2][1] + v[3] * m.m_data[3][1],
									v[0] * m.m_data[0][2] + v[1] * m.m_data[1][2] + v[2] * m.m_data[2][2] + v[3] * m.m_data[3][2],
									v[0] * m.m_data[0][3] + v[1] * m.m_data[1][3] + v[2] * m.m_data[2][3] + v[3] * m.m_data[3][3]);
	}
	template<typename Type>
	const AbstractMatrix<Type>& operator*(const Type& q, const AbstractMatrix<Type>& m) { return m * q; }
	template<typename Type>
	const AbstractMatrix<Type>& operator*(const AbstractMatrix<Type>& m, const Type& q) {
		AbstractMatrix<Type> res(m1);
		for (size_t i = 0; i < 4; i++)
			for (size_t j = 0; j < 4; j++)
				res[i][j] *= q;
		return res;
	}
	template<typename Type>
	const AbstractMatrix<Type>& operator/(const AbstractMatrix<Type>& m, const Type& q) {
		AbstractMatrix<Type> res(m1);
		for (size_t i = 0; i < 4; i++)
			for (size_t j = 0; j < 4; j++)
				res[i][j] /= q;
		return res;
	}

	using Matrix = AbstractMatrix<float>;
}