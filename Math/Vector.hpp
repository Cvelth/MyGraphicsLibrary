#pragma once
#include "MGL\SharedHeaders\Exceptions.hpp"
DefineNewMglException(VectorException)
#include <algorithm>

namespace mgl {
	namespace math {
		template<typename T, size_t S>
		class vector_basic {
		protected:
			T m_data[S];
		protected:
			vector_basic(size_t const s, T* data) {
				static_assert(s <= S, "To much data.");
				std::copy(data, data + s, m_data);
				std::fill(m_data + s, m_data + S, T(0));
			}
		public:
			template <typename... Tail>
			vector_basic(typename std::enable_if<sizeof...(Tail) + 1 <= S, T>::type head = T(0.0), 
					Tail... tail)
				: m_data{head, T(tail)...} {}
			template<size_t S_O>
			vector_basic(vector_basic<T, S_O> const& other, typename std::enable_if<S_O < S>::type* size = 0) {
				std::copy(other.begin(), other.end(), m_data);
				std::fill(m_data + S_O, m_data + S, T(0));
			}
			template<size_t S_O>
			vector_basic(vector_basic<T, S_O>&& other, typename std::enable_if<S_O < S>::type* size = 0) {
				std::move(other.begin(), other.end(), m_data);
				std::fill(m_data + S_O, m_data + S, T(0));
			}

			T const& at(size_t index) const {
				if (index >= S)
					throw Exceptions::VectorException("There is no element with this index in the vector");
				return m_data[index];
			}
			T& at(size_t index) {
				if (index >= S)
					throw Exceptions::VectorException("There is no element with this index in the vector");
				return m_data[index];
			}
			T const& operator[](size_t index) const {
				if (index >= S)
					throw Exceptions::VectorException("There is no element with this index in the vector");
				return m_data[index];
			}
			T& operator[](size_t index) {
				if (index >= S)
					throw Exceptions::VectorException("There is no element with this index in the vector");
				return m_data[index];
			}

			bool isNull() const {
				for (size_t i = 0; i < S; i++)
					if (m_data[i] != T(0))
						return false;
				return true;
			}
			size_t length() const {
				T sum = T(0);
				for (size_t i = 0; i < S; i++)
					sum += m_data[i] * m_data[i];
				return std::sqrtf(sum);
			}
			void normalize() {
				auto l = length();
				for (size_t i = 0; i < S; i++)
					m_data[i] /= l;
			}
			vector_basic<T, S> const normalized() const {
				vector_basic<T, S> ret(*this);
				ret.normalize();
				return ret;
			}

			T const* begin() const {
				return m_data;
			}
			T const* end() const{
				return m_data + S;
			}

			vector_basic<T, S> const& operator+=(vector_basic<T, S> const& other) {
				for (size_t i = 0; i < S; i++)
					m_data[i] += other.m_data[i];
				return *this;
			}
			vector_basic<T, S> const& operator-=(vector_basic<T, S> const& other) {
				for (size_t i = 0; i < S; i++)
					m_data[i] -= other.m_data[i];
				return *this;
			}
			vector_basic<T, S> const& operator*=(vector_basic<T, S> const& other) {
				for (size_t i = 0; i < S; i++)
					m_data[i] *= other.m_data[i];
				return *this;
			}
			vector_basic<T, S> const& operator/=(vector_basic<T, S> const& other) {
				for (size_t i = 0; i < S; i++)
					m_data[i] /= other.m_data[i];
				return *this;
			}
			vector_basic<T, S> const& operator*=(T const& q) {
				for (size_t i = 0; i < S; i++)
					m_data[i] *= q;
				return *this;
			}
			vector_basic<T, S> const& operator/=(T const& q) {
				for (size_t i = 0; i < S; i++)
					m_data[i] /= q;
				return *this;
			}
		};
		template<typename T, size_t S>
		class vector_homogeneous : public vector_basic<T, S + 1> {
		protected:
			vector_homogeneous(size_t const s, T* data) : vector_basic<T, S + 1>::vector_basic(s, data) { m_data[S] = T(1); }
		public:
			template<typename... Tail>
			vector_homogeneous(typename std::enable_if<sizeof...(Tail) + 1 <= S, T>::type head = T(0), 
							   Tail... tail) : vector_basic(head, tail...) { m_data[S] = T(1); }
			template<size_t S_O>
			vector_homogeneous(vector_basic<T, S_O> const& other, typename std::enable_if<S_O < S + 1>::type* size = 0)
				: vector_basic<T, S + 1>::vector_basic(other) { m_data[S] = T(1); }
			template<size_t S_O>
			vector_homogeneous(vector_basic<T, S_O>&& other, typename std::enable_if<S_O < S + 1>::type* size = 0)
				: vector_basic<T, S + 1>::vector_basic(other) { m_data[S] = T(1); }

			template<size_t C = 0> typename std::enable_if<S >= C, T>::type const& x() const { return m_data[0]; }
			template<size_t C = 1> typename std::enable_if<S >= C, T>::type const& y() const { return m_data[1]; }
			template<size_t C = 2> typename std::enable_if<S >= C, T>::type const& z() const { return m_data[2]; }
			template<size_t C = 3> typename std::enable_if<S >= C, T>::type const& w() const { return m_data[3]; }
			template<size_t C = 0> typename std::enable_if<S >= C>::type x(T const& value) { m_data[0] = value; }
			template<size_t C = 1> typename std::enable_if<S >= C>::type y(T const& value) { m_data[1] = value; }
			template<size_t C = 2> typename std::enable_if<S >= C>::type z(T const& value) { m_data[2] = value; }
			template<size_t C = 3> typename std::enable_if<S >= C>::type w(T const& value) { m_data[3] = value; }
			template<size_t C = 0> typename std::enable_if<S >= C>::type set(T const& x) { m_data[0] = x; }
			template<size_t C = 1> typename std::enable_if<S >= C>::type set(T const& x, T const& y) { m_data[0] = x; m_data[1] = y; }
			template<size_t C = 2> typename std::enable_if<S >= C>::type set(T const& x, T const& y, T const& z) { m_data[0] = x; m_data[1] = y; m_data[2] = z; }
			template<size_t C = 3> typename std::enable_if<S >= C>::type set(T const& x, T const& y, T const& z, T const& w) { m_data[0] = x; m_data[1] = y; m_data[2] = z; m_data[3] = w; }
		};

		template<typename T, size_t S>
		bool operator==(vector_basic<T, S> &v1, vector_basic<T, S> &v2) {
			for (size_t i = 0; i < S; i++)
				if (v1[i] != v2[i])
					return false;
			return true;
		}
		template<typename T, size_t S>
		bool operator!=(vector_basic<T, S> &v1, vector_basic<T, S> &v2) {
			return !(v1 == v2);
		}

		template<typename T, size_t S>
		vector_basic<T, S> const operator+(vector_basic<T, S> const& v1, vector_basic<T, S> const& v2) {
			vector_basic<T, S> res = v1;
			return res += v2;
		}
		template<typename T, size_t S>
		vector_basic<T, S> const operator-(vector_basic<T, S> const& v1, vector_basic<T, S> const& v2) {
			vector_basic<T, S> res = v1;
			return res -= v2;
		}
		template<typename T, size_t S>
		vector_basic<T, S> const operator*(vector_basic<T, S> const& v1, vector_basic<T, S> const& v2) {
			vector_basic<T, S> res = v1;
			return res *= v2;
		}
		template<typename T, size_t S>
		vector_basic<T, S> const operator*(vector_basic<T, S> const& v, T const& q) {
			vector_basic<T, S> res = v;
			return res *= q;
		}
		template<typename T, size_t S>
		vector_basic<T, S> const operator*(T const& q, vector_basic<T, S> const& v) {
			vector_basic<T, S> res = v;
			return res *= q;
		}
		template<typename T, size_t S>
		vector_basic<T, S> const operator/(vector_basic<T, S> const& v1, vector_basic<T, S> const& v2) {
			vector_basic<T, S> res = v1;
			return res /= v2;
		}
		template<typename T, size_t S>
		vector_basic<T, S> const operator/(vector_basic<T, S> const& v, T const& q) {
			vector_basic<T, S> res = v;
			return res /= q;
		}

		template<typename T, size_t S>
		T const operator%(vector_basic<T, S> const& v1, vector_basic<T, S> const& v2) {
			T res = T(0);
			for (int i = 0; i < S; i++)
				res += v1[i] * v2[i];
			return res;
		}
		template<typename T, size_t S>
		T const dot(vector_basic<T, S> const& v1, vector_basic<T, S> const& v2) {
			return v1 % v2;
		}

		template<typename T>
		vector_basic<T, 3> const operator^(vector_basic<T, 3> const& v1, vector_basic<T, 3> const& v2) {
			return vector_basic<T, 3>(v1[1] * v2[2] - v2[1] * v1[2],
									  v1[2] * v2[0] - v2[2] * v1[0],
									  v1[0] * v2[1] - v2[0] * v1[1]);
		}
		template<typename T>
		vector_basic<T, 3> const cross(vector_basic<T, 3> const& v1, vector_basic<T, 3> const& v2) {
			return v1 ^ v2;
		}

		template<typename T, size_t S>
		bool operator==(vector_basic<T, S> &v1, vector_homogeneous<T, S> &v2) {
			for (size_t i = 0; i < S; i++)
				if (v1[i] != v2[i])
					return false;
			return true;
		}
		template<typename T, size_t S>
		bool operator==(vector_homogeneous<T, S> &v1, vector_basic<T, S> &v2) {
			for (size_t i = 0; i < S; i++)
				if (v1[i] != v2[i])
					return false;
			return true;
		}
		template<typename T, size_t S>
		bool operator!=(vector_basic<T, S> &v1, vector_homogeneous<T, S> &v2) {
			return !(v1 == v2);
		}
		template<typename T, size_t S>
		bool operator!=(vector_homogeneous<T, S> &v1, vector_basic<T, S> &v2) {
			return !(v1 == v2);
		}

		template<typename T>
		vector_basic<T, 3> const operator^(vector_homogeneous<T, 3> const& v1, vector_basic<T, 3> const& v2) {
			return vector_basic<T, 3>(v1[1] * v2[2] - v2[1] * v1[2],
									  v1[2] * v2[0] - v2[2] * v1[0],
									  v1[0] * v2[1] - v2[0] * v1[1]);
		}
		template<typename T>
		vector_basic<T, 3> const cross(vector_homogeneous<T, 3> const& v1, vector_basic<T, 3> const& v2) {
			return v1 ^ v2;
		}
		template<typename T>
		vector_basic<T, 3> const operator^(vector_basic<T, 3> const& v1, vector_homogeneous<T, 3> const& v2) {
			return vector_basic<T, 3>(v1[1] * v2[2] - v2[1] * v1[2],
									  v1[2] * v2[0] - v2[2] * v1[0],
									  v1[0] * v2[1] - v2[0] * v1[1]);
		}
		template<typename T>
		vector_basic<T, 3> const cross(vector_basic<T, 3> const& v1, vector_homogeneous<T, 3> const& v2) {
			return v1 ^ v2;
		}

		using scalar = float;
		using vector2F = vector_basic<scalar, 2u>;
		using vector3F = vector_basic<scalar, 3u>;
		using vector4F = vector_basic<scalar, 4u>;
		using vector = vector3F;
		using vectorH = vector_homogeneous<scalar, 3u>;
	}
}