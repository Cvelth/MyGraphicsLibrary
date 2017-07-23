#pragma once
#include <list>
#include "SharedHeaders\Exceptions.hpp"
#include "OpenGL_Mirror\EnumsMirror\EnumsMirror.hpp"

namespace mgl {
	class Buffer;
	class Color;
	namespace math {
		class Vector;
		class Matrix;
	}

	namespace Exceptions {
		class PrimitiveException : public AbstractStringException {
			using AbstractStringException::AbstractStringException;
		};
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

	class Primitive {
	protected:
		std::list<Vertex*> m_data;
		Buffer* m_buffer;
		VertexConnectionType m_connection;
		Color* m_basic_color;
	public:
		Primitive(Color* basicColor, VertexConnectionType type = VertexConnectionType::Points);
		Primitive(Color* basicColor, VertexConnectionType type, const float* array, size_t size, size_t COORDS_POINT_NUMBER = 3, size_t COLOR_POINT_NUMBER = 3);
		Primitive(Color* basicColor, VertexConnectionType type, math::Vector* coords_array, size_t size);
		Primitive(Color* basicColor, VertexConnectionType type, math::Vector* coords_array, Color* colors_array, size_t size);
		Primitive(Color* basicColor, VertexConnectionType type, const std::initializer_list<math::Vector*>& coords_list);
		Primitive(Color* basicColor, VertexConnectionType type, const std::initializer_list<math::Vector*>& coords_list, const std::initializer_list<Color*>& color_list);
		Primitive(Color* basicColor, VertexConnectionType type, const std::list<math::Vector*>& coords_list);
		Primitive(Color* basicColor, VertexConnectionType type, const std::list<math::Vector*>& coords_list, const std::list<Color*>& color_list);
		~Primitive();
		
		virtual size_t getSize() const;
		virtual size_t getNumber() const;
		
		virtual void insert(math::Vector* v);
		virtual void insert(math::Vector* v, Color* c);
		virtual void send(DataUsage u);
		virtual void draw();
		virtual void clean();
		
		std::list<Vertex*>& operator*();
		const std::list<Vertex*>& operator*() const;
	};
}