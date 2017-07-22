#pragma once
#include "Math\Vector.hpp"

namespace mgl {
	class Color : protected math::Vector {
	public:
		Color(float r = 0.f, float g = 0.f, float b = 0.f, float a = 1.f);
		Color(size_t r, size_t g, size_t b, size_t a = 255, size_t MAXIMUM_VALUE = 255);

		float r() const;
		float g() const;
		float b() const;
		float a() const;
		void r(float value);
		void g(float value);
		void b(float value);
		void a(float value);
		void r(size_t value, size_t MAXIMUM_VALUE = 255);
		void g(size_t value, size_t MAXIMUM_VALUE = 255);
		void b(size_t value, size_t MAXIMUM_VALUE = 255);
		void a(size_t value, size_t MAXIMUM_VALUE = 255);
	};
}