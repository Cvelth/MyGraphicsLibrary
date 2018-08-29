#include "mgl/dependencies/OpenGL_Dependency/opengl_dependency.hpp"
#include "GlobalStateController.hpp"
#include "mgl/EnumConverter/enum_converter.hpp"

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
	else if (!bound_buffer(binding_point).first || buffer->m_ids[index] != bound_buffer(binding_point).first->m_ids[index])
		glBindBuffer(mgl::enum_converter::convert(binding_point), buffer->m_ids[index]);
	m_buffers_bound[size_t(binding_point)] = std::make_pair(buffer, index);
}
std::pair<mgl::MultiBuffer const*, size_t> const mgl::GlobalStateController::bound_buffer(BufferBindingPoint const& binding_point) {
	return m_buffers_bound[size_t(binding_point)];
}
