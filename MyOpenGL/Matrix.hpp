#pragma once
#include "Vector.hpp"
#include "AbstractException.hpp"

namespace mgl {
	enum InitialValue { UnitializedMatrix = 0, IdentityMatrix = 1 };
	class MatrixException : AbstractStringException {
		using AbstractStringException::AbstractStringException;
	};

	struct MatrixHolder {
		float m[16];

		MatrixHolder() {}
		MatrixHolder(const float& e00, const float& e01, const float& e02, const float& e03,
					 const float& e10, const float& e11, const float& e12, const float& e13,
					 const float& e20, const float& e21, const float& e22, const float& e23,
					 const float& e30, const float& e31, const float& e32, const float& e33);

		void fill(const float& v);
		void identityFill();

		inline float* data() { return m; }
		inline const float* data() const { return m; }

		inline float& operator()(const size_t i, const size_t j) {
			return m[i * 4 + j];
		}
		inline const float& operator()(const size_t i, const size_t j) const {
			return m[i * 4 + j];
		}
		MatrixHolder& operator=(const MatrixHolder& h);
	};

	class Matrix {
	private:
		MatrixHolder m_data;
	public:
		Matrix(const float& e00, const float& e01, const float& e02, const float& e03,
			   const float& e10, const float& e11, const float& e12, const float& e13,
			   const float& e20, const float& e21, const float& e22, const float& e23,
			   const float& e30, const float& e31, const float& e32, const float& e33);
		Matrix(const Matrix& m);
		Matrix(const float& v);
		Matrix(InitialValue i = IdentityMatrix);
		~Matrix();

		const Vector column(const size_t& c) const;
		const Vector row(const size_t& c) const;

		void setColumn(const size_t& c, const Vector& v);
		void setRow(const size_t& c, const Vector& v);
		
		inline float* data() { return m_data.data(); }
		inline const float* data() const { return m_data.data(); }

		void fill(const float& v);
		const float determinant() const;

		void translate(const Vector& v);
		void translate(const float& x = 0, const float& y = 0, const float& z = 0);
		void rotate(const float& angle, const Vector& v);
		void rotate(const float& angle, const float& x = 0, const float& y = 0, const float& z = 0);
		void scale(const float& q);
		void scale(const float& x, const float& y, const float& z = 1.f);
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
		static const Matrix translationMatrix(const float& x = 0.f, const float& y = 0.f, const float& z = 0.f);				
		static const Matrix rotationMatrix(const float& angle, const Vector& v);		
		static const Matrix rotationMatrix(const float& angle, const float& x = 0.f, const float& y = 0.f, const float& z = 1.f);
		static const Matrix scalingMatrix(const float& q);		
		static const Matrix scalingMatrix(const float& x, const float& y, const float& z = 1.f);
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

		float& operator()(size_t row, size_t col) { return m_data(row, col); }
		const float& operator()(size_t row, size_t col) const { return m_data(row, col); }

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