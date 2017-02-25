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
					   const Type& e30, const Type& e31, const Type& e32, const Type& e33);
		AbstractMatrix(const Type* const m);
		AbstractMatrix(const Type& v);
		AbstractMatrix(InitialValue init = IdentityMatrix);

		const AbstractVector<Type>& column(const size_t& c) const;
		const AbstractVector<Type>& row(const size_t& c) const;

		Type* data();
		const Type* data() const;

		void fill(const Type& v);

		const Type& determinant() const;

		static const AbstractMatrix<Type>& orthographicMatrix(const Type& left, const Type& right, const Type& top, const Type& bottom, const Type& near, const Type& far);
		static const AbstractMatrix<Type>& orthographicUnprojectionMatrix(const Type& left, const Type& right, const Type& top, const Type& bottom, const Type& near, const Type& far);
		static const AbstractMatrix<Type>& perspectiveMatrix(const Type& left, const Type& right, const Type& top, const Type& bottom, const Type& near, const Type& far);

		static const AbstractMatrix<Type>& translationMatrix(const AbstractVector<Type>& v);
		static const AbstractMatrix<Type>& translationMatrix(const Type& x = 0, const Type& y = 0, const Type& z = 0);
		static const AbstractMatrix<Type>& rotationMatrix(const Type& angle, const AbstractVector<Type>& v);
		static const AbstractMatrix<Type>& rotationMatrix(const Type& angle, const Type& x = 0, const Type& y = 0, const Type& z = 1);
		static const AbstractMatrix<Type>& scalingMatrix(const Type& q);
		static const AbstractMatrix<Type>& scalingMatrix(const Type& x = 1, const Type& y = 1, const Type& z = 1);
		static const AbstractMatrix<Type>& scalingMatrix(const AbstractVector<Type>& v);

		bool operator==(const AbstractMatrix<Type>& matrix);
		bool operator!=(const AbstractMatrix<Type>& matrix);
		AbstractMatrix<Type>& operator+=(const AbstractMatrix<Type>& matrix);
		AbstractMatrix<Type>& operator-=(const AbstractMatrix<Type>& matrix);
		AbstractMatrix<Type>& operator*=(const AbstractMatrix<Type>& matrix);
		AbstractMatrix<Type>& operator*=(const Type& q);
		AbstractMatrix<Type>& operator/=(const Type& q);

		Type& operator()(size_t row, size_t col);
		const Type& operator()(size_t row, size_t col) const;

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
	const AbstractMatrix<Type>& operator+(const AbstractMatrix<Type>& m1, const AbstractMatrix<Type>& m2);
	template<typename Type>
	const AbstractMatrix<Type>& operator-(const AbstractMatrix<Type>& m1, const AbstractMatrix<Type>& m2);
	template<typename Type>
	const AbstractMatrix<Type>& operator*(const AbstractMatrix<Type>& m1, const AbstractMatrix<Type>& m2);
	template<typename Type>
	const AbstractVector<Type>& operator*(const AbstractMatrix<Type>& m, const AbstractVector<Type>& v);
	template<typename Type>
	const AbstractVector<Type>& operator*(const AbstractVector<Type>& v, const AbstractMatrix<Type>& m);
	template<typename Type>
	const AbstractMatrix<Type>& operator*(const Type& q, const AbstractMatrix<Type>& m);
	template<typename Type>
	const AbstractMatrix<Type>& operator*(const AbstractMatrix<Type>& m, const Type& q);
	template<typename Type>
	const AbstractMatrix<Type>& operator/(const AbstractMatrix<Type>& m, const Type& q);

	using Matrix = AbstractMatrix<float>;
}