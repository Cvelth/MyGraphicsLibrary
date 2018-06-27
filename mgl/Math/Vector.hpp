#pragma once
#include "../MyGraphicsLibrary/MGL/SharedHeaders/Exceptions.hpp"
DefineNewMglException(VectorException)
#include <algorithm>
#include <initializer_list>

namespace mgl {
	namespace math {
		template<typename T, size_t S>
		class vector_basic {
		protected:
			T data[S];
		public:
			vector_basic(vector_basic<T, S> const& other) {
				std::copy(other.begin(), other.end(), data);
			}
			vector_basic(vector_basic<T, S>&& other) {
				std::move(other.begin(), other.end(), data);
			}
			template <typename... Tail>
			vector_basic(typename std::enable_if<sizeof...(Tail) + 1 <= S, T>::type head = T(0), 
					Tail... tail) : data{head, T(tail)...} {}
			template<size_t S_O>
			vector_basic(vector_basic<T, S_O> const& other, typename std::enable_if<S_O < S>::type* size = 0) {
				std::copy(other.begin(), other.end(), data);
				std::fill(data + S_O, data + S, T(0));
			}
			template<size_t S_O>
			vector_basic(vector_basic<T, S_O>&& other, typename std::enable_if<S_O < S>::type* size = 0) {
				std::move(other.begin(), other.end(), data);
				std::fill(data + S_O, data + S, T(0));
			}
			vector_basic(std::initializer_list<T> const& inputs) {
				if (inputs.size() > S)
					throw Exceptions::VectorException("Too many inputs.");
				std::copy(inputs.begin(), inputs.end(), data);
				std::fill(data + inputs.size(), data + S, T(0));
			}
			vector_basic(std::initializer_list<T>&& inputs) {
				if (inputs.size() > S)
					throw Exceptions::VectorException("Too many inputs.");
				std::move(inputs.begin(), inputs.end(), data);
				std::fill(data + inputs.size(), data + S, T(0));
			}

			vector_basic<T, S> const& operator=(vector_basic<T, S> const& other) {
				std::copy(other.begin(), other.end(), data);
				return *this;
			}
			vector_basic<T, S> const& operator=(vector_basic<T, S>&& other) {
				std::move(other.begin(), other.end(), data);
				return *this;
			}

			T const& operator[](size_t index) const {
				if (index >= S)
					throw Exceptions::VectorException("There is no element with this index in the vector");
				return data[index];
			}
			T& operator[](size_t index) {
				if (index >= S)
					throw Exceptions::VectorException("There is no element with this index in the vector");
				return data[index];
			}
			T const& at(size_t index) const {
				return operator[](index);
			}
			T& at(size_t index) {
				return operator[](index);
			}

			bool isNull() const {
				for (size_t i = 0; i < S; i++)
					if (data[i] != T(0))
						return false;
				return true;
			}
			float length() const {
				T sum = T(0);
				for (size_t i = 0; i < S; i++)
					sum += data[i] * data[i];
				return std::sqrtf(sum);
			}
			void normalize() {
				auto l = length();
				for (size_t i = 0; i < S; i++)
					data[i] /= l;
			}
			vector_basic<T, S> const normalized() const {
				vector_basic<T, S> ret(*this);
				ret.normalize();
				return ret;
			}

			T const* begin() const {
				return data;
			}
			T const* end() const{
				return data + S;
			}

			vector_basic<T, S> const& operator+=(vector_basic<T, S> const& other) {
				for (size_t i = 0; i < S; i++)
					data[i] += other.data[i];
				return *this;
			}
			vector_basic<T, S> const& operator-=(vector_basic<T, S> const& other) {
				for (size_t i = 0; i < S; i++)
					data[i] -= other.data[i];
				return *this;
			}
			vector_basic<T, S> const& operator*=(vector_basic<T, S> const& other) {
				for (size_t i = 0; i < S; i++)
					data[i] *= other.data[i];
				return *this;
			}
			vector_basic<T, S> const& operator/=(vector_basic<T, S> const& other) {
				for (size_t i = 0; i < S; i++)
					data[i] /= other.data[i];
				return *this;
			}
			vector_basic<T, S> const& operator*=(T const& q) {
				for (size_t i = 0; i < S; i++)
					data[i] *= q;
				return *this;
			}
			vector_basic<T, S> const& operator/=(T const& q) {
				for (size_t i = 0; i < S; i++)
					data[i] /= q;
				return *this;
			}

			vector_basic<T, S> const operator-() const {
				vector_basic<T, S> res;
				for (size_t i = 0; i < S; i++)
					res.data[i] = -data[i];
				return res;
			}
		};
		template<typename T, size_t S>
		class vector_homogeneous : public vector_basic<T, S + 1> {
		public:
			template<typename... Tail>
			vector_homogeneous(typename std::enable_if<sizeof...(Tail) + 1 <= S, T>::type head = T(0), 
							   Tail... tail) : vector_basic<T, S + 1>(head, tail...) { data[S] = T(1); }
			template<typename... Tail>
			vector_homogeneous(typename std::enable_if<sizeof...(Tail) == S, T>::type head = T(0),
							   Tail... tail) : vector_basic<T, S + 1>(head, tail...) {}
			template<size_t S_O>
			vector_homogeneous(vector_basic<T, S_O> const& other, typename std::enable_if<S_O < S + 1>::type* size = 0)
				: vector_basic<T, S + 1>::vector_basic(other) { data[S] = T(1); }
			template<size_t S_O>
			vector_homogeneous(vector_basic<T, S_O>&& other, typename std::enable_if<S_O < S + 1>::type* size = 0)
				: vector_basic<T, S + 1>::vector_basic(other) { data[S] = T(1); }
			vector_homogeneous(T* inputs) : vector_basic(inputs) { data[S] = T(1); }
			vector_homogeneous(std::initializer_list<T> const& inputs) : vector_basic(inputs) {
				data[S] = T(1);
			}
			vector_homogeneous(std::initializer_list<T>&& inputs) : vector_basic(inputs) {
				data[S] = T(1);
			}


			template<size_t C = 0> typename std::enable_if<S >= C, T>::type const& x() const { return data[0]; }
			template<size_t C = 1> typename std::enable_if<S >= C, T>::type const& y() const { return data[1]; }
			template<size_t C = 2> typename std::enable_if<S >= C, T>::type const& z() const { return data[2]; }
			template<size_t C = 3> typename std::enable_if<S >= C, T>::type const& w() const { return data[3]; }
			template<size_t C = 0> typename std::enable_if<S >= C>::type x(T const& value) { data[0] = value; }
			template<size_t C = 1> typename std::enable_if<S >= C>::type y(T const& value) { data[1] = value; }
			template<size_t C = 2> typename std::enable_if<S >= C>::type z(T const& value) { data[2] = value; }
			template<size_t C = 3> typename std::enable_if<S >= C>::type w(T const& value) { data[3] = value; }
			template<size_t C = 0> typename std::enable_if<S >= C>::type set(T const& x) { data[0] = x; }
			template<size_t C = 1> typename std::enable_if<S >= C>::type set(T const& x, T const& y) { data[0] = x; data[1] = y; }
			template<size_t C = 2> typename std::enable_if<S >= C>::type set(T const& x, T const& y, T const& z) { data[0] = x; data[1] = y; data[2] = z; }
			template<size_t C = 3> typename std::enable_if<S >= C>::type set(T const& x, T const& y, T const& z, T const& w) { data[0] = x; data[1] = y; data[2] = z; data[3] = w; }
		};

		template<typename T, size_t S>
		bool operator==(vector_basic<T, S> const& v1, vector_basic<T, S> const& v2) {
			for (size_t i = 0; i < S; i++)
				if (v1[i] != v2[i])
					return false;
			return true;
		}
		template<typename T, size_t S>
		bool operator!=(vector_basic<T, S> const& v1, vector_basic<T, S> const& v2) {
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

		template<typename T, size_t S>
		T const operator%(vector_basic<T, S> const& v1, vector_homogeneous<T, S> const& v2) {
			T res = T(0);
			for (int i = 0; i < S; i++)
				res += v1[i] * v2[i];
			return res;
		}
		template<typename T, size_t S>
		T const dot(vector_basic<T, S> const& v1, vector_homogeneous<T, S> const& v2) {
			return v1 % v2;
		}

		template<typename T, size_t S>
		T const operator%(vector_homogeneous<T, S> const& v1, vector_basic<T, S> const& v2) {
			T res = T(0);
			for (int i = 0; i < S; i++)
				res += v1[i] * v2[i];
			return res;
		}
		template<typename T, size_t S>
		T const dot(vector_homogeneous<T, S> const& v1, vector_basic<T, S> const& v2) {
			return v1 % v2;
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
		class vector2F : public vector_basic<scalar, 2u> { public: using vector_basic::vector_basic; };
		class vector3F : public vector_basic<scalar, 3u> { public: using vector_basic::vector_basic; };
		class vector4F : public vector_basic<scalar, 4u> { public: using vector_basic::vector_basic; };
		class vector : public vector3F { public: using vector3F::vector3F; };
		class vectorH : public vector_homogeneous<scalar, 3u> { public: using vector_homogeneous::vector_homogeneous; };
	}
}