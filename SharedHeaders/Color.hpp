#pragma once
#include "MGL\SharedHeaders\Exceptions.hpp"
DefineNewMglException(ColorException);
namespace mgl {
	class Color {
		float m_data[4];
	public:
		Color(float r = 0.f, float g = 0.f, float b = 0.f, float a = 1.f) {
			set(r, g, b, a);
		}
		Color(unsigned r, unsigned g, unsigned b, unsigned a = 255, unsigned MAXIMUM_VALUE = 255) {
			set(float(r) / MAXIMUM_VALUE, float(g) / MAXIMUM_VALUE, float(b) / MAXIMUM_VALUE, float(a) / MAXIMUM_VALUE);
		}
		Color(signed r, signed g, signed b, signed a = 255, int MAXIMUM_VALUE = 255) {
			if (r < 0 || g < 0 || b < 0 || a < 0)
				throw Exceptions::ColorException("Unsupportable Color Data was passed.");
			set(float(r) / MAXIMUM_VALUE, float(g) / MAXIMUM_VALUE, float(b) / MAXIMUM_VALUE, float(a) / MAXIMUM_VALUE);
		}

		inline void set(float r, float g, float b, float a) {
			m_data[0] = r;
			m_data[1] = g;
			m_data[2] = b;
			m_data[3] = a;
		}

		inline float r() const { return m_data[0]; }
		inline float g() const { return m_data[1]; }
		inline float b() const { return m_data[2]; }
		inline float a() const { return m_data[3]; }
		inline void r(float value) { m_data[0] = value; }
		inline void g(float value) { m_data[1] = value; }
		inline void b(float value) { m_data[2] = value; }
		inline void a(float value) { m_data[3] = value; }
		inline void r(size_t value, size_t MAXIMUM_VALUE = 255) { m_data[0] = float(value) / MAXIMUM_VALUE; }
		inline void g(size_t value, size_t MAXIMUM_VALUE = 255) { m_data[1] = float(value) / MAXIMUM_VALUE; }
		inline void b(size_t value, size_t MAXIMUM_VALUE = 255) { m_data[2] = float(value) / MAXIMUM_VALUE; }
		inline void a(size_t value, size_t MAXIMUM_VALUE = 255) { m_data[3] = float(value) / MAXIMUM_VALUE; }
	};
}