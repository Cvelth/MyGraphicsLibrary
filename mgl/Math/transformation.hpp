#pragma once
#include "matrix.hpp"

namespace mgl::math {
	template <typename T, size_t S>
	class basic_transformation : public basic_matrix<T, S + 1, S + 1> {
	protected:
		using basic_matrix<T, S + 1, S + 1>::data;
	public:
		using basic_matrix<T, S + 1, S + 1>::basic_matrix;
	};

	class transformation2f : public basic_transformation<float, 2u> { public: using basic_transformation::basic_transformation; };
	class transformation3f : public basic_transformation<float, 3u> { public: using basic_transformation::basic_transformation; };
	class transformation2d : public basic_transformation<double, 2u> { public: using basic_transformation::basic_transformation; };
	class transformation3d : public basic_transformation<double, 3u> { public: using basic_transformation::basic_transformation; };

	class transformation : public transformation3f { public: using transformation3f::transformation3f; };

	transformation translation(vector const& direction);
	transformation rotation(vector::value_type const& angle, vector const& axis);
	transformation scaling(vector const& direction);
	transformation orthographic_projection(basic_vector<vector2f, 3> const& edges);
	transformation perspective_projection(basic_vector<vector2f, 3> const& edges);

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