#pragma once
namespace mgl {
	class Color;
	namespace math {
		class vectorH;
	}

	class Vertex {
		math::vectorH* m_coords;
		Color* m_color;
	public:
		Vertex(math::vectorH const& coords, Color const& color);
		Vertex(math::vectorH&& coords, Color&& color);
		~Vertex();
		void set(math::vectorH const& coords, Color const& color);
		void set(math::vectorH&& coords, Color&& color);
		inline math::vectorH* coords() {
			return m_coords;
		}
		inline const math::vectorH* coords() const {
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