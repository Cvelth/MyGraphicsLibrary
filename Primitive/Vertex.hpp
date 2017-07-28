#pragma once
namespace mgl {
	class Color;
	namespace math {
		class Vector;
	}

	class Vertex {
		math::Vector* m_coords;
		Color* m_color;
	public:
		Vertex(math::Vector* coords, Color* color);
		~Vertex();
		void set(math::Vector* coords, Color* color);
		inline math::Vector* coords() {
			return m_coords;
		}
		inline const math::Vector* coords() const {
			return m_coords;
		}
		inline Color* color() {
			return m_color;
		}
		inline const Color* color() const {
			return m_color;
		}
	};
}