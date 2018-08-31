#pragma once
#include <cstdint>
#include <list>
namespace mgl {
	enum class VertexConnectionType {
		Points, Lines, LineStrip, LineLoop, Triangles, TriangleStrip, TriangleFan, Quads, QuadStrip, Polygon
	};
	enum class DrawIndexType {
		OneByte = 1, TwoByte = 2, FourByte = 4
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

		void draw(size_t index, VertexConnectionType connection, size_t count, size_t first = 0);
		void draw_indexed(size_t index, VertexConnectionType connection, size_t count, size_t first = 0, int base_vertex = 0, DrawIndexType type = DrawIndexType::TwoByte);
		void draw_indexed(size_t index, VertexConnectionType connection, size_t start, size_t end, size_t count, size_t first = 0, int base_vertex = 0, DrawIndexType type = DrawIndexType::TwoByte);
		void draw_indirect(size_t index, VertexConnectionType connection, size_t byte_offset = 0);
		void draw_indexed_indirect(size_t index, VertexConnectionType connection, DrawIndexType type = DrawIndexType::TwoByte, size_t byte_offset = 0);
		void draw_multiple(size_t index, VertexConnectionType connection, size_t drawcount, int const* counts, int const* firsts);
		void draw_multiple_indexed(size_t index, VertexConnectionType connection, size_t drawcount, int const* counts, int const* byte_offsets, DrawIndexType type = DrawIndexType::TwoByte);
		void draw_multiple_indexed(size_t index, VertexConnectionType connection, size_t drawcount, int const* counts, int const* byte_offsets, int const* base_vertices, DrawIndexType type = DrawIndexType::TwoByte);
		void draw_multiple_indirect(size_t index, VertexConnectionType connection, size_t drawcount, size_t byte_offset = 0, size_t stride = 0);
		void draw_multiple_indexed_indirect(size_t index, VertexConnectionType connection, size_t drawcount, DrawIndexType type = DrawIndexType::TwoByte, size_t byte_offset = 0, size_t stride = 0);

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

		void draw(VertexConnectionType connection, size_t count, size_t first) {
			MultiVertexArray::draw(0, connection, count, first);
		}
		void draw_indexed(VertexConnectionType connection, size_t count, size_t first = 0, int base_vertex = 0, DrawIndexType type = DrawIndexType::TwoByte) {
			MultiVertexArray::draw_indexed(0, connection, count, first, base_vertex, type);
		}
		void draw_indexed(VertexConnectionType connection, size_t start, size_t end, size_t count, size_t first = 0, int base_vertex = 0, DrawIndexType type = DrawIndexType::TwoByte) {
			MultiVertexArray::draw_indexed(0, connection, start, end, count, first, base_vertex, type);
		}
		void draw_indirect(VertexConnectionType connection, size_t byte_offset = 0) {
			MultiVertexArray::draw_indirect(0, connection, byte_offset);
		}
		void draw_indexed_indirect(VertexConnectionType connection, DrawIndexType type = DrawIndexType::TwoByte, size_t byte_offset = 0) {
			MultiVertexArray::draw_indexed_indirect(0, connection, type, byte_offset);
		}
		void draw_multiple(VertexConnectionType connection, size_t drawcount, int const* count, int const* first) {
			MultiVertexArray::draw_multiple(0, connection, drawcount, count, first);
		}
		void draw_multiple_indexed(VertexConnectionType connection, size_t drawcount, int const* counts, int const* byte_offsets, DrawIndexType type = DrawIndexType::TwoByte) {
			MultiVertexArray::draw_multiple_indexed(0, connection, drawcount, counts, byte_offsets, type);
		}
		void draw_multiple_indexed(VertexConnectionType connection, size_t drawcount, int const* counts, int const* byte_offsets, int const* base_vertices, DrawIndexType type = DrawIndexType::TwoByte){
			MultiVertexArray::draw_multiple_indexed(0, connection, drawcount, counts, byte_offsets, base_vertices, type);
		}
		void draw_multiple_indirect(size_t index, VertexConnectionType connection, size_t drawcount, size_t byte_offset = 0, size_t stride = 0) {
			MultiVertexArray::draw_multiple_indirect(0, connection, drawcount, byte_offset, stride);
		}
		void draw_multiple_indexed_indirect(size_t index, VertexConnectionType connection, size_t drawcount, DrawIndexType type = DrawIndexType::TwoByte, size_t byte_offset = 0, size_t stride = 0) {
			MultiVertexArray::draw_multiple_indexed_indirect(0, connection, drawcount, type, byte_offset, stride);
		}

		VertexArray(VertexArray &&other) : MultiVertexArray(std::move(other)) {}
	};
}

#include "mgl/exceptions.hpp"
DefineNewMGLException(VertexArrayCreationError)
DefineNewMGLException(MultiVertexArrayIndexOutOfBounds)
DefineNewMGLException(AttribPointerError)