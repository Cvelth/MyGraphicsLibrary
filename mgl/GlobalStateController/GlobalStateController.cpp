#include "mgl/dependencies/OpenGL_Dependency/opengl_dependency.hpp"
#include "GlobalStateController.hpp"
#include "mgl/EnumConverter/enum_converter.hpp"

bool mgl::GlobalStateController::m_is_initialized = false;

#include "mgl/ShaderProgram/ShaderProgram.hpp"
mgl::ShaderProgram *mgl::GlobalStateController::m_shader_program_used = nullptr;
void mgl::GlobalStateController::use_shader_program(ShaderProgram *program) {
	if (!program)
		glUseProgram(0);
	else if (m_shader_program_used != program)
		glUseProgram(program->m_id);
	else
		return;
	m_shader_program_used = program;
}
mgl::ShaderProgram const* mgl::GlobalStateController::used_shader_program() {
	return m_shader_program_used;
}

#include "mgl/VertexData/Buffer.hpp"
std::pair<mgl::MultiBuffer*, size_t> mgl::GlobalStateController::m_buffers_bound[14];
void mgl::GlobalStateController::bind_buffer(BufferBindingPoint const& binding_point, MultiBuffer *buffer, size_t index) {
	if (!buffer)
		glBindBuffer(mgl::enum_converter::convert(binding_point), 0);
	else if (!bound_buffer(binding_point).first || buffer->m_ids[index] != bound_buffer(binding_point).first->m_ids[bound_buffer(binding_point).second])
		glBindBuffer(mgl::enum_converter::convert(binding_point), buffer->m_ids[index]);
	else
		return;
	m_buffers_bound[size_t(binding_point)] = std::make_pair(buffer, index);
}
std::pair<mgl::MultiBuffer const*, size_t> const mgl::GlobalStateController::bound_buffer(BufferBindingPoint const& binding_point) {
	return m_buffers_bound[size_t(binding_point)];
}

#include "mgl/VertexData/VertexArray.hpp"
std::pair<mgl::MultiVertexArray*, size_t> mgl::GlobalStateController::m_vertex_array_bound;
void mgl::GlobalStateController::bind_vertex_array(MultiVertexArray *vertex_array, size_t index) {
	if (!vertex_array)
		glBindVertexArray(0);
	else if (!m_vertex_array_bound.first || vertex_array->m_ids[index] != m_vertex_array_bound.first->m_ids[m_vertex_array_bound.second])
		glBindVertexArray(vertex_array->m_ids[index]);
	else
		return;
	m_vertex_array_bound = std::make_pair(vertex_array, index);
}
std::pair<mgl::MultiVertexArray const*, size_t> const mgl::GlobalStateController::bound_vertex_array() {
	return m_vertex_array_bound;
}
