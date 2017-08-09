#pragma once
#include "MGL\Math\vector.hpp"
#include "MGL\SharedHeaders\Exceptions.hpp"
DefineNewMglException(MatrixException)
#include <algorithm>

namespace mgl {
	namespace math {
		template<typename T, size_t R, size_t C>
		class matrix_basic {
		protected:
			vector_basic<T, C> data[R];
		public:
			matrix_basic() {
				for (size_t i = 0; i < 4; i++)
					data[i][i] = T(1);
			}
			template <typename... Tail>
			matrix_basic(typename std::enable_if<sizeof...(Tail) + 1 <= R, vector_basic<T, C>>::type head = vector_basic<T, C>(0),
						 Tail... tail) : data{head, vector_basic<T, C>(tail)...} {}
			matrix_basic(std::initializer_list<std::initializer_list<T>> const& inputs) {
				if (inputs.size() > R)
					throw Exceptions::MatrixException("Too many inputs.");
				size_t i = 0;
				for (auto it : inputs)
					data[i++] = (it);
			}

			vector_basic<T, C> const& operator[](size_t index) const {
				if (index >= R)
					throw Exceptions::MatrixException("There is no element with this index in the matrix");
				return data[index];
			}
			vector_basic<T, C>& operator[](size_t index) {
				if (index >= R)
					throw Exceptions::MatrixException("There is no element with this index in the matrix");
				return data[index];
			}
			T const& operator()(size_t row, size_t column) const {
				if (row >= R || column >= C)
					throw Exceptions::MatrixException("There is no element with this index in the matrix");
				return data[row][column];
			}
			T& operator()(size_t row, size_t column) {
				if (row >= R || column >= C)
					throw Exceptions::MatrixException("There is no element with this index in the matrix");
				return data[row][column];
			}

			T const& at(size_t row, size_t column) const {
				return operator()(row, column);
			}
			T& at(size_t row, size_t column) {
				return operator()(row, column);
			}

			bool isNull() const {
				for (size_t i = 0; i < R; i++)
					for (size_t j = 0; j < C; j++)
						if (data[i][j] != T(0))
							return false;
				return true;
			}

			matrix_basic<T, R, C> const& transpose() {
				static_assert(R != C, "The operation is avaulable for square matrices only.")
				for (size_t i = 0; i < R; i++)
					for (size_t j = 0; j < i; j++) {
						auto t = data[i][j];
						data[i][j] = data[j][i];
						data[j][i] = t;
					}
				return *this;
			}
			matrix_basic<T, C, R> const transposed() const {
				matrix_basic<T, C, R> res;
				for (size_t i = 0; i < R; i++)
					for (size_t j = 0; j < C; j++)
						res[i][j] = at(j, i);
				return res;
			}

			T const* begin() const {
				return &data[0][0];
			}
			T const* end() const {
				return &data[R][C];
			}

			matrix_basic<T, R, C> const& operator+=(matrix_basic<T, R, C> const& other) {
				for (size_t i = 0; i < R; i++)
					for (size_t j = 0; j < C; j++)
						data[i][j] += other.data[i][j];
				return *this;
			}
			matrix_basic<T, R, C> const& operator-=(matrix_basic<T, R, C> const& other) {
				for (size_t i = 0; i < R; i++)
					for (size_t j = 0; j < C; j++)
						data[i][j] -= other.data[i][j];
				return *this;
			}
			matrix_basic<T, R, C> const& operator*=(matrix_basic<T, R, C> const& other) {
				for (size_t i = 0; i < R; i++)
					for (size_t j = 0; j < C; j++)
						data[i][j] *= other.data[i][j];
				return *this;
			}
			matrix_basic<T, R, C> const& operator/=(matrix_basic<T, R, C> const& other) {
				for (size_t i = 0; i < R; i++)
					for (size_t j = 0; j < C; j++)
						data[i][j] /= other.data[i][j];
				return *this;
			}
			matrix_basic<T, R, C> const& operator*=(T const& q) {
				for (size_t i = 0; i < R; i++)
					for (size_t j = 0; j < C; j++)
						data[i][j] *= q;
				return *this;
			}
			matrix_basic<T, R, C> const& operator/=(T const& q) {
				for (size_t i = 0; i < R; i++)
					for (size_t j = 0; j < C; j++)
						data[i][j] /= q;
				return *this;
			}

			template <
			matrix_basic<T, R, C> const& operator%=(matrix_basic<T, R, C> const& other) {
				vector_basic<T,R,C> const SrcA0 = m1[0];
				vector_basic<T,R,C> const SrcA1 = m1[1];
				vector_basic<T,R,C> const SrcA2 = m1[2];
				vector_basic<T,R,C> const SrcA3 = m1[3];
				
				vector_basic<T,R,C> const SrcB0 = m2[0];
				vector_basic<T,R,C> const SrcB1 = m2[1];
				vector_basic<T,R,C> const SrcB2 = m2[2];
				vector_basic<T,R,C> const SrcB3 = m2[3];

				tmat4x4<T, P> Result(uninitialize);
				Result[0] = SrcA0 * SrcB0[0] + SrcA1 * SrcB0[1] + SrcA2 * SrcB0[2] + SrcA3 * SrcB0[3];
				Result[1] = SrcA0 * SrcB1[0] + SrcA1 * SrcB1[1] + SrcA2 * SrcB1[2] + SrcA3 * SrcB1[3];
				Result[2] = SrcA0 * SrcB2[0] + SrcA1 * SrcB2[1] + SrcA2 * SrcB2[2] + SrcA3 * SrcB2[3];
				Result[3] = SrcA0 * SrcB3[0] + SrcA1 * SrcB3[1] + SrcA2 * SrcB3[2] + SrcA3 * SrcB3[3];
				return Result;
			}
		};
		template <typename T>
		class matrix_4x4 : public matrix_basic<T, 4, 4> {
		public:
			using matrix_basic::matrix_basic;
			
			T* determinant() const {
				auto t0 = data[2][2] * data[3][3] - data[3][2] * data[2][3];
				auto t1 = data[2][1] * data[3][3] - data[3][1] * data[2][3];
				auto t2 = data[2][1] * data[3][2] - data[3][1] * data[2][2];
				auto t3 = data[2][0] * data[3][3] - data[3][0] * data[2][3];
				auto t4 = data[2][0] * data[3][2] - data[3][0] * data[2][2];
				auto t5 = data[2][0] * data[3][1] - data[3][0] * data[2][1];

				vector_basic<t, 4> v(data[1][1] * t0 - data[1][2] * t1 + data[1][3] * t2, 
									-data[1][0] * t0 - data[1][2] * t3 + data[1][3] * t4,
									+data[1][0] * t1 - data[1][1] * t3 + data[1][3] * t5,
									-data[1][0] * t2 - data[1][1] * t4 + data[1][2] * t5);

				return data[0][0] * v[0] + data[0][1] * v[1] + data[0][2] * v[2] + data[0][3] * v[3];
			}

		};
		template<typename T, size_t R, size_t C>
		bool operator==(matrix_basic<T, R, C> const& m1, matrix_basic<T, R, C> const& m2) {
			for (size_t i = 0; i < R; i++)
				for (size_t j = 0; j < C; j++)
					if (m1[i][j] != m2[i][j])
						return false;
			return true;
		}
		template<typename T, size_t R, size_t C>
		bool operator!=(matrix_basic<T, R, C> const& m1, matrix_basic<T, R, C> const& m2) {
			return !(m1 == m2);
		}

		template<typename T, size_t R, size_t C>
		matrix_basic<T, R, C> const operator+(matrix_basic<T, R, C> const& m1, matrix_basic<T, R, C> const& m2) {
			matrix_basic<T, R, C> res = m1;
			return res += m2;
		}
		template<typename T, size_t R, size_t C>
		matrix_basic<T, R, C> const operator-(matrix_basic<T, R, C> const& m1, matrix_basic<T, R, C> const& m2) {
			matrix_basic<T, R, C> res = m1;
			return res -= m2;
		}
		template<typename T, size_t R, size_t C>
		matrix_basic<T, R, C> const operator*(matrix_basic<T, R, C> const& m1, matrix_basic<T, R, C> const& m2) {
			matrix_basic<T, R, C> res = m1;
			return res *= m2;
		}
		template<typename T, size_t R, size_t C>
		matrix_basic<T, R, C> const operator*(matrix_basic<T, R, C> const& m1, T const& q) {
			vector_basic<T, S> res = v;
			return res *= q;
		}
		template<typename T, size_t R, size_t C>
		matrix_basic<T, R, C> const operator*(T const& q, matrix_basic<T, R, C> const& m1) {
			vector_basic<T, S> res = v;
			return res *= q;
		}
		template<typename T, size_t R, size_t C>
		matrix_basic<T, R, C> const operator/(matrix_basic<T, R, C> const& m1, matrix_basic<T, R, C> const& m2) {
			matrix_basic<T, R, C> res = m1;
			return res /= m2;
		}
		template<typename T, size_t R, size_t C>
		matrix_basic<T, R, C> const operator/(matrix_basic<T, R, C> const& m1, T const& q) {
			vector_basic<T, S> res = v;
			return res /= q;
		}

		using matrix = matrix_4x4<scalar>;
	}
}