#pragma once
#include "matrix.hpp"

namespace mgl::math {
	template <typename T, size_t S>
	class basic_transformation : public basic_matrix<T, S + 1, S + 1> {
	protected:
		using basic_matrix<T, S + 1, S + 1>::data;
	public:
		using basic_matrix<T, S + 1, S + 1>::basic_matrix;

		template <typename T_O, typename = typename std::enable_if<std::is_convertible<T_O, T>::value>::type>
		basic_transformation<T, S> translate(basic_vector<T_O, S> const& direction) {
			for (size_t r = 0; r < S + 1; r++)
				data[r][S] += dot(data[r], direction);
			return *this;
		}
		template <typename T_O, typename = typename std::enable_if<std::is_convertible<T_O, T>::value>::type>
		basic_transformation<T, S> scale(basic_vector<T_O, S> const& direction) {
			for (size_t r = 0; r < S + 1; r++)
				data[r] *= direction;
			return *this;
		}
	};

	class transformation2f : public basic_transformation<float, 2u> { public: using basic_transformation::basic_transformation; };
	class transformation3f : public basic_transformation<float, 3u> { public: using basic_transformation::basic_transformation; };
	class transformation2d : public basic_transformation<double, 2u> { public: using basic_transformation::basic_transformation; };
	class transformation3d : public basic_transformation<double, 3u> { public: using basic_transformation::basic_transformation; };

	class transformation : public transformation3f { public: using transformation3f::transformation3f; };

	transformation translation(vector const& direction) { 
		transformation ret;
		return ret.translate(direction); 
	}
	transformation rotation(vector::value_type const& angle, vector const& axis) { return transformation(); }
	transformation scaling(vector const& direction) {
		transformation ret;
		return ret.scale(direction);
	}
	transformation orthographic_projection(basic_vector<vector2f, 3> const& edges) { return transformation(); }
	transformation perspective_projection(basic_vector<vector2f, 3> const& edges) { return transformation(); }

	transformation translation(float x, float y, float z) { return translation({x,y,z}); }
	transformation rotation(vector::value_type const& angle, float x, float y, float z) { return rotation(angle, {x,y,z}); }
	transformation scaling(float x, float y, float z) { return scaling({x,y,z}); }
	transformation orthographic_projection(float left, float right, float bottom, float top, float near, float far) {
		return orthographic_projection({{left, right}, {bottom, top}, {near, far}});
	}
	transformation perspective_projection(float left, float right, float bottom, float top, float near, float far) {
		return orthographic_projection({{left, right},{bottom, top},{near, far}});
	}
}