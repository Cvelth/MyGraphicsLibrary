#pragma once
#include "mgl/Math/vector.hpp"

#include "mgl/exceptions.hpp"
DefineNewMGLException(MatrixIndexOutOfBounds);

namespace mgl::math {
	template<typename T, size_t R, size_t C>
	class matrix_interface {
		using row_type = basic_vector<T, C>;
	public:
		virtual size_t size() const abstract;
		virtual T const* begin() const abstract;
		virtual T* begin() abstract;
		virtual T const* end() const abstract;
		virtual T* end() abstract;

		virtual row_type const& operator[](size_t r) const abstract;
		virtual row_type const& row(size_t r) const {
			return operator[](r);
		}
		virtual row_type& operator[](size_t r) abstract;
		virtual row_type& row(size_t r) {
			return operator[](r);
		}

		virtual T const& operator()(size_t r, size_t c) const abstract;
		T const& at(size_t r, size_t c) const {
			return operator()(r, c);
		}
		virtual T& operator()(size_t r, size_t c) abstract;
		T& at(size_t r, size_t c) {
			return operator()(r, c);
		}
	};

	template<typename T, size_t R, size_t C>
	class basic_matrix : public basic_vector<basic_vector<T, C>, R>, public matrix_interface<T, R, C> {
		using row_type = basic_vector<T, C>;
		using base_type = basic_vector<row_type, R>;
	protected:
		using base_type::data;
	protected:
		template <typename... Tail>
		void set_values(size_t r, size_t c) {}
		template <typename... Tail>
		void set_values(size_t r, size_t c, typename std::enable_if<sizeof...(Tail) + 1 <= R * C, T>::type const& head, Tail ...tail) {
			data[r][c] = head;
			if (++c == C) {
				++r;
				c = 0u;
			}
			set_values(r, c, T(tail)...);
		}

		template <typename... Tail>
		void set_rows(size_t r) {}
		template <typename... Tail>
		void set_rows(size_t r, typename std::enable_if<sizeof...(Tail) + 1 <= R, row_type>::type const& head, Tail ...tail) {
			data[r] = head;
			set_rows(++r, row_type(tail)...);
		}
	public:
		basic_matrix(basic_matrix<T, C, R> const& other) {
			std::copy(other.begin(), other.end(), data);
		}
		basic_matrix(basic_matrix<T, C, R>&& other) {
			std::move(other.begin(), other.end(), data);
		}
		template <typename... Tail>
		basic_matrix(typename std::enable_if<sizeof...(Tail) + 1 <= R * C, T>::type const& head = T(0), Tail... tail) {
			set_values(0, 0, head, tail...);
		}
		template <typename... Tail>
		basic_matrix(typename std::enable_if<sizeof...(Tail) + 1 <= R, row_type>::type const& head = row_type(0), Tail... tail) {
			set_rows(0, head, tail...);
		}
		basic_matrix(std::initializer_list<std::initializer_list<T>> const& list) {
			size_t r = 0;
			for (auto &it : list)
				data[r++] = row_type(it);
		}
		basic_matrix(std::initializer_list<std::initializer_list<T>> &&list) {
			size_t r = 0;
			for (auto &it : list)
				data[r++] = row_type(it);
		}
		basic_matrix(std::initializer_list<T> const& list) {
			size_t r = 0, c = 0;
			for (auto &it : list) {
				data[r][c] = it;
				if (++c == C) {
					++r;
					c = 0;
				}
			}
		}
		basic_matrix(std::initializer_list<T> &&list) {
			size_t r = 0, c = 0;
			for (auto &it : list) {
				data[r][c] = it;
				if (++c == C) {
					++r;
					c = 0;
				}
			}
		}

		template<typename T_O, size_t R_O, size_t C_O, typename = typename std::enable_if<std::is_convertible<T_O, T>::value>::type>
		basic_matrix(matrix_interface<T_O, R_O, C_O> const& other, typename std::enable_if<(R_O <= R && C_O <= C), void*>::type less = nullptr) {
			for (int r = 0; r < R_O; r++)
				data[r] = other[r];
			for (int r = R_O; r < R; r++)
				data[r].clear();
		}
		template<typename T_O, size_t R_O, size_t C_O, typename = typename std::enable_if<std::is_convertible<T_O, T>::value>::type>
		basic_matrix(matrix_interface<T_O, R_O, C_O> &&other, typename std::enable_if<(R_O <= R && C_O <= C), void*>::type less = nullptr) {
			for (int r = 0; r < R_O; r++)
				data[r] = other[r];
			for (int r = R_O; r < R; r++)
				data[r].clear();
		}
		template<typename T_O, size_t R_O, size_t C_O, typename = typename std::enable_if<std::is_convertible<T_O, T>::value>::type>
		explicit basic_matrix(matrix_interface<T_O, R_O, C_O> const& other, typename std::enable_if<(R_O > R || C_O > C), void*>::type more = nullptr) {
			for (int r = 0; r < std::min(R, R_O); r++)
				data[r] = row_type(other[r]);
		}
		template<typename T_O, size_t R_O, size_t C_O, typename = typename std::enable_if<std::is_convertible<T_O, T>::value>::type>
		explicit basic_matrix(matrix_interface<T_O, R_O, C_O> &&other, typename std::enable_if<(R_O > R || C_O > C), void*>::type more = nullptr) {
			for (int r = 0; r < std::min(R, R_O); r++)
				data[r] = row_type(other[r]);
		}
		basic_matrix<T, C, R> const& operator=(basic_matrix<T, C, R> const& other) {
			std::copy(other.begin(), other.end(), data);
			return *this;
		}
		basic_matrix<T, C, R> const& operator=(basic_matrix<T, C, R> &&other) {
			std::move(other.begin(), other.end(), data);
			return *this;
		}

		virtual size_t size() const override {
			return C * R;
		}
		virtual T const* begin() const override {
			return base_type::begin()->begin();
		}
		virtual T* begin() override {
			return base_type::begin()->begin();
		}
		virtual T const* end() const override {
			return base_type::end()->begin();
		}
		virtual T* end() override {
			return base_type::end()->begin();
		}

		virtual T const& operator()(size_t r, size_t c) const override {
			if (r >= R || c >= C)
				throw Exceptions::MatrixIndexOutOfBounds();
			return data[r][c];
		}
		virtual T& operator()(size_t r, size_t c) override {
			if (r >= R || c >= C)
				throw Exceptions::MatrixIndexOutOfBounds();
			return data[r][c];
		}
		virtual row_type const& operator[](size_t r) const override {
			if (r >= R)
				throw Exceptions::MatrixIndexOutOfBounds();
			return base_type::operator[](r);
		}
		virtual row_type& operator[](size_t r) override {
			if (r >= R)
				throw Exceptions::MatrixIndexOutOfBounds();
			return base_type::operator[](r);
		}
	};
}