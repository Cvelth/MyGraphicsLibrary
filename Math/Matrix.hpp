#pragma once
#include "..\MyGraphicsLibrary\SharedHeaders\Exceptions.hpp"
DefineNewMglException(MatrixException)

namespace mgl {
	namespace math {
		enum InitialMatrixValue { UnitializedMatrix = 0, IdentityMatrix = 1 };

		class Vector;
		class MatrixInnerStructure;

		class Matrix {
		private:
			MatrixInnerStructure *m_data;
		protected:
			Matrix(MatrixInnerStructure* data);
			Matrix(const MatrixInnerStructure& data);
			Matrix(MatrixInnerStructure&& data);
		public:
			explicit Matrix(const float e00, const float e01, const float e02, const float e03,
				   const float e10, const float e11, const float e12, const float e13,
				   const float e20, const float e21, const float e22, const float e23,
				   const float e30, const float e31, const float e32, const float e33);
			Matrix(const float v);
			Matrix(const float* v);
			Matrix(const float** v);
			Matrix(InitialMatrixValue i = IdentityMatrix);
			~Matrix();

			const Vector column(const size_t c) const;
			const Vector row(const size_t c) const;

			void setColumn(const size_t c, const Vector& v);
			void setRow(const size_t c, const Vector& v);

			float* data(float* data = nullptr) const;
			float** data(float** data) const;

			float* data4x4(float* data = nullptr) const;
			float** data4x4(float** data) const;
			float* data3x3(float* data = nullptr) const;
			float** data3x3(float** data) const;
			float* data2x2(float* data = nullptr) const;
			float** data2x2(float** data) const;

			void fill(const float v);
			const float determinant() const;

			Matrix& translate(const Vector& v);
			Matrix& translate(const float x = 0.f, const float y = 0.f, const float z = 0.f);
			Matrix& rotate(const float angle, const Vector& v);
			Matrix& rotate(const float angle, const float x = 0.f, const float y = 0.f, const float z = 1.f);
			Matrix& scale(const float q);
			Matrix& scale(const float x, const float y, const float z = 1.f);
			Matrix& scale(const Vector& v);

			static const Matrix orthographicMatrix(const float left, const float right,
												   const float bottom, const float top,
												   const float near, const float far);
			static const Matrix perspectiveMatrix(const float left, const float right,
												  const float bottom, const float top,
												  const float near, const float far);

			static const Matrix translationMatrix(const Vector& v);
			static const Matrix translationMatrix(const float x = 0.f, const float y = 0.f, const float z = 0.f);
			static const Matrix rotationMatrix(const float angle, const Vector& v);
			static const Matrix rotationMatrix(const float angle, const float x = 0.f, const float y = 0.f, const float z = 1.f);
			static const Matrix scalingMatrix(const float q);
			static const Matrix scalingMatrix(const float x, const float y, const float z = 1.f);
			static const Matrix scalingMatrix(const Vector& v);

		public:
			const Vector operator[](size_t i) const;
			Vector operator[](size_t i);
			bool operator==(const Matrix& matrix);
			bool operator!=(const Matrix& matrix);

			Matrix& operator+=(const Matrix& matrix);
			Matrix& operator-=(const Matrix& matrix);
			Matrix& operator*=(const Matrix& matrix);
			Matrix& operator*=(const float q);
			Matrix& operator/=(const float q);

			float operator()(size_t row, size_t col);
			const float operator()(size_t row, size_t col) const;

			friend const Matrix operator+(const Matrix& m1, const Matrix& m2);
			friend const Matrix operator-(const Matrix& m1, const Matrix& m2);
			friend const Matrix operator*(const Matrix& m1, const Matrix& m2);
			friend const Vector operator*(const Matrix& m, const Vector& v);
			friend const Vector operator*(const Vector& v, const Matrix& m);
			friend const Matrix operator*(const Matrix& m, const float q);
			friend const Matrix operator*(const float q, const Matrix& m);
			friend const Matrix operator/(const Matrix& m, const float q);
		};

		const Matrix operator+(const Matrix& m1, const Matrix& m2);
		const Matrix operator-(const Matrix& m1, const Matrix& m2);
		const Matrix operator*(const Matrix& m1, const Matrix& m2);
		const Vector operator*(const Matrix& m, const Vector& v);
		const Vector operator*(const Vector& v, const Matrix& m);
		const Matrix operator*(const float q, const Matrix& m);
		const Matrix operator*(const Matrix& m, const float q);
		const Matrix operator/(const Matrix& m, const float q);
	}
}