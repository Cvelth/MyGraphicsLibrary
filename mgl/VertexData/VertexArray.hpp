#pragma once
#include <cstdint>
#include <list>
namespace mgl {
	enum class VertexConnectionType {
		Points, Lines, LineStrip, LineLoop, Triangles, TriangleStrip, TriangleFan, Quads, QuadStrip, Polygon
	};
	class GlobalStateController;
	class ShaderVariable;

	class MultiVertexArray {
		friend GlobalStateController;
	private:
		size_t const m_number;
		uint32_t *m_ids;
	protected:
		MultiVertexArray(size_t number, uint32_t *ids);
	public:
		MultiVertexArray(size_t number);
		virtual ~MultiVertexArray();

		void bind(size_t index);
		void attrib_pointer(size_t index, ShaderVariable const& variable, size_t stride, size_t shift);
		void attrib_pointer(size_t index, std::list<ShaderVariable> const& variables);

		void draw(size_t index, VertexConnectionType connection, size_t first, size_t count);

		MultiVertexArray(MultiVertexArray const& other) = delete;
		MultiVertexArray(MultiVertexArray &&other) : MultiVertexArray(other.m_number, other.m_ids) {}
	};

	class VertexArray : private MultiVertexArray {
		friend GlobalStateController;
	private:
		uint32_t m_id;
	protected:
		VertexArray(uint32_t id) : MultiVertexArray(1, &id) {}
	public:
		VertexArray() : MultiVertexArray(1) {}
		virtual ~VertexArray() {}

		void bind() { MultiVertexArray::bind(0); }
		void attrib_pointer(ShaderVariable const& variable, size_t stride, size_t shift) {
			MultiVertexArray::attrib_pointer(0, variable, stride, shift);
		}
		void attrib_pointer(std::list<ShaderVariable> const& variables) {
			MultiVertexArray::attrib_pointer(0, variables);
		}

		void draw(VertexConnectionType connection, size_t first, size_t count) {
			MultiVertexArray::draw(0, connection, first, count);
		}

		VertexArray(VertexArray &&other) : MultiVertexArray(std::move(other)) {}
	};
}

#include "mgl/exceptions.hpp"
DefineNewMGLException(VertexArrayCreationError)
DefineNewMGLException(MultiVertexArrayIndexOutOfBounds)