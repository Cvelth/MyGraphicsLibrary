#pragma once
#include "Vector.hpp"

namespace mgl {
	enum InitialValue { UnitializedMatrix = 0, IdentityMatrix = 1 };

	class Matrix {
	private:
		float (*m_data)[4];
	public:
		Matrix(const float& e00, const float& e01, const float& e02, const float& e03,
			   const float& e10, const float& e11, const float& e12, const float& e13,
			   const float& e20, const float& e21, const float& e22, const float& e23,
			   const float& e30, const float& e31, const float& e32, const float& e33);
		Matrix(const float& v);
		Matrix(InitialValue i = IdentityMatrix);
		~Matrix();

		const Vector column(const size_t& c) const;
		const Vector row(const size_t& c) const;

		void setColumn(const size_t& c, const Vector& v);
		void setRow(const size_t& c, const Vector& v);
		
		float (*data())[4] { return m_data; }
		const float (*data() const)[4] { return m_data; }

		void fill(const float& v);
		const float determinant() const;

		void translate(const Vector& v);
		void translate(const float& x = 0, const float& y = 0, const float& z = 0);
		void rotate(const float& angle, const Vector& v);
		void rotate(const float& angle, const float& x = 0, const float& y = 0, const float& z = 0);
		void scale(const float& q);
		void scale(const float& x = 1.f, const float& y = 1.f, const float& z = 1.f);
		void scale(const Vector& v);
		
		static const Matrix orthographicMatrix(const float& left, const float& right,
												const float& top, const float& bottom,
												const float& near, const float& far);
		static const Matrix orthographicUnprojectionMatrix(const float& left, const float& right,
														   const float& top, const float& bottom,
														   const float& near, const float& far);
		static const Matrix perspectiveMatrix(const float& left, const float& right,
													  const float& top, const float& bottom,
													  const float& near, const float& far);
		
		static const Matrix translationMatrix(const Vector& v);
		static const Matrix translationMatrix(const float& x = 0, const float& y = 0, const float& z = 0);				
		static const Matrix rotationMatrix(const float& angle, const Vector& v);		
		static const Matrix rotationMatrix(const float& angle, const float& x = 0, const float& y = 0, const float& z = 1);
		static const Matrix scalingMatrix(const float& q);		
		static const Matrix scalingMatrix(const float& x = 1, const float& y = 1, const float& z = 1);
		static const Matrix scalingMatrix(const Vector& v);
		
	public:
		const Vector operator[](size_t i) const;
		Vector operator[](size_t i);
		bool operator==(const Matrix& matrix);		
		bool operator!=(const Matrix& matrix);
		
		Matrix& operator+=(const Matrix& matrix);
		Matrix& operator-=(const Matrix& matrix);		
		Matrix& operator*=(const Matrix& matrix);		
		Matrix& operator*=(const float& q);		
		Matrix& operator/=(const float& q);		

		float& operator()(size_t row, size_t col) { return m_data[row][col]; }
		const float& operator()(size_t row, size_t col) const { return m_data[row][col]; }

		friend const Matrix operator+(const Matrix& m1, const Matrix& m2);
		friend const Matrix operator-(const Matrix& m1, const Matrix& m2);
		friend const Matrix operator*(const Matrix& m1, const Matrix& m2);
		friend const Vector operator*(const Matrix& m, const Vector& v);
		friend const Vector operator*(const Vector& v, const Matrix& m);
		friend const Matrix operator*(const float& q, const Matrix& m);
		friend const Matrix operator*(const Matrix& m, const float& q);
		friend const Matrix operator/(const Matrix& m, const float& q);
	};
}