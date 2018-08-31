#include "mgl/dependencies/OpenGL_Dependency/opengl_dependency.hpp"
#include "VertexArray.hpp"
mgl::MultiVertexArray::MultiVertexArray(size_t number, uint32_t *ids) : m_number(number) {
	m_ids = new uint32_t[number];
	std::copy(ids, ids + number, m_ids);
	for (size_t i = 0; i < number; i++)
		if (m_ids[i] == 0 || !glIsVertexArray(m_ids[i]))
			throw Exceptions::VertexArrayCreationError();
}
mgl::MultiVertexArray::MultiVertexArray(size_t number) : m_number(number) {
	m_ids = new uint32_t[number];
	glGenVertexArrays(GLsizei(number), m_ids);
}
mgl::MultiVertexArray::~MultiVertexArray() {
	if (m_number) delete[] m_ids;
}

#include "mgl/EnumConverter/enum_converter.hpp"
#include "mgl/GlobalStateController/GlobalStateController.hpp"
#include "mgl/ShaderProgram/ShaderVariable.hpp"
#include "Buffer.hpp"
void mgl::MultiVertexArray::bind(size_t index) {
	if (index >= m_number) throw Exceptions::MultiVertexArrayIndexOutOfBounds();
	GlobalStateController::bind_vertex_array(this, index);
}
void mgl::MultiVertexArray::attrib_pointer(size_t index, ShaderVariable const& variable, size_t stride, size_t shift) {
	if (GlobalStateController::bound_buffer(mgl::BufferBindingPoint::ArrayBuffer).first == nullptr)
		throw Exceptions::AttribPointerError("attrib_pointer cannot be called without a buffer with vertex data being bound to BufferBindingPoint::ArrayBuffer.");
	bind(index);
	auto type = enum_converter::convert_variable_type(variable.data_type);
	glVertexAttribPointer(variable.location, GLint(enum_converter::convert_to_number(type.second)), 
						  GLsizei(enum_converter::convert(type.first)), GL_FALSE, GLsizei(stride), (const void*) shift);
	glEnableVertexAttribArray(variable.location);
}
namespace mgl {
	size_t count_size(std::list<ShaderVariable> const& variables) {
		size_t ret = 0u;
		for (auto &it : variables) {
			auto type = enum_converter::convert_variable_type(it.data_type);
			ret += enum_converter::get_size(type.first) * enum_converter::convert_to_number(type.second);
		}
		return ret;
	}
}
void mgl::MultiVertexArray::attrib_pointer(size_t index, std::list<ShaderVariable> const& variables) {
	size_t stride = count_size(variables);
	size_t shift = 0u;
	for (auto &it : variables) {
		attrib_pointer(index, it, stride, shift);
		shift += enum_converter::get_size(enum_converter::convert_variable_type(it.data_type).first);
	}
}

void mgl::MultiVertexArray::draw(size_t index, VertexConnectionType connection, size_t first, size_t count) {
	bind(index);
	glDrawArrays(enum_converter::convert(connection), GLint(first), GLsizei(count));
}
void mgl::MultiVertexArray::draw_indexed(size_t index, VertexConnectionType connection, size_t count, size_t first, int base_vertex, DrawIndexType type) {
	if (GlobalStateController::bound_buffer(mgl::BufferBindingPoint::ElementArrayBuffer).first == nullptr)
		throw Exceptions::AttribPointerError("Indexed draw is impossible without a buffer with index data being bound to BufferBindingPoint::ElementArrayBuffer.");
	bind(index);
	if (base_vertex)
		glDrawElementsBaseVertex(enum_converter::convert(connection), GLsizei(count), enum_converter::convert(type), (void*) (first * size_t(type)), GLint(base_vertex));
	else
		glDrawElements(enum_converter::convert(connection), GLsizei(count), enum_converter::convert(type), (void*) (first * size_t(type)));
}
void mgl::MultiVertexArray::draw_indexed(size_t index, VertexConnectionType connection, size_t start, size_t end, size_t count, size_t first, int base_vertex, DrawIndexType type) {
	if (GlobalStateController::bound_buffer(mgl::BufferBindingPoint::ElementArrayBuffer).first == nullptr)
		throw Exceptions::AttribPointerError("Indexed draw is impossible without a buffer with index data being bound to BufferBindingPoint::ElementArrayBuffer.");
	bind(index);
	if (base_vertex)
		glDrawRangeElementsBaseVertex(enum_converter::convert(connection), GLuint(start), GLuint(end), GLsizei(count), enum_converter::convert(type), (void*) (first * size_t(type)), GLint(base_vertex));
	else
		glDrawRangeElements(enum_converter::convert(connection), GLuint(start), GLuint(end), GLsizei(count), enum_converter::convert(type), (void*) (first * size_t(type)));
}
void mgl::MultiVertexArray::draw_indirect(size_t index, VertexConnectionType connection, size_t byte_offset) {
	if (GlobalStateController::bound_buffer(mgl::BufferBindingPoint::DrawIndirectBuffer).first == nullptr)
		throw Exceptions::AttribPointerError("Indirect draw is impossible without a buffer with draw data being bound to BufferBindingPoint::DrawIndirectBuffer.");
	bind(index);
	glDrawArraysIndirect(enum_converter::convert(connection), (void*) (byte_offset));
}
void mgl::MultiVertexArray::draw_indexed_indirect(size_t index, VertexConnectionType connection, DrawIndexType type, size_t byte_offset) {
	if (GlobalStateController::bound_buffer(mgl::BufferBindingPoint::ElementArrayBuffer).first == nullptr)
		throw Exceptions::AttribPointerError("Indexed draw is impossible without a buffer with index data being bound to BufferBindingPoint::ElementArrayBuffer.");
	if (GlobalStateController::bound_buffer(mgl::BufferBindingPoint::DrawIndirectBuffer).first == nullptr)
		throw Exceptions::AttribPointerError("Indirect draw is impossible without a buffer with draw data being bound to BufferBindingPoint::DrawIndirectBuffer.");
	bind(index);
	glDrawElementsIndirect(enum_converter::convert(connection), enum_converter::convert(type), (void*) (byte_offset));
}
void mgl::MultiVertexArray::draw_multiple(size_t index, VertexConnectionType connection, size_t drawcount, int const* counts, int const* firsts) {
	bind(index);
	glMultiDrawArrays(enum_converter::convert(connection), (GLint const*) firsts, (GLint const*) counts, GLsizei(drawcount));
}
void mgl::MultiVertexArray::draw_multiple_indexed(size_t index, VertexConnectionType connection, size_t drawcount, int const* counts, int const* byte_offsets, DrawIndexType type) {
	if (GlobalStateController::bound_buffer(mgl::BufferBindingPoint::ElementArrayBuffer).first == nullptr)
		throw Exceptions::AttribPointerError("Indexed draw is impossible without a buffer with index data being bound to BufferBindingPoint::ElementArrayBuffer.");
	bind(index);
	glMultiDrawElements(enum_converter::convert(connection), (GLsizei*) counts, enum_converter::convert(type), (void**) (byte_offsets), GLsizei(drawcount));
}
void mgl::MultiVertexArray::draw_multiple_indexed(size_t index, VertexConnectionType connection, size_t drawcount, int const* counts, int const* byte_offsets, int const* base_vertices, DrawIndexType type) {
	if (GlobalStateController::bound_buffer(mgl::BufferBindingPoint::ElementArrayBuffer).first == nullptr)
		throw Exceptions::AttribPointerError("Indexed draw is impossible without a buffer with index data being bound to BufferBindingPoint::ElementArrayBuffer.");
	bind(index);
	glMultiDrawElementsBaseVertex(enum_converter::convert(connection), (GLsizei*) counts, enum_converter::convert(type), (void**) (byte_offsets), GLsizei(drawcount), (GLint*) base_vertices);
}
void mgl::MultiVertexArray::draw_multiple_indirect(size_t index, VertexConnectionType connection, size_t drawcount, size_t byte_offset, size_t stride) {
	if (GlobalStateController::bound_buffer(mgl::BufferBindingPoint::DrawIndirectBuffer).first == nullptr)
		throw Exceptions::AttribPointerError("Indirect draw is impossible without a buffer with draw data being bound to BufferBindingPoint::DrawIndirectBuffer.");
	bind(index);
	glMultiDrawArraysIndirect(enum_converter::convert(connection), (void*) (byte_offset), GLsizei(drawcount), GLsizei(stride));
}
void mgl::MultiVertexArray::draw_multiple_indexed_indirect(size_t index, VertexConnectionType connection, size_t drawcount, DrawIndexType type, size_t byte_offset, size_t stride) {
	if (GlobalStateController::bound_buffer(mgl::BufferBindingPoint::ElementArrayBuffer).first == nullptr)
		throw Exceptions::AttribPointerError("Indexed draw is impossible without a buffer with index data being bound to BufferBindingPoint::ElementArrayBuffer.");
	if (GlobalStateController::bound_buffer(mgl::BufferBindingPoint::DrawIndirectBuffer).first == nullptr)
		throw Exceptions::AttribPointerError("Indirect draw is impossible without a buffer with draw data being bound to BufferBindingPoint::DrawIndirectBuffer.");
	bind(index);
	glMultiDrawElementsIndirect(enum_converter::convert(connection), enum_converter::convert(type), (void*) (byte_offset), GLsizei(drawcount), GLsizei(stride));
}